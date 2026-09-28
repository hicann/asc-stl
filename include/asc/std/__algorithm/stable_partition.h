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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_STABLE_PARTITION_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_STABLE_PARTITION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/rotate.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#define CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API CANN_ASC_STL_HOST_API
#else
#define CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API CANN_ASC_STL_API
#endif

template <class ForwardIterator, class Predicate>
CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API constexpr ForwardIterator stable_partition(
    ForwardIterator first, ForwardIterator last, Predicate predicate)
{
    while (first != last && predicate(*first)) {
        ++first;
    }
    ForwardIterator boundary = first;
    for (ForwardIterator current = first; current != last; ++current) {
        if (predicate(*current)) {
            ForwardIterator next = current;
            ++next;
            ::asc::std::rotate(boundary, current, next);
            ++boundary;
        }
    }
    return boundary;
}

CANN_ASC_STL_END_NAMESPACE

#undef CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_STABLE_PARTITION_H
