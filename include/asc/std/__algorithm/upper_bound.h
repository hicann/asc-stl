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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_UPPER_BOUND_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_UPPER_BOUND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/cstdint>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/half_positive.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Keep index arithmetic in 32 bits without backend-specific bit intrinsics.
template <class _Iter, class _Type, class _Comp, class _Proj>
CANN_ASC_STL_API constexpr _Iter __upper_bound_indexed(
    _Iter __first, int32_t __length, const _Type& __value, _Comp& __comp, _Proj& __proj)
{
    int32_t __left = 0;
    int32_t __right = __length;
    while (__left < __right) {
        const int32_t __mid = __left + (__right - __left) / 2;
        const bool __advance = !::asc::std::invoke(__comp, __value, ::asc::std::invoke(__proj, __first[__mid]));
        __left = __advance ? __mid + 1 : __left;
        __right = __advance ? __right : __mid;
    }
    return __first + __left;
}

template <class _AlgPolicy, class _Compare, class _Iter, class _Sent, class _Tp, class _Proj>
CANN_ASC_STL_API constexpr _Iter __upper_bound(
    _Iter __first, _Sent __last, const _Tp& __value, _Compare&& __comp, _Proj&& __proj)
{
    auto __len = ::asc::std::distance(__first, __last);
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // Keep Device pointer indices in 32 bits when the range fits.
    // Larger ranges retain the iterator difference_type in the fallback below.
    if constexpr (is_pointer_v<_Iter>) {
        if (__len >= 0 && __len <= 2147483647) {
            return ::asc::std::__upper_bound_indexed(__first, static_cast<int32_t>(__len), __value, __comp, __proj);
        }
    }
#endif

    while (__len != 0) {
        auto __half_len = ::asc::std::__half_positive(__len);
        auto __mid = __first;
        ::asc::std::advance(__mid, __half_len);
        if (::asc::std::invoke(__comp, __value, ::asc::std::invoke(__proj, *__mid))) {
            __len = __half_len;
        } else {
            __first = ++__mid;
            __len -= __half_len + 1;
        }
    }
    return __first;
}

template <class _ForwardIterator, class _Tp, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator upper_bound(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value, _Compare __comp)
{
    static_assert(is_copy_constructible_v<_ForwardIterator>, "Iterator has to be copy constructible");
    return ::asc::std::__upper_bound<__classic_algorithm_iterator_operations>(
        ::asc::std::move(__first), ::asc::std::move(__last), __value, ::asc::std::move(__comp), ::asc::std::identity());
}

template <class _ForwardIterator, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator upper_bound(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
{
    return ::asc::std::upper_bound(  // NOLINT(build/include_what_you_use)
                                     // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::move(__first), ::asc::std::move(__last), __value, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_UPPER_BOUND_H
