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
#include <algorithm>
#include <forward_list>

#include "../../../../../support/b020_semantics.h"
#include "support/binary_search_regressions.h"

namespace {
struct CountingRange {
    asc::std::int64_t offset;
    constexpr asc::std::int64_t operator[](asc::std::int32_t index) const
    {
        return offset + index;
    }
    constexpr CountingRange operator+(asc::std::int32_t index) const
    {
        return {offset + index};
    }
};
struct WideLess {
    constexpr bool operator()(asc::std::int64_t lhs, asc::std::int64_t rhs) const
    {
        return lhs < rhs;
    }
};

bool check_large_indexed_ranges()
{
    // Virtual elements exercise the 32-bit limit without allocating a huge array.
    constexpr asc::std::int32_t lengths[] = {1073741823, 1073741824, 1073741825, 2147483646, 2147483647};
    for (auto length : lengths) {
        const asc::std::int64_t queries[] = {
            -1, 0, 1, length / 2, length - 1, length, static_cast<asc::std::int64_t>(length) + 1};
        for (auto query : queries) {
            const auto lower = query < 0 ? 0 : query > length ? length : query;
            const auto upper = query < 0 ? 0 : query >= length ? length : query + 1;
            WideLess comp;
            asc::std::identity projection;
            if (asc::std::__lower_bound_indexed(CountingRange{0}, length, query, comp, projection).offset != lower ||
                asc::std::__upper_bound_indexed(CountingRange{0}, length, query, comp, projection).offset != upper) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace

int main()
{
    if (asc_stl_b020_test::evaluate_mutating_algorithms() != 0) {
        return 1;
    }
    int ascending[257]{};
    int descending[257]{};
    for (int i = 0; i < 257; ++i) {
        ascending[i] = i / 3 - 20;
        descending[i] = 100 - i / 3;
    }
    for (int length = 0; length <= 257; ++length) {
        if (asc_stl_binary_search_test::check_range(ascending, length, asc_stl_binary_search_test::Less{}) != 0 ||
            asc_stl_binary_search_test::check_range(descending, length, asc_stl_binary_search_test::Greater{}) != 0) {
            return 2;
        }
    }
    std::forward_list<int> values{-4, -1, 0, 0, 7, 12};
    for (int query = -5; query <= 13; ++query) {
        if (asc::std::lower_bound(values.begin(), values.end(), query) !=
                std::lower_bound(values.begin(), values.end(), query) ||
            asc::std::upper_bound(values.begin(), values.end(), query) !=
                std::upper_bound(values.begin(), values.end(), query)) {
            return 3;
        }
    }
    return check_large_indexed_ranges() ? 0 : 4;
}
