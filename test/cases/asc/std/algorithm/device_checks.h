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

#ifndef ASC_STL_TEST_ALGORITHM_DEVICE_CHECKS_H
#define ASC_STL_TEST_ALGORITHM_DEVICE_CHECKS_H

#include <asc/std/algorithm>
#include <asc/std/random>
#include "support/private_sort.h"

namespace asc_stl_test_algorithm {
struct less {
    CANN_ASC_STL_API bool operator()(int a, int b) const
    {
        return a < b;
    }
};
struct even {
    CANN_ASC_STL_API bool operator()(int a) const
    {
        return a % 2 == 0;
    }
};
struct add {
    CANN_ASC_STL_API int operator()(int a, int b) const
    {
        return a + b;
    }
};

CANN_ASC_STL_API int check(int seed = 7)
{
    namespace s = ::asc::std;
    if (asc_stl_private_sort_test::check(seed) != 0)
        return 25;
    int values[] = {seed, 4, 6, 2, 9, 1};
    // Keep this oracle independent of the input. CANN 9.3 can miscopy a
    // constant aggregate from global memory into a lane-private array.
    const volatile int one = 1;
    const int sorted[] = {one, 2 * one, 4 * one, 6 * one, 7 * one, 9 * one};
    s::make_heap(values, values + 5, less{});
    s::push_heap(values, values + 6, less{});
    if (values[0] != 9 || !s::is_heap(values, values + 6))
        return 1;
    s::pop_heap(values, values + 6, less{});
    if (values[5] != 9 || !s::is_heap(values, values + 5))
        return 2;
    s::sort_heap(values, values + 5, less{});
    if (!s::equal(values, values + 6, sorted))
        return 3;
    s::make_heap(values, values + 5);
    s::push_heap(values, values + 6);
    s::pop_heap(values, values + 6);
    s::sort_heap(values, values + 5);
    if (!s::equal(values, values + 6, sorted))
        return 4;
    int perms[] = {1, 1, 2};
    if (!s::next_permutation(perms, perms + 3) || perms[1] != 2 || !s::next_permutation(perms, perms + 3, less{}) ||
        perms[0] != 2 || s::next_permutation(perms, perms + 3) || perms[2] != 2 ||
        s::prev_permutation(perms, perms + 3, less{}) || perms[0] != 2 || !s::prev_permutation(perms, perms + 3) ||
        perms[1] != 2)
        return 5;
    s::iter_swap(perms, perms + 1);
    int pair[] = {3, 4};
    if (s::swap_ranges(perms, perms + 2, pair) != pair + 2 || perms[0] != 3 || perms[1] != 4 || pair[0] != 2 ||
        pair[1] != 1)
        return 6;
    s::minstd_rand rng(17);
    s::shuffle(values, values + 6, rng);
    if (!s::is_permutation(values, values + 6, sorted))
        return 7;
    int sample[8] = {};
    if (s::sample(sorted, sorted + 6, sample, 9, rng) != sample + 6 || !s::equal(sample, sample + 6, sorted) ||
        sample[6] != 0 || s::sample(sorted, sorted + 6, sample, 0, rng) != sample)
        return 8;
    if (s::sample(sorted, sorted + 6, sample, 3, rng) != sample + 3 || !s::is_sorted(sample, sample + 3) ||
        !s::includes(sorted, sorted + 6, sample, sample + 3))
        return 9;
    int range[] = {4, 1, 2, 1};
    if (s::ranges::sort(range) != range + 4 || !s::ranges::contains(range, 4) || s::ranges::find(range, 1) != range ||
        s::ranges::find_if(range, even{}) != range + 2 || s::ranges::find_if_not(range, even{}) != range ||
        s::ranges::min_element(range) != range || s::ranges::min(range) != 1 ||
        s::ranges::fold_left(range, 1, add{}) != 9)
        return 10;
    int second[] = {2, 3};
    const auto combined = s::ranges::transform(range, second, sample, add{});
    if (combined.in1 != range + 2 || combined.in2 != second + 2 || combined.out != sample + 2 || sample[0] != 3 ||
        sample[1] != 4)
        return 11;
    return 0;
}
}  // namespace asc_stl_test_algorithm

#endif  // ASC_STL_TEST_ALGORITHM_DEVICE_CHECKS_H
