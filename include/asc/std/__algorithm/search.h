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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_H

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
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
CANN_ASC_STL_API ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 pattern_first,
    ForwardIterator2 pattern_last, BinaryPredicate predicate)
{
    if (pattern_first == pattern_last) {
        return first;
    }
    for (; first != last; ++first) {
        ForwardIterator1 current = first;
        ForwardIterator2 pattern = pattern_first;
        while (predicate(*current, *pattern)) {
            ++pattern;
            if (pattern == pattern_last) {
                return first;
            }
            ++current;
            if (current == last) {
                return last;
            }
        }
    }
    return last;
}

template <class ForwardIterator1, class ForwardIterator2>
CANN_ASC_STL_API ForwardIterator1 search(
    ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 pattern_first, ForwardIterator2 pattern_last)
{
    return ::asc::std::search(first, last, pattern_first, pattern_last, __equal_to{});
}

template <class ForwardIterator, class Searcher>
CANN_ASC_STL_API ForwardIterator search(ForwardIterator first, ForwardIterator last, const Searcher& searcher)
{
    return searcher(first, last).first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_H
