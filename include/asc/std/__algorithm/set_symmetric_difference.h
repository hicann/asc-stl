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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SET_SYMMETRIC_DIFFERENCE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SET_SYMMETRIC_DIFFERENCE_H

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

CANN_ASC_STL_BEGIN_NAMESPACE

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
CANN_ASC_STL_API constexpr OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)
{
    while (first1 != last1 && first2 != last2) {
        if (compare(*first1, *first2)) {
            *result++ = *first1++;
        } else if (compare(*first2, *first1)) {
            *result++ = *first2++;
        } else {
            ++first1;
            ++first2;
        }
    }
    while (first1 != last1) {
        *result++ = *first1++;
    }
    while (first2 != last2) {
        *result++ = *first2++;
    }
    return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator set_symmetric_difference(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    return ::asc::std::set_symmetric_difference(first1, last1, first2, last2, result, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SET_SYMMETRIC_DIFFERENCE_H
