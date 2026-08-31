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

#include <asc/std/__cstddef/types.h>
#include <iostream>
#include <type_traits>
#include <cstddef>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][types] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][types] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    expect_true("is_same<asc::std::size_t, ::size_t>", std::is_same<asc::std::size_t, ::size_t>::value);
    expect_true("is_same<asc::std::ptrdiff_t, ::ptrdiff_t>", std::is_same<asc::std::ptrdiff_t, ::ptrdiff_t>::value);
    expect_true(
        "is_same<asc::std::nullptr_t, decltype(nullptr)>", std::is_same<asc::std::nullptr_t, decltype(nullptr)>::value);
    expect_true("alignof(asc::std::max_align_t) >= alignof(long double)",
        alignof(asc::std::max_align_t) >= alignof(long double));
    expect_true("alignof(asc::std::max_align_t) >= alignof(double)", alignof(asc::std::max_align_t) >= alignof(double));
    expect_true(
        "alignof(asc::std::max_align_t) >= alignof(long long)", alignof(asc::std::max_align_t) >= alignof(long long));

    asc::std::size_t s = 42;
    expect_eq("size_t var = 42", s, static_cast<::size_t>(42));

    int arr[10];
    asc::std::ptrdiff_t pdiff = &arr[5] - &arr[0];
    expect_eq("ptrdiff_t ptr diff", pdiff, static_cast<::ptrdiff_t>(5));

    asc::std::nullptr_t np = nullptr;
    expect_true("nullptr_t == nullptr", np == nullptr);

    return g_failures == 0 ? 0 : 1;
}
