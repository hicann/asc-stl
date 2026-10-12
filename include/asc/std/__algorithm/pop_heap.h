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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_POP_HEAP_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_POP_HEAP_H

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
#include <asc/std/__algorithm/push_heap.h>
#include <asc/std/__algorithm/sift_down.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// 策略化内部入口：供 sort_heap / ranges 等策略迁移头复用。
// _AlgPolicy 需提供静态 iter_move/iter_swap（如 __classic_algorithm_iterator_operations）。
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare& __comp, typename iterator_traits<_RandomAccessIterator>::difference_type __len)
{
    // Calling `pop_heap` on an empty range is undefined behavior, but in practice it will be a no-op.
    CANN_ASC_STL_DETAIL_ASSERT(__len > 0, "The heap given to pop_heap must be non-empty");

    __comp_ref_type<_Compare> __comp_ref = __comp;

    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    if (__len > 1) {
        value_type __top = _AlgPolicy::iter_move(__first);  // create a hole at __first
        _RandomAccessIterator __hole = ::asc::std::__floyd_sift_down<_AlgPolicy>(__first, __comp_ref, __len);
        --__last;

        if (__hole == __last) {
            *__hole = ::asc::std::move(__top);  // NOLINT(build/include_what_you_use)
        } else {
            *__hole = _AlgPolicy::iter_move(__last);
            ++__hole;
            *__last = ::asc::std::move(__top);  // NOLINT(build/include_what_you_use)
            ::asc::std::__sift_up<_AlgPolicy>(__first, __hole, __comp_ref, __hole - __first);
        }
    }
}

template <class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    static_assert(::asc::std::is_copy_constructible_v<_RandomAccessIterator>, "Iterators must be copy constructible.");
    static_assert(::asc::std::is_copy_assignable_v<_RandomAccessIterator>, "Iterators must be copy assignable.");

    typename iterator_traits<_RandomAccessIterator>::difference_type __len = __last - __first;
    ::asc::std::__pop_heap<__classic_algorithm_iterator_operations>(
        ::asc::std::move(__first), ::asc::std::move(__last), __comp, __len);
}

template <class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    ::asc::std::pop_heap(                                                // NOLINT(build/include_what_you_use)
        ::asc::std::move(__first), ::asc::std::move(__last), __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_POP_HEAP_H
