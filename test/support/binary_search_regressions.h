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

#ifndef ASC_STL_TEST_SUPPORT_BINARY_SEARCH_REGRESSIONS_H
#define ASC_STL_TEST_SUPPORT_BINARY_SEARCH_REGRESSIONS_H

#include <asc/std/__algorithm/lower_bound.h>
#include <asc/std/__algorithm/upper_bound.h>

namespace asc_stl_binary_search_test {
struct Less {
    CANN_ASC_STL_API constexpr bool operator()(int lhs, int rhs) const
    {
        return lhs < rhs;
    }
};
struct Greater {
    CANN_ASC_STL_API constexpr bool operator()(int lhs, int rhs) const
    {
        return lhs > rhs;
    }
};

template <class Pointer, class Compare>
CANN_ASC_STL_API int check_range(Pointer first, int length, Compare comp)
{
    for (int query = -22; query <= 102; ++query) {
        // A linear scan supplies an independent reference for both boundaries.
        int lower = 0;
        while (lower < length && comp(first[lower], query)) {
            ++lower;
        }
        int upper = 0;
        while (upper < length && !comp(query, first[upper])) {
            ++upper;
        }
        asc::std::identity projection;
        if (asc::std::lower_bound(first, first + length, query, comp) != first + lower ||
            asc::std::upper_bound(first, first + length, query, comp) != first + upper ||
            asc::std::__lower_bound_indexed(first, length, query, comp, projection) != first + lower ||
            asc::std::__upper_bound_indexed(first, length, query, comp, projection) != first + upper) {
            return 1;
        }
    }
    return 0;
}
}  // namespace asc_stl_binary_search_test

#endif  // ASC_STL_TEST_SUPPORT_BINARY_SEARCH_REGRESSIONS_H
