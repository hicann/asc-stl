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

#include <asc/std/__new/launder.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][launder] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][launder] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Basic: launder returns the same pointer value
    {
        int x = 42;
        int* p = &x;
        int* laundered = asc::std::launder(p);
        expect_true("launder(&x) == &x", laundered == &x);
        expect_eq("*launder(&x)", *laundered, 42);
    }

    // With const pointer
    {
        const int x = 99;
        const int* p = &x;
        const int* laundered = asc::std::launder(p);
        expect_true("launder(const &x) == &x", laundered == &x);
        expect_eq("*launder(const &x)", *laundered, 99);
    }

    // With float
    {
        float f = 3.14f;
        float* p = &f;
        float* laundered = asc::std::launder(p);
        expect_true("launder(&f) == &f", laundered == &f);
        expect_eq("*launder(&f)", *laundered, 3.14f);
    }

    // launder returns a usable pointer: modify through laundered pointer
    {
        int x = 10;
        *asc::std::launder(&x) = 20;
        expect_eq("after *launder(&x)=20, x", x, 20);
    }

    // Nullptr check
    {
        int* p = nullptr;
        int* laundered = asc::std::launder(p);
        expect_true("launder(nullptr) == nullptr", laundered == nullptr);
    }

    return g_failures == 0 ? 0 : 1;
}
