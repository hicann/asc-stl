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

#include <asc/__fwd/random.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][random] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][random] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Verify __feistel_bijection is declared in asc namespace
    expect_true("asc::__feistel_bijection is declared",
        std::is_same<asc::__feistel_bijection, asc::__feistel_bijection>::value);

    // Verify random_bijection default _IndexType is asc::std::uint64_t
    expect_true("random_bijection default _IndexType == asc::std::uint64_t",
        std::is_same<asc::random_bijection<>,
            asc::random_bijection<asc::std::uint64_t, asc::__feistel_bijection>>::value);

    // Verify random_bijection with explicit uint64_t matches default
    expect_true("random_bijection<uint64_t> == random_bijection<>",
        std::is_same<asc::random_bijection<asc::std::uint64_t>, asc::random_bijection<>>::value);

    // Verify random_bijection with uint32_t differs from default
    expect_true("random_bijection<uint32_t> != random_bijection<>",
        !std::is_same<asc::random_bijection<asc::std::uint32_t>, asc::random_bijection<>>::value);

    return g_failures == 0 ? 0 : 1;
}
