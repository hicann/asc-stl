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

#include <asc/std/__fwd/allocator.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][allocator] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][allocator] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][allocator] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // Verify asc::std::allocator is forward-declared and usable as a type
    // (can form pointers/references to it)
    using A = asc::std::allocator<int>;
    A* p = nullptr;
    (void)p;

    // Verify __is_asc_std_allocator_v trait: true for asc::std::allocator<T>
    expect_true("__is_asc_std_allocator_v<asc::std::allocator<int>>",
        asc::std::__is_asc_std_allocator_v<asc::std::allocator<int>>);
    expect_true("__is_asc_std_allocator_v<asc::std::allocator<double>>",
        asc::std::__is_asc_std_allocator_v<asc::std::allocator<double>>);
    expect_true("__is_asc_std_allocator_v<asc::std::allocator<char>>",
        asc::std::__is_asc_std_allocator_v<asc::std::allocator<char>>);

    // Verify __is_asc_std_allocator_v trait: false for non-allocator types
    expect_false("__is_asc_std_allocator_v<int>", asc::std::__is_asc_std_allocator_v<int>);
    expect_false("__is_asc_std_allocator_v<double>", asc::std::__is_asc_std_allocator_v<double>);
    expect_false("__is_asc_std_allocator_v<void>", asc::std::__is_asc_std_allocator_v<void>);

    // Verify __is_asc_std_allocator_v is false for std::allocator (host std, not asc::std)
    expect_false(
        "__is_asc_std_allocator_v<std::allocator<int>>", asc::std::__is_asc_std_allocator_v<std::allocator<int>>);

    return g_failures == 0 ? 0 : 1;
}
