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

#include <asc/std/__algorithm/ranges_find_if_not.h>

#include <iostream>

namespace {

int g_failures = 0;

void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "[host][ranges_find_if_not] FAIL: " << label << '\n';
        ++g_failures;
    }
}

struct Item {
    int key;
    int value;
};

}  // namespace

int main()
{
    int data[5] = {2, 4, 5, 8, 10};

    // Negation semantics: first element that does NOT satisfy the predicate.
    auto first_odd = asc::std::ranges::find_if_not(data, [](int value) { return value % 2 == 0; });
    expect(first_odd == data + 2, "negation picks first non-matching");
    expect(first_odd == data + 2 && *first_odd == 5, "negated element value");

    // Iterator + sentinel overload.
    auto bounded = asc::std::ranges::find_if_not(data, data + 3, [](int value) { return value < 5; });
    expect(bounded == data + 2, "iterator+sentinel negation");

    // No element fails the predicate: returns the end iterator.
    int evens[4] = {2, 4, 6, 8};
    auto none = asc::std::ranges::find_if_not(evens, [](int value) { return value % 2 == 0; });
    expect(none == evens + 4, "all match returns end");

    // Projection is applied before the negated predicate.
    auto projected =
        asc::std::ranges::find_if_not(data, [](int digit) { return digit != 0; }, [](int value) { return value % 10; });
    expect(projected == data + 4, "projection negation hit");

    // Member-pointer projection over a custom type.
    Item items[4] = {{1, 10}, {2, 20}, {4, 40}, {8, 80}};
    auto member = asc::std::ranges::find_if_not(items, [](int key) { return key < 4; }, &Item::key);
    expect(member == items + 2, "member-pointer projection");
    expect(member == items + 2 && member->value == 40, "projected element content");

    // Complement property: find_if_not with pred == find_if with !pred over the same data.
    auto direct = asc::std::ranges::find_if(data, [](int value) { return value % 2 != 0; });
    expect(direct == first_odd, "find_if_not equals find_if of negated predicate");

    if (g_failures == 0) {
        std::cout << "[host][ranges_find_if_not] all checks passed" << std::endl;
    }
    return g_failures == 0 ? 0 : 1;
}
