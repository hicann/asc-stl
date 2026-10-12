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

#include <asc/std/__algorithm/ranges_find_if.h>

#include <iostream>

namespace {

int g_failures = 0;

void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "[host][ranges_find_if] FAIL: " << label << '\n';
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
    int data[5] = {3, 7, 2, 9, 4};

    // Iterator + sentinel overload: first element greater than 5.
    auto hit_iter = asc::std::ranges::find_if(data, data + 5, [](int value) { return value > 5; });
    expect(hit_iter == data + 1, "iterator+sentinel hit");

    // Range overload: first element greater than 8.
    auto hit_range = asc::std::ranges::find_if(data, [](int value) { return value > 8; });
    expect(hit_range == data + 3, "range overload hit");

    // Miss returns the end iterator.
    auto miss = asc::std::ranges::find_if(data, [](int) { return false; });
    expect(miss == data + 5, "miss returns end");

    // Empty range never matches.
    auto empty = asc::std::ranges::find_if(data, data, [](int) { return true; });
    expect(empty == data, "empty range returns first");

    // Projection is applied before the predicate.
    auto projected =
        asc::std::ranges::find_if(data, [](int digit) { return digit == 2; }, [](int value) { return value % 10; });
    expect(projected == data + 2, "projection hit");

    // Iterator overload with an explicit projection.
    auto projected_iter = asc::std::ranges::find_if(
        data + 1, data + 5, [](int digit) { return digit == 9; }, [](int v) { return v % 10; });
    expect(projected_iter == data + 3, "iterator overload with projection");

    // Member-pointer projection over a custom type.
    Item items[4] = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};
    auto member = asc::std::ranges::find_if(items, [](int key) { return key == 3; }, &Item::key);
    expect(member == items + 2, "member-pointer projection");
    expect(member == items + 2 && member->value == 30, "projected element content");

    if (g_failures == 0) {
        std::cout << "[host][ranges_find_if] all checks passed" << std::endl;
    }
    return g_failures == 0 ? 0 : 1;
}
