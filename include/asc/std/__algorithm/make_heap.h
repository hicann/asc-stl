/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAKE_HEAP_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAKE_HEAP_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/sift_down.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __make_heap(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare&& __comp)
{
    __comp_ref_type<_Compare> __comp_ref = __comp;

    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    difference_type __n = __last - __first;
    if (__n > 1) {
        // start from the first parent, there is no need to consider children
        for (difference_type __start = (__n - 2) / 2; __start >= 0; --__start) {
            ::asc::std::__sift_down<_AlgPolicy>(__first, __comp_ref, __n, __first + __start);
        }
    }
}
template <class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    ::asc::std::__make_heap<_ClassicAlgPolicy>(::asc::std::move(__first), ::asc::std::move(__last), __comp);
}
template <class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    ::asc::std::make_heap(
        ::asc::std::move(__first), ::asc::std::move(__last), __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAKE_HEAP_H
