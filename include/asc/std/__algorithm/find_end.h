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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_END_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_END_H

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
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr ForwardIterator1 find_end(ForwardIterator1 first1,
    ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate)
{
    if (first2 == last2) {
        return last1;
    }
    ForwardIterator1 result = last1;
    for (; first1 != last1; ++first1) {
        ForwardIterator1 current1 = first1;
        ForwardIterator2 current2 = first2;
        while (current1 != last1 && current2 != last2 && predicate(*current1, *current2)) {
            ++current1;
            ++current2;
        }
        if (current2 == last2) {
            result = first1;
        }
        if (current1 == last1) {
            break;
        }
    }
    return result;
}

template <class ForwardIterator1, class ForwardIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr ForwardIterator1 find_end(
    ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    return ::asc::std::find_end(first1, last1, first2, last2, __equal_to{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_END_H
