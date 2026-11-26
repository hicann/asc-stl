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

#ifndef ASC_STL_TEST_STANDARD_ALGORITHM_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_ALGORITHM_SEMANTICS_H

#include <asc/std/algorithm>
#include <asc/std/random>

namespace asc_stl_standard_algorithm_test {

namespace ast = asc::std;

struct even {
    CANN_ASC_STL_API bool operator()(int value) const
    {
        return value % 2 == 0;
    }
};

CANN_ASC_STL_API int evaluate_mutations(int seed)
{
    const int sorted[] = {seed, seed + 1, seed + 1, seed + 3, seed + 7};
    if (ast::lower_bound(sorted, sorted + 5, seed + 1) != sorted + 1 ||
        ast::upper_bound(sorted, sorted + 5, seed + 1) != sorted + 3)
        return 1;
    int partitioned[] = {2 * seed, 2 * seed + 1, 2 * seed + 3, 2 * seed + 2, 2 * seed + 4, 2 * seed + 5};
    const auto* middle = ast::partition(partitioned, partitioned + 6, even{});
    if (middle != partitioned + 3)
        return 2;
    for (int index = 0; index < 6; ++index) {
        if (even{}(partitioned[index]) != (index < 3))
            return 3;
    }

    int heap[] = {seed + 7, seed + 2, seed + 4, seed + 1, seed + 9};
    ast::push_heap(heap, heap + 5);
    if (heap[0] != seed + 9 || !ast::is_heap(heap, heap + 5))
        return 4;

    int letters[] = {seed, seed + 1, seed + 2, seed + 3};
    ast::reverse(letters, letters + 4);
    for (int index = 0; index != 4; ++index) {
        if (letters[index] != seed + 3 - index)
            return 5;
    }

    const int left[] = {seed, seed + 1, seed + 2, seed + 6};
    const int right[] = {seed + 1, seed + 2, seed + 5};
    // Materialize the guard words with scalar stores. The CANN 9.3 SIMT
    // compiler can clobber the source address when copying a constant array.
    const volatile int guard = -1;
    int intersection[4] = {0, 0, guard, guard};
    if (ast::set_intersection(left, left + 4, right, right + 3, intersection) != intersection + 2 ||
        intersection[0] != seed + 1 || intersection[1] != seed + 2 || intersection[2] != -1 || intersection[3] != -1)
        return 6;

    int repeated[] = {seed, seed, seed + 1, seed + 1, seed + 2};
    int copied[5] = {0, 0, 0, guard, guard};
    if (ast::unique_copy(repeated, repeated + 5, copied) != copied + 3 || copied[3] != -1 || copied[4] != -1 ||
        ast::unique(repeated, repeated + 5) != repeated + 3)
        return 7;
    for (int index = 0; index != 3; ++index) {
        if (repeated[index] != seed + index || copied[index] != seed + index)
            return 8;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_reordering(int seed)
{
    ast::minstd_rand generator(static_cast<unsigned>(seed));
    const int source[] = {seed, seed + 1, seed + 2, seed + 3, seed + 4};
    const volatile int guard = -1;
    int sample[4] = {guard, guard, guard, guard};
    if (ast::sample(source, source + 5, sample, 3, generator) != sample + 3 || sample[3] != -1)
        return 1;
    unsigned mask = 0;
    for (int i = 0; i < 3; ++i) {
        const int index = sample[i] - seed;
        if (index < 0 || index >= 5 || (mask & (1u << index)) != 0)
            return 2;
        mask |= 1u << index;
    }
    int shuffled[] = {seed, seed + 1, seed + 2, seed + 3, seed + 4};
    ast::shuffle(shuffled, shuffled + 5, generator);
    mask = 0;
    for (int value : shuffled) {
        const int index = value - seed;
        if (index < 0 || index >= 5 || (mask & (1u << index)) != 0)
            return 3;
        mask |= 1u << index;
    }
    return mask == 31 ? 0 : 4;
}

}  // namespace asc_stl_standard_algorithm_test

#endif  // ASC_STL_TEST_STANDARD_ALGORITHM_SEMANTICS_H
