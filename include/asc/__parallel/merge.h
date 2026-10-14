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

#ifndef CANN_ASC_STL_ASC___PARALLEL_MERGE_H
#define CANN_ASC_STL_ASC___PARALLEL_MERGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {
// Zip merge over two sorted runs in one pass. Tie handling is deliberate and
// load-bearing for stability: when compare(*first2, *first1) is false the
// element of the first (left) run is emitted first, so equal keys keep their
// input order. Rewriting the branch as compare(*first1, *first2) would flip
// the tie to the right run and silently break every stable consumer
// (merge_sort_operation in merge_sort.h relies on this exact tie rule).
// Parallelization path (later runtime work, kept as an anchor): merge-path
// partitioning - each tile binary-searches its diagonal alignment point in
// both runs and merges its tile independently; until that plan lands, this
// single-work-item scan is the documented sequential baseline.
template <class Input1, class Input2, class Output, class Compare>
struct merge_operation {
    Input1 first1;
    Input1 last1;
    Input2 first2;
    Input2 last2;
    Output result;
    Compare compare;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        while (first1 != last1 && first2 != last2) {
            if (compare(*first2, *first1)) {
                *result = *first2;
                ++first2;
            } else {
                *result = *first1;
                ++first1;
            }
            ++result;
        }
        while (first1 != last1) {
            *result = *first1;
            ++first1;
            ++result;
        }
        while (first2 != last2) {
            *result = *first2;
            ++first2;
            ++result;
        }
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_MERGE_H
