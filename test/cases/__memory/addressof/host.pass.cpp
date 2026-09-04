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

#include <asc/std/__memory/addressof.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][addressof] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][addressof] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Type that overloads operator& to return something other than its own address
struct Overloaded {
    int val;
    int* operator&()  // NOLINT(runtime/operator)
    {
        return nullptr;
    }
};

int main()
{
    // Basic: addressof returns the same address as built-in & for int
    {
        int x = 42;
        int* p = asc::std::addressof(x);
        expect_true("addressof(x) == &x", p == &x);
        expect_eq("*addressof(x)", *p, 42);
    }

    // Works with float
    {
        float f = 3.0f;
        float* p = asc::std::addressof(f);
        expect_true("addressof(f) == &f", p == &f);
        expect_eq("*addressof(f)", *p, 3.0f);
    }

    // Modify through pointer returned by addressof
    {
        int x = 10;
        *asc::std::addressof(x) = 99;
        expect_eq("modify via addressof", x, 99);
    }

    // Works with const objects
    {
        const int c = 55;
        const int* p = asc::std::addressof(c);
        expect_true("addressof(const) == &c", p == &c);
        expect_eq("*addressof(const)", *p, 55);
    }

    // Works with type that overloads operator&
    {
        Overloaded obj{123};
        // &obj returns nullptr due to overloaded operator&
        expect_true("&obj == nullptr (overloaded)", &obj == nullptr);
        // addressof returns the true address
        Overloaded* p = asc::std::addressof(obj);
        expect_true("addressof(obj) != nullptr", p != nullptr);
        expect_eq("addressof(obj)->val", p->val, 123);
    }

    // addressof returns non-null for valid objects
    {
        double d = 2.5;
        expect_true("addressof(d) is a valid pointer", asc::std::addressof(d) == &d);
    }

    return g_failures == 0 ? 0 : 1;
}
