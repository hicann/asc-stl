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

#include <asc/std/__iterator/iter_swap.h>
#include "support/b010_semantics.h"

namespace readonly_rows {
struct cursor {
    using value_type = int;
    using difference_type = long;
    using pointer = const int*;
    using reference = const int&;
    using iterator_category = asc::std::input_iterator_tag;
    int* row;
    int* exchanges;

    const int& operator*() const noexcept
    {
        return *row;
    }
    friend void iter_swap(const cursor& left, const cursor& right) noexcept
    {
        int old = *left.row;
        *left.row = *right.row;
        *right.row = old;
        ++*left.exchanges;
    }
};
static_assert(asc::std::indirectly_swappable<cursor>);
static_assert(!asc::std::indirectly_writable<cursor, int>);
static_assert(
    noexcept(asc::std::ranges::iter_swap(asc::std::declval<const cursor&>(), asc::std::declval<const cursor&>())));

int evaluate()
{
    int rows[] = {3, 7};
    int exchanges = 0;
    const cursor first{rows, &exchanges}, second{rows + 1, &exchanges};
    asc::std::ranges::iter_swap(first, second);
    return rows[0] == 7 && rows[1] == 3 && exchanges == 1 ? 0 : 1;
}
}  // namespace readonly_rows

int main()
{
    const int basic = asc_stl_b010_test::evaluate_runtime();
    return basic != 0 ? basic : readonly_rows::evaluate();
}
