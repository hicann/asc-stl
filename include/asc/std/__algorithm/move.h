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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_H

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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

// 通用逐元素移动，返回 (源尾, 目标尾)；经典路径下元素取出即
// ::asc::std::move(*it)。首个模板参数为算法策略占位（默认 void），
// 供按策略分派的内部算法以 __move<策略>(...) 形式复用。
template <class _AlgPolicy = void, class _InputIterator, class _OutputIterator>
CANN_ASC_STL_API constexpr pair<_InputIterator, _OutputIterator> __move(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result)
{
    for (; __first != __last; ++__first, (void)++__result) {
        *__result = ::asc::std::move(*__first);  // NOLINT(build/include_what_you_use)
    }
    return {__last, __result};
}

// 平凡可拷贝指针特化：移动退化为 memmove 位搬移；常量求值期与设备 TU
// 回退到逐元素移动循环（对平凡可拷贝类型即逐元素拷贝，语义等价）。
template <class _AlgPolicy = void, class _Tp, class _Up, enable_if_t<is_same_v<remove_const_t<_Tp>, _Up>, int> = 0,
    enable_if_t<is_trivially_copyable_v<_Up>, int> = 0>
CANN_ASC_STL_API constexpr pair<_Tp*, _Up*> __move(_Tp* __first, _Tp* __last, _Up* __result)
{
    const ptrdiff_t __n = __last - __first;
    if (__n > 0) {
        if (::asc::std::__memmove_dispatch(__result, __first, static_cast<size_t>(__n))) {
            return {__last, __result + __n};
        }
        for (ptrdiff_t __i = 0; __i < __n; ++__i) {
            *(__result + __i) = ::asc::std::move(*(__first + __i));  // NOLINT(build/include_what_you_use)
        }
    }
    return {__last, __result + __n};
}

template <class InputIterator, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator move(  // NOLINT(build/include_what_you_use)
    InputIterator first, InputIterator last, OutputIterator result)
{
    static_assert(is_copy_constructible_v<InputIterator>, "Iterators has to be copy constructible.");
    static_assert(is_copy_constructible_v<OutputIterator>, "The output iterator has to be copy constructible.");
    return ::asc::std::__move(
        ::asc::std::__unwrap_iter(first), ::asc::std::__unwrap_iter(last), ::asc::std::__unwrap_iter(result))
        .second;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_H
