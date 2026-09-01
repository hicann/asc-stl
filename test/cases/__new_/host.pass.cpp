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

#include <asc/std/__new_>
#include <asc/std/__type_traits/is_same.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][__new_] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][__new_] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Test launder with constexpr int (mirrors the upstream launder test)
    static constexpr int gi = 5;
    expect_true("launder(&gi) == &gi", asc::std::launder(&gi) == &gi);

    const int* pi = &gi;
    expect_true("launder(pi) == pi", asc::std::launder(pi) == pi);

    // Test launder with constexpr float (mirrors the upstream launder test)
    static constexpr float gf = 8.0f;
    expect_true("launder(&gf) == &gf", asc::std::launder(&gf) == &gf);

    const float* pf = &gf;
    expect_true("launder(pf) == pf", asc::std::launder(pf) == pf);

    // Type checks: launder(T*) should return T* (mirrors the upstream launder test)
    expect_true("is_same<decltype(pi), decltype(launder(pi))>",
        asc::std::is_same<decltype(pi), decltype(asc::std::launder(pi))>::value);
    expect_true("is_same<decltype(pf), decltype(launder(pf))>",
        asc::std::is_same<decltype(pf), decltype(asc::std::launder(pf))>::value);

    // Test with mutable int pointer and verify dereferenced value
    int x = 42;
    int* px = &x;
    expect_true("launder(px) == px", asc::std::launder(px) == px);
    expect_eq("*launder(px)", *asc::std::launder(px), 42);

    // Test with mutable double pointer and verify dereferenced value
    double d = 3.14;
    double* pd = &d;
    expect_true("launder(pd) == pd", asc::std::launder(pd) == pd);
    expect_eq("*launder(pd)", *asc::std::launder(pd), 3.14);

    // Test with array element pointer
    int arr[3] = {10, 20, 30};
    expect_true("launder(&arr[1]) == &arr[1]", asc::std::launder(&arr[1]) == &arr[1]);
    expect_eq("*launder(&arr[1])", *asc::std::launder(&arr[1]), 20);

    // Test with volatile-qualified pointer type
    volatile int v = 99;
    volatile int* pv = &v;
    expect_true("launder(pv) == pv", asc::std::launder(pv) == pv);
    expect_true("is_same<volatile int*, decltype(launder(pv))>",
        asc::std::is_same<volatile int*, decltype(asc::std::launder(pv))>::value);

    // Verify noexcept
    expect_true("noexcept(launder(px))", noexcept(asc::std::launder(px)));

    return g_failures == 0 ? 0 : 1;
}
