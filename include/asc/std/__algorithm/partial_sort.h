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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_PARTIAL_SORT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_PARTIAL_SORT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/make_heap.h>
#include <asc/std/__algorithm/sift_down.h>
#include <asc/std/__algorithm/sort_heap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// 策略化内部入口（支持哨兵、返回到达末尾的迭代器）：供 ranges 等策略迁移头复用。
// _AlgPolicy 需提供静态 iter_move/iter_swap；基座无 dev 侧 __make_heap 策略入口，
// 建堆走公开 make_heap（比较器按值拷贝，语义等价）。
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator, class _Sentinel>
CANN_ASC_STL_API constexpr _RandomAccessIterator __partial_sort_impl(
    _RandomAccessIterator __first, _RandomAccessIterator __middle, _Sentinel __last, _Compare&& __comp)
{
    if (__first == __middle) {
        while (__middle != __last) {
            ++__middle;
        }
        return __middle;
    }

    ::asc::std::make_heap(__first, __middle, __comp);

    typename iterator_traits<_RandomAccessIterator>::difference_type __len = __middle - __first;
    _RandomAccessIterator __i = __middle;
    for (; __i != __last; ++__i) {
        if (__comp(*__i, *__first)) {
            _AlgPolicy::iter_swap(__i, __first);
            ::asc::std::__sift_down<_AlgPolicy>(__first, __comp, __len, __first);
        }
    }
    ::asc::std::__sort_heap<_AlgPolicy>(::asc::std::move(__first), ::asc::std::move(__middle), __comp);

    return __i;
}

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator, class _Sentinel>
CANN_ASC_STL_API constexpr _RandomAccessIterator __partial_sort(
    _RandomAccessIterator __first, _RandomAccessIterator __middle, _Sentinel __last, _Compare& __comp)
{
    if (__first == __middle) {
        while (__middle != __last) {
            ++__middle;
        }
        return __middle;
    }

    return ::asc::std::__partial_sort_impl<_AlgPolicy>(
        __first, __middle, __last, static_cast<__comp_ref_type<_Compare>>(__comp));
}

//! @brief 部分排序：使 [first, middle) 按升序含整个区间最小的 (middle - first) 个元素，
//! 余下元素置于 [middle, last) 无序。
template <class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void partial_sort(
    _RandomAccessIterator __first, _RandomAccessIterator __middle, _RandomAccessIterator __last, _Compare __comp)
{
    static_assert(is_copy_constructible_v<_RandomAccessIterator>, "Iterators must be copy constructible.");
    static_assert(is_copy_assignable_v<_RandomAccessIterator>, "Iterators must be copy assignable.");

    (void)::asc::std::__partial_sort<__classic_algorithm_iterator_operations>(::asc::std::move(__first),
        ::asc::std::move(__middle), ::asc::std::move(__last), __comp);  // NOLINT(build/include_what_you_use)
}

//! @brief 部分排序（默认 less 比较）。
template <class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void partial_sort(
    _RandomAccessIterator __first, _RandomAccessIterator __middle, _RandomAccessIterator __last)
{
    ::asc::std::partial_sort(__first, __middle, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_PARTIAL_SORT_H
