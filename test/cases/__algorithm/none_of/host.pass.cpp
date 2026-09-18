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

#include <asc/std/__algorithm/none_of.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][none_of] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// 偶数谓词: 委托实现的另一种写法
struct is_even {
    constexpr bool matches(int value) const noexcept
    {
        return value % 2 == 0;
    }
    constexpr bool operator()(int value) const noexcept
    {
        return matches(value);
    }
};

int main()
{
    // All even → none_of = false
    {
        int ia[] = {2, 4, 6, 8};
        expect_eq("none_of({2,4,6,8}, is_even)", asc::std::none_of(ia, ia + 4, is_even()), false);
    }

    // Empty range → none_of = true
    {
        int ia[] = {2, 4, 6, 8};
        expect_eq("none_of(empty, is_even)", asc::std::none_of(ia, ia, is_even()), true);
    }

    // Mixed (some even) → none_of = false
    {
        int ia[] = {2, 4, 5, 8};
        expect_eq("none_of({2,4,5,8}, is_even)", asc::std::none_of(ia, ia + 4, is_even()), false);
    }

    // All odd → none_of = true
    {
        int ia[] = {1, 3, 5, 7};
        expect_eq("none_of({1,3,5,7}, is_even)", asc::std::none_of(ia, ia + 4, is_even()), true);
    }

    // {1, 3, 6, 7} → none_of = false (6 is even)
    {
        int ia[] = {1, 3, 6, 7};
        expect_eq("none_of({1,3,6,7}, is_even)", asc::std::none_of(ia, ia + 4, is_even()), false);
    }

    // Single element even → false
    {
        int ia[] = {2};
        expect_eq("none_of({2}, is_even)", asc::std::none_of(ia, ia + 1, is_even()), false);
    }

    // Single element odd → true
    {
        int ia[] = {1};
        expect_eq("none_of({1}, is_even)", asc::std::none_of(ia, ia + 1, is_even()), true);
    }

    // Lambda predicate: none negative → true
    {
        int ia[] = {1, 2, 3};
        auto is_negative = [](int v) { return v < 0; };
        expect_eq("none_of({1,2,3}, is_negative)", asc::std::none_of(ia, ia + 3, is_negative), true);
    }

    // Lambda predicate: some negative → false
    {
        int ia[] = {1, -2, 3};
        auto is_negative = [](int v) { return v < 0; };
        expect_eq("none_of({1,-2,3}, is_negative)", asc::std::none_of(ia, ia + 3, is_negative), false);
    }

    // Const data with const pointer
    {
        const int ia[] = {1, 3, 5, 7};
        expect_eq("none_of(const{1,3,5,7}, is_even)", asc::std::none_of(ia, ia + 4, is_even()), true);
    }

    return g_failures == 0 ? 0 : 1;
}
