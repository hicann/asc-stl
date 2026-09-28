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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_NEXT_PERMUTATION_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_NEXT_PERMUTATION_H

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
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__algorithm/reverse.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class BidirectionalIterator, class Compare>
CANN_ASC_STL_API constexpr bool next_permutation(
    BidirectionalIterator first, BidirectionalIterator last, Compare compare)
{
    if (first == last) {
        return false;
    }
    BidirectionalIterator current = last;
    if (first == --current) {
        return false;
    }
    for (;;) {
        BidirectionalIterator previous = current;
        if (compare(*--current, *previous)) {
            BidirectionalIterator selected = last;
            while (!compare(*current, *--selected)) {
            }
            ::asc::std::iter_swap(current, selected);
            ::asc::std::reverse(previous, last);
            return true;
        }
        if (current == first) {
            ::asc::std::reverse(first, last);
            return false;
        }
    }
}

template <class BidirectionalIterator>
CANN_ASC_STL_API constexpr bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
{
    return ::asc::std::next_permutation(first, last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_NEXT_PERMUTATION_H
