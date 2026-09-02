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

#include <asc/std/__algorithm/all_of.h>
#include <iostream>
#include <vector>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    const bool ok = (got == expected);
    std::cout << "[host][all_of] " << expr << " => " << (got ? "true" : "false") << " (want "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// 偶数谓词: 以取模判别
struct is_even {
    constexpr bool operator()(const int& value) const noexcept
    {
        return (value % 2) == 0;
    }
};

int main()
{
    // All even: should be true
    {
        int ia[] = {2, 4, 6, 8};
        expect_eq("all_of(ia, ia+4, is_even) [all even]", asc::std::all_of(ia, ia + 4, is_even{}), true);
    }

    // One odd element: should be false
    {
        int ib[] = {2, 4, 5, 8};
        expect_eq("all_of(ib, ib+4, is_even) [has odd]", asc::std::all_of(ib, ib + 4, is_even{}), false);
    }

    // Empty range: should be true (vacuous truth)
    {
        int ic[] = {1, 3, 5};
        expect_eq("all_of(ic, ic, is_even) [empty range]", asc::std::all_of(ic, ic, is_even{}), true);
    }

    // Single element, satisfies predicate
    {
        int id[] = {42};
        expect_eq("all_of(id, id+1, is_even) [single even]", asc::std::all_of(id, id + 1, is_even{}), true);
    }

    // Single element, does not satisfy predicate
    {
        int ie[] = {7};
        expect_eq("all_of(ie, ie+1, is_even) [single odd]", asc::std::all_of(ie, ie + 1, is_even{}), false);
    }

    // Lambda predicate: all positive
    {
        int if_[] = {1, 2, 3, 4, 5};
        expect_eq("all_of(if_, if_+5, positive) [all positive]",
            asc::std::all_of(if_, if_ + 5, [](const int& v) { return v > 0; }), true);
    }

    // Lambda predicate: not all positive
    {
        int ig[] = {1, -2, 3, 4, 5};
        expect_eq("all_of(ig, ig+5, positive) [has negative]",
            asc::std::all_of(ig, ig + 5, [](const int& v) { return v > 0; }), false);
    }

    // Using std::vector iterators
    {
        std::vector<int> vh = {10, 20, 30, 40};
        expect_eq("all_of(vec, positive) [vector all positive]",
            asc::std::all_of(vh.begin(), vh.end(), [](const int& v) { return v > 0; }), true);
    }

    // Using std::vector with a failing predicate
    {
        std::vector<int> vh = {10, 0, 30, 40};
        expect_eq("all_of(vec, positive) [vector has zero]",
            asc::std::all_of(vh.begin(), vh.end(), [](const int& v) { return v > 0; }), false);
    }

    return g_failures == 0 ? 0 : 1;
}
