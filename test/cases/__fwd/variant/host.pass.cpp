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

#include <asc/std/__fwd/variant.h>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][variant] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][variant] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // --- variant_npos: inline constexpr size_t = static_cast<size_t>(-1) ---
    expect_eq("variant_npos", asc::std::variant_npos, static_cast<size_t>(-1));
    expect_true("variant_npos == SIZE_MAX", asc::std::variant_npos == SIZE_MAX);
    expect_true("is_same<decltype(variant_npos), const size_t>",
        std::is_same<decltype(asc::std::variant_npos), const size_t>::value);

    // --- __variant_npos<T>: template variable = static_cast<T>(-1) ---
    expect_eq("__variant_npos<size_t>", asc::std::__variant_npos<size_t>, static_cast<size_t>(-1));
    expect_eq("__variant_npos<int>", asc::std::__variant_npos<int>, static_cast<int>(-1));
    expect_eq("__variant_npos<unsigned>", asc::std::__variant_npos<unsigned>, static_cast<unsigned>(-1));
    expect_eq("__variant_npos<long long>", asc::std::__variant_npos<long long>, static_cast<long long>(-1));

    // --- variant forward-declared as template; can form pointer to incomplete type ---
    {
        asc::std::variant<int, float, double>* p = nullptr;
        expect_true("variant<int,float,double>* decl ok", p == nullptr);
    }
    {
        asc::std::variant<char>* p = nullptr;
        expect_true("variant<char>* decl ok", p == nullptr);
    }
    {
        asc::std::variant<>* p = nullptr;
        expect_true("variant<>* decl ok", p == nullptr);
    }

    // --- variant_size forward-declared as template; can form pointer ---
    {
        using V = asc::std::variant<int, float>;
        asc::std::variant_size<V>* ps = nullptr;
        expect_true("variant_size<V>* decl ok", ps == nullptr);
    }

    // --- variant_alternative forward-declared as template; can form pointer ---
    {
        using V = asc::std::variant<int, float>;
        asc::std::variant_alternative<0, V>* pa0 = nullptr;
        asc::std::variant_alternative<1, V>* pa1 = nullptr;
        expect_true("variant_alternative<0,V>* decl ok", pa0 == nullptr);
        expect_true("variant_alternative<1,V>* decl ok", pa1 == nullptr);
    }

    return g_failures == 0 ? 0 : 1;
}
