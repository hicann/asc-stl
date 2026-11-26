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

#pragma once

#include <asc/std/compare>
#include "support/comparison_helpers_semantics.h"

namespace asc_stl_test_compare {

CANN_ASC_STL_API int check(int seed = 7)
{
    const int a = seed - 1;
    const int b = seed;
    // Read the same immutable table directly in each kernel invocation.
    static constexpr unsigned int categories[] = {0, 1, 2, 3, 0, 1, 2, 0, 1, 1, 2};
    const auto results = asc_stl_comparison_helpers_test::evaluate(categories);
    if (results.failures || results.checks != 66 || !asc::std::is_lt(asc::std::compare_strong_order_fallback{}(a, b)) ||
        !asc::std::is_gt(asc::std::compare_weak_order_fallback{}(b, a)) ||
        !asc::std::is_eq(asc::std::compare_partial_order_fallback{}(a, a)))
        return 1;
#if CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON()
    if (!(asc::std::compare_three_way{}(a, b) < 0) || !(asc::std::compare_three_way{}(1.0f, 1.0f) == 0) ||
        asc::std::compare_three_way{}(__builtin_nanf(""), 1.0f) == 0)
        return 2;
#endif
    return 0;
}

}  // namespace asc_stl_test_compare
