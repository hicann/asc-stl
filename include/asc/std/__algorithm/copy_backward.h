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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_BACKWARD_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_BACKWARD_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/copy.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/cstddef>
#include <asc/std/cstring>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _BidirectionalIterator, class _OutputIterator>
CANN_ASC_STL_API constexpr _OutputIterator __copy_backward(
    _BidirectionalIterator __first, _BidirectionalIterator __last, _OutputIterator __result)
{
    while (__first != __last) {
        *--__result = *--__last;
    }
    return __result;
}

// 基座 copy.h 尚无 __dispatch_memmove，按 dev 语义内联最小等价实现：
// 常量求值期返回 false 走 constexpr 逐元素回退；运行期宿主用 builtin/libc
// memmove 返回 true；设备 TU 上两条路均不可用（aicore 链接无 libc），一律
// 返回 false 走 constexpr 循环，语义等价、性能次优。
template <class _Tp, class _Up>
CANN_ASC_STL_API constexpr bool __dispatch_memmove(_Up* __result, _Tp* __first, const size_t __n)
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

template <class _Tp, class _Up, enable_if_t<is_same_v<remove_const_t<_Tp>, _Up>, int> = 0,
    enable_if_t<is_trivially_copyable_v<_Up>, int> = 0>
CANN_ASC_STL_API constexpr _Up* __copy_backward(_Tp* __first, _Tp* __last, _Up* __result)
{
    const ptrdiff_t __n = __last - __first;
    if (__n > 0) {
        if (__dispatch_memmove(__result - __n, __first, __n)) {
            return __result - __n;
        }
        for (ptrdiff_t __i = 1; __i <= __n; ++__i) {
            *(__result - __i) = *(__last - __i);
        }
    }
    return __result - __n;
}

template <class _BidirectionalIterator1, class _BidirectionalIterator2>
CANN_ASC_STL_API constexpr _BidirectionalIterator2 copy_backward(
    _BidirectionalIterator1 __first, _BidirectionalIterator1 __last, _BidirectionalIterator2 __result)
{
    return ::asc::std::__copy_backward(
        ::asc::std::__unwrap_iter(__first), ::asc::std::__unwrap_iter(__last), ::asc::std::__unwrap_iter(__result));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_BACKWARD_H
