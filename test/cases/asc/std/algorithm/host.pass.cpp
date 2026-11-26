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

#include <asc/std/algorithm>

#include "support/v1_algorithm_semantics.h"

struct record {
    int key;
    int order;
};
struct record_less {
    constexpr bool operator()(const record& left, const record& right) const
    {
        return left.key < right.key;
    }
};
struct descending {
    constexpr bool operator()(int left, int right) const
    {
        return left > right;
    }
};

int main()
{
    if (asc_stl_v1_algorithm_test::evaluate() != 0)
        return 12;
    int values[] = {5, 1, 3, 3, 2, 4, 0};
    asc::std::sort(values, values + 7);
    for (int index = 0; index < 7; ++index) {
        if (values[index] != index - (index > 3 ? 1 : 0))
            return 1;
    }
    int reversed[] = {9, 8, 7, 6, 5, 4};
    asc::std::nth_element(reversed, reversed + 2, reversed + 6);
    if (reversed[2] != 6)
        return 2;
    int partial[] = {8, 2, 7, 1, 6, 3};
    asc::std::partial_sort(partial, partial + 3, partial + 6);
    if (partial[0] != 1 || partial[1] != 2 || partial[2] != 3)
        return 3;
    int copied[4] = {-1, -1, -1, 77};
    auto copied_end = asc::std::partial_sort_copy(partial, partial + 6, copied, copied + 3);
    if (copied_end != copied + 3 || copied[3] != 77)
        return 4;
    record stable[] = {{2, 0}, {1, 1}, {2, 2}, {1, 3}, {2, 4}};
    asc::std::stable_sort(stable, stable + 5, record_less{});
    if (stable[0].order != 1 || stable[1].order != 3 || stable[2].order != 0 || stable[4].order != 4)
        return 5;
    record partitioned[] = {{1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}};
    auto boundary = asc::std::stable_partition(
        partitioned, partitioned + 5, [](const record& value) { return (value.key & 1) == 0; });
    if (boundary != partitioned + 2 || partitioned[0].order != 1 || partitioned[1].order != 3 ||
        partitioned[2].order != 0 || partitioned[4].order != 4)
        return 6;
    record merged[] = {{1, 0}, {2, 1}, {2, 2}, {1, 3}, {2, 4}, {3, 5}};
    asc::std::inplace_merge(merged, merged + 3, merged + 6, record_less{});
    if (merged[0].order != 0 || merged[1].order != 3 || merged[2].order != 1 || merged[3].order != 2 ||
        merged[4].order != 4)
        return 7;
    int singleton[] = {1};
    asc::std::sort(singleton, singleton + 1);
    asc::std::sort(singleton, singleton);  // NOLINT(build/include_what_you_use)
    int custom[] = {1, 4, 2, 5, 3};
    asc::std::sort(custom, custom + 5, descending{});  // NOLINT(build/include_what_you_use)
    if (custom[0] != 5 || custom[4] != 1)
        return 8;
    int custom_nth[] = {1, 4, 2, 5, 3};
    asc::std::nth_element(custom_nth, custom_nth + 2, custom_nth + 5, descending{});
    if (custom_nth[2] != 3 || custom_nth[0] < 3 || custom_nth[1] < 3 || custom_nth[3] > 3 || custom_nth[4] > 3)
        return 9;
    int short_input[] = {6, 2};
    int wide_output[] = {-1, -1, 71, 72};
    const auto wide_end = asc::std::partial_sort_copy(short_input, short_input + 2, wide_output, wide_output + 4);
    if (wide_end != wide_output + 2 || wide_output[0] != 2 || wide_output[1] != 6 || wide_output[2] != 71 ||
        wide_output[3] != 72)
        return 10;
    const auto select_all = [](int) { return true; };
    if (asc::std::stable_partition(singleton, singleton, select_all) != singleton) {
        return 11;
    }
    asc::std::partial_sort(singleton, singleton, singleton);
    asc::std::inplace_merge(singleton, singleton, singleton);
    return 0;
}
