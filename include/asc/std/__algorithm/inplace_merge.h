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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_INPLACE_MERGE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_INPLACE_MERGE_H

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
#include <asc/std/__algorithm/lower_bound.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__algorithm/move.h>
#include <asc/std/__algorithm/rotate.h>
#include <asc/std/__algorithm/upper_bound.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#define CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API CANN_ASC_STL_HOST_API
#else
#define CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API CANN_ASC_STL_API
#endif

template <class BidirectionalIterator, class Compare>
CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API constexpr void inplace_merge(
    BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Compare compare)
{
    // Rotate each out-of-order right element into the first range. Equal left
    // elements stay before equal right elements, preserving stability.
    while (first != middle && middle != last) {
        if (!compare(*middle, *first)) {
            ++first;
            continue;
        }
        BidirectionalIterator next = middle;
        ++next;
        ::asc::std::rotate(first, middle, next);
        ++first;
        middle = next;
    }
}

template <class BidirectionalIterator>
CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API constexpr void inplace_merge(
    BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last)
{
    ::asc::std::inplace_merge(first, middle, last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#undef CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_INPLACE_MERGE_H
