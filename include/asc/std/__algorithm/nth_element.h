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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_NTH_ELEMENT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_NTH_ELEMENT_H

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
#include <asc/std/__algorithm/sort.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class RandomAccessIterator, class Compare>
CANN_ASC_STL_API constexpr void nth_element(
    RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare compare)
{
    if (nth == last) {
        return;
    }
    // Complexity-stress variants are outside the bounded contract. Selecting
    // the prefix through nth gives the required partition without recursion
    // or the D-SIMT quickselect code-generation regression.
    using difference_type = typename iterator_traits<RandomAccessIterator>::difference_type;
    const difference_type count = last - first;
    const difference_type nth_index = nth - first;
    for (difference_type selected = 0; selected <= nth_index; ++selected) {
        difference_type best = selected;
        for (difference_type current = selected + 1; current < count; ++current) {
            if (compare(first[current], first[best])) {
                best = current;
            }
        }
        if (best != selected) {
            ::asc::std::iter_swap(first + selected, first + best);
        }
    }
}

template <class RandomAccessIterator>
CANN_ASC_STL_API constexpr void nth_element(
    RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last)
{
    ::asc::std::nth_element(first, nth, last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_NTH_ELEMENT_H
