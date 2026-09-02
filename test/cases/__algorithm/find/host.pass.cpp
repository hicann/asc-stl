/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/__algorithm/find.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][find] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}
struct Item {
    int key;
};
struct Key {
    constexpr int operator()(const Item& x) const noexcept
    {
        return x.key;
    }
};
int main()
{
    int values[] = {1, 4, 7, 4};
    expect_true("find(values, 7) == values+2", asc::std::find(values, values + 4, 7) == values + 2);
    expect_true("find(values, 9) == end", asc::std::find(values, values + 4, 9) == values + 4);
    Item items[] = {{2}, {5}, {8}};
    Key key;
    expect_true("__find_impl(items, 5, key) == items+1", asc::std::__find_impl(items, items + 3, 5, key) == items + 1);

    return g_failures == 0 ? 0 : 1;
}
