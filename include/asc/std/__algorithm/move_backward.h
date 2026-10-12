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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_BACKWARD_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_BACKWARD_H

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
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

// 通用逐元素反向移动，返回 (源首, 目标尾)。首个模板参数为算法策略占位
// （默认 void），供按策略分派的内部算法以 __move_backward<策略>(...) 复用。
template <class _AlgPolicy = void, class _BidirectionalIterator, class _OutputIterator>
CANN_ASC_STL_API constexpr pair<_BidirectionalIterator, _OutputIterator> __move_backward(
    _BidirectionalIterator __first, _BidirectionalIterator __last, _OutputIterator __result)
{
    while (__first != __last) {
        *--__result = ::asc::std::move(*--__last);  // NOLINT(build/include_what_you_use)
    }
    return {__first, __result};
}

// 平凡可拷贝指针特化：反向移动退化为 memmove 位搬移（目标区整体前移）；
// 常量求值期与设备 TU 回退到逐元素反向移动循环，语义等价。
template <class _AlgPolicy = void, class _Tp, class _Up, enable_if_t<is_same_v<remove_const_t<_Tp>, _Up>, int> = 0,
    enable_if_t<is_trivially_copyable_v<_Up>, int> = 0>
CANN_ASC_STL_API constexpr pair<_Tp*, _Up*> __move_backward(_Tp* __first, _Tp* __last, _Up* __result)
{
    const ptrdiff_t __n = __last - __first;
    if (__n > 0) {
        if (::asc::std::__memmove_dispatch(__result - __n, __first, static_cast<size_t>(__n))) {
            return {__last, __result - __n};
        }
        for (ptrdiff_t __i = 1; __i <= __n; ++__i) {
            *(__result - __i) = ::asc::std::move(*(__last - __i));  // NOLINT(build/include_what_you_use)
        }
    }
    return {__last, __result - __n};
}

template <class BidirectionalIterator1, class BidirectionalIterator2>
CANN_ASC_STL_API constexpr BidirectionalIterator2 move_backward(
    BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
{
    return ::asc::std::__move_backward(
        ::asc::std::__unwrap_iter(first), ::asc::std::__unwrap_iter(last), ::asc::std::__unwrap_iter(result))
        .second;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_BACKWARD_H
