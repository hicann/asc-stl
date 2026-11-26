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

#ifndef ASC_STL_TEST_ALGORITHM_PRIVATE_SORT_H
#define ASC_STL_TEST_ALGORITHM_PRIVATE_SORT_H

#include <asc/std/algorithm>

namespace asc_stl_private_sort_test {

// Keep this result-only call separate: making the array escape changes
// BiSheng's release code generation for naturally aligned private storage.
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int constant_five()
{
    int values[] = {5, 1, 4, 2, 3};
    asc::std::sort(values, values + 5);  // NOLINT(build/include_what_you_use)
    return values[0] != 1 || values[4] != 5;
}

struct descending {
    CANN_ASC_STL_API bool operator()(int a, int b) const
    {
        return a > b;
    }
};

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool dynamic_five(int seed)
{
    int small[] = {seed + 5, seed + 1, seed + 4, seed + 2, seed + 3};
    asc::std::sort(small, small + 5, descending{});  // NOLINT(build/include_what_you_use)
    for (int i = 0; i < 5; ++i) {
        if (small[i] != seed + 5 - i)
            return false;
    }
    return true;
}

CANN_ASC_STL_API constexpr int fixed_value(int index)
{
    return index % 2 == 0 ? 17 - index / 2 : 8 - index / 2;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int constant_seventeen()
{
    // A fused SIMT kernel can miscopy a 68-byte constant initializer before
    // sort runs. Materialize the same fixed permutation and check its input.
    int constant[17];
    volatile int* initialized = constant;
    for (int i = 0; i < 17; ++i)
        initialized[i] = fixed_value(i);
    for (int i = 0; i < 17; ++i) {
        if (initialized[i] != fixed_value(i))
            return 3;
    }
    asc::std::sort(constant, constant + 17, descending{});  // NOLINT(build/include_what_you_use)
    for (int i = 0; i < 17; ++i) {
        if (constant[i] != 17 - i)
            return 4;
    }
    return 0;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool dynamic_seventeen(int seed)
{
    int dynamic[17];
    for (int i = 0; i < 17; ++i)
        dynamic[i] = seed + 17 - i;
    asc::std::sort(dynamic, dynamic + 17);  // NOLINT(build/include_what_you_use)
    for (int i = 0; i < 17; ++i) {
        if (dynamic[i] != seed + i + 1)
            return false;
    }
    return true;
}

CANN_ASC_STL_API unsigned int check(int seed)
{
    if (constant_five() != 0)
        return 1;
    if (!dynamic_five(seed))
        return 2;
    if (const auto failure = constant_seventeen())
        return failure;
    return dynamic_seventeen(seed) ? 0 : 5;
}

}  // namespace asc_stl_private_sort_test

#endif  // ASC_STL_TEST_ALGORITHM_PRIVATE_SORT_H
