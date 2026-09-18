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

#include <asc/std/__algorithm/any_of.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][any_of] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// 偶数谓词: 按位与判别, 与取模写法区分
struct multiple_of_two {
    constexpr bool operator()(int value) const noexcept
    {
        return (value & 1) == 0;
    }
};

int main()
{
    {
        int ia[] = {2, 4, 6, 8};
        expect_eq("any_of(ia, ia+4, multiple_of_two)", asc::std::any_of(ia, ia + 4, multiple_of_two()), true);
        expect_eq("any_of(ia, ia, multiple_of_two)", asc::std::any_of(ia, ia, multiple_of_two()), false);
    }
    {
        int ia[] = {2, 4, 5, 8};
        expect_eq("any_of(ia, ia+4, multiple_of_two)", asc::std::any_of(ia, ia + 4, multiple_of_two()), true);
        expect_eq("any_of(ia, ia, multiple_of_two)", asc::std::any_of(ia, ia, multiple_of_two()), false);
    }
    {
        int ia[] = {1, 3, 5, 7};
        expect_eq("any_of(ia, ia+4, multiple_of_two)", asc::std::any_of(ia, ia + 4, multiple_of_two()), false);
        expect_eq("any_of(ia, ia, multiple_of_two)", asc::std::any_of(ia, ia, multiple_of_two()), false);
    }
    {
        int ia[] = {1, 3, 5, 8};
        auto pred = [](int x) { return x > 5; };
        expect_eq("any_of(ia, ia+4, >5)", asc::std::any_of(ia, ia + 4, pred), true);
    }

    return g_failures == 0 ? 0 : 1;
}
