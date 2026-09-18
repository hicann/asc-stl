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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_POP_HEAP_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_POP_HEAP_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/push_heap.h>
#include <asc/std/__algorithm/sift_down.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare& __comp, typename iterator_traits<_RandomAccessIterator>::difference_type __len)
{
    // Calling `pop_heap` on an empty range is undefined behavior, but in practice it will be a no-op.
    CANN_ASC_STL_DETAIL_ASSERT(__len > 0, "The heap given to pop_heap must be non-empty");

    __comp_ref_type<_Compare> __comp_ref = __comp;

    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    if (__len > 1) {
        value_type __top = _IterOps<_AlgPolicy>::__iter_move(__first);  // create a hole at __first
        _RandomAccessIterator __hole = ::asc::std::__floyd_sift_down<_AlgPolicy>(__first, __comp_ref, __len);
        --__last;

        if (__hole == __last) {
            *__hole = ::asc::std::move(__top);
        } else {
            *__hole = _IterOps<_AlgPolicy>::__iter_move(__last);
            ++__hole;
            *__last = ::asc::std::move(__top);
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
    ::asc::std::__pop_heap<_ClassicAlgPolicy>(::asc::std::move(__first), ::asc::std::move(__last), __comp, __len);
}
template <class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    ::asc::std::pop_heap(
        ::asc::std::move(__first), ::asc::std::move(__last), __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_POP_HEAP_H
