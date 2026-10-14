/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/cstdlib>
#include <asc/std/cstring>

CANN_ASC_STL_BEGIN_NAMESPACE

// General element-wise copy returning (source end, result end), for internal
// algorithms that need the source-end iterator. The first template parameter is
// a policy placeholder (defaults to void) so internal algorithms can reuse this
// template as __copy<policy>(...); the classic path uses no policy.
template <class _AlgPolicy = void, class _InputIterator, class _OutputIterator>
CANN_ASC_STL_API constexpr pair<_InputIterator, _OutputIterator> __copy(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    for (; __first != __last; ++__first, (void)++__result) {
        *__result = *__first;
    }
    return {__last, __result};
}

// memmove fast-path dispatch: returns false during constant evaluation to take
// the constexpr element-wise fallback; at runtime the host prefers the compiler
// builtin (constant lengths can be fully inlined), otherwise hosted libc
// ::memmove. Neither path is available in a device TU — for runtime lengths
// __builtin_memmove lowers to an external libc call and the aicore link has no
// libc — so it always returns false to take the constexpr loop, semantically
// equivalent but slower.
// Note: named to differ from the __dispatch_memmove inlined in copy_backward.h;
// a duplicate name would be a redefinition when both headers are included.
template <class _Tp, class _Up>
CANN_ASC_STL_API constexpr bool __memmove_dispatch(_Up* __result, _Tp* __first, const size_t __n)
{
    if (!::asc::std::is_constant_evaluated()) {
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && (defined(__GNUC__) || defined(__clang__))
        __builtin_memmove(__result, __first, __n * sizeof(_Up));
        return true;
#elif !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        ::memmove(__result, __first, __n * sizeof(_Up));
        return true;
#endif
    }
    return false;
}

// Tail-overlap detection for constant evaluation: relational pointer
// comparison is not valid in constant expressions for unrelated objects, so use
// an equality linear scan instead (the result only affects the loop direction
// when the ranges truly overlap; a scan that finds nothing means no overlap).
template <class _Tp, class _Up>
CANN_ASC_STL_API constexpr bool __constexpr_tail_overlap_fallback(_Tp* __first, _Up* __needle, _Tp* __last)
{
    bool __result = false;
    while (__first != __last) {
        if (__first == __needle) {
            __result = true;
            break;
        }
        ++__first;
    }
    return __result;
}

template <class _Tp, class _Up>
CANN_ASC_STL_API constexpr bool __constexpr_tail_overlap(_Tp* __first, _Up* __needle, [[maybe_unused]] _Tp* __last)
{
    if (!::asc::std::is_constant_evaluated()) {
        return __first < __needle;
    }
    return ::asc::std::__constexpr_tail_overlap_fallback(__first, __needle, __last);
}

// Trivially copyable pointer specialization: prefer the memmove fast path; the
// fallback picks a backward or forward element-wise loop based on the overlap
// direction, preserving memmove semantics.
template <class _AlgPolicy = void, class _Tp, class _Up, enable_if_t<is_same_v<remove_const_t<_Tp>, _Up>, int> = 0,
    enable_if_t<is_trivially_copyable_v<_Up>, int> = 0>
CANN_ASC_STL_API constexpr pair<_Tp*, _Up*> __copy(  // NOLINT(build/include_what_you_use)
    _Tp* __first, _Tp* __last, _Up* __result)
{
    const ptrdiff_t __n = __last - __first;
    if (__n > 0) {
        if (::asc::std::__memmove_dispatch(__result, __first, static_cast<size_t>(__n))) {
            return {__last, __result + __n};
        }
        if (::asc::std::__constexpr_tail_overlap(__first, __result, __last)) {
            for (ptrdiff_t __i = __n; __i > 0; --__i) {
                *(__result + __i - 1) = *(__first + __i - 1);
            }
        } else {
            for (ptrdiff_t __i = 0; __i < __n; ++__i) {
                *(__result + __i) = *(__first + __i);
            }
        }
    }
    return {__last, __result + __n};
}

template <class InputIterator, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator copy(  // NOLINT(build/include_what_you_use)
    InputIterator first, InputIterator last, OutputIterator result)
{
    return ::asc::std::__copy(
        ::asc::std::__unwrap_iter(first), ::asc::std::__unwrap_iter(last), ::asc::std::__unwrap_iter(result))
        .second;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_H
