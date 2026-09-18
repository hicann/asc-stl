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

#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_bool(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_nothrow_convertible] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct NothrowConv {
    operator int() noexcept
    {
        return 42;
    }
};

struct ThrowingConv {
    operator int() noexcept(false)
    {
        return 42;
    }
};

struct NothrowCopy {
    int v;
    NothrowCopy(int x) noexcept : v(x)  // NOLINT(runtime/explicit)
    {}
    NothrowCopy(const NothrowCopy&) noexcept = default;
};

struct ThrowingCopy {
    int v;
    ThrowingCopy(int x) : v(x)  // NOLINT(runtime/explicit)
    {}
    ThrowingCopy(const ThrowingCopy&) noexcept(false)
    {}
};

int main()
{
    // Basic arithmetic conversions (all noexcept)
    expect_bool("is_nothrow_convertible_v<int, double>", asc::std::is_nothrow_convertible_v<int, double>, true);
    expect_bool("is_nothrow_convertible_v<double, int>", asc::std::is_nothrow_convertible_v<double, int>, true);
    expect_bool("is_nothrow_convertible_v<int, long>", asc::std::is_nothrow_convertible_v<int, long>, true);
    expect_bool("is_nothrow_convertible_v<char, int>", asc::std::is_nothrow_convertible_v<char, int>, true);
    expect_bool("is_nothrow_convertible_v<int, int>", asc::std::is_nothrow_convertible_v<int, int>, true);
    expect_bool("is_nothrow_convertible_v<float, double>", asc::std::is_nothrow_convertible_v<float, double>, true);
    expect_bool("is_nothrow_convertible_v<bool, int>", asc::std::is_nothrow_convertible_v<bool, int>, true);
    expect_bool("is_nothrow_convertible_v<int, bool>", asc::std::is_nothrow_convertible_v<int, bool>, true);

    // void conversions
    expect_bool("is_nothrow_convertible_v<void, void>", asc::std::is_nothrow_convertible_v<void, void>, true);
    expect_bool("is_nothrow_convertible_v<int, void>", asc::std::is_nothrow_convertible_v<int, void>, false);
    expect_bool("is_nothrow_convertible_v<void, int>", asc::std::is_nothrow_convertible_v<void, int>, false);

    // Pointer conversions
    expect_bool("is_nothrow_convertible_v<int*, void*>", asc::std::is_nothrow_convertible_v<int*, void*>, true);
    expect_bool("is_nothrow_convertible_v<void*, int*>", asc::std::is_nothrow_convertible_v<void*, int*>, false);
    expect_bool("is_nothrow_convertible_v<int*, double*>", asc::std::is_nothrow_convertible_v<int*, double*>, false);
    expect_bool(
        "is_nothrow_convertible_v<int*, const int*>", asc::std::is_nothrow_convertible_v<int*, const int*>, true);
    expect_bool(
        "is_nothrow_convertible_v<const int*, int*>", asc::std::is_nothrow_convertible_v<const int*, int*>, false);

    // Reference conversions
    expect_bool("is_nothrow_convertible_v<int&, int>", asc::std::is_nothrow_convertible_v<int&, int>, true);
    expect_bool("is_nothrow_convertible_v<int, const int&>", asc::std::is_nothrow_convertible_v<int, const int&>, true);
    expect_bool("is_nothrow_convertible_v<int, int&>", asc::std::is_nothrow_convertible_v<int, int&>, false);

    // Custom conversion operators
    expect_bool(
        "is_nothrow_convertible_v<NothrowConv, int>", asc::std::is_nothrow_convertible_v<NothrowConv, int>, true);
    expect_bool(
        "is_nothrow_convertible_v<ThrowingConv, int>", asc::std::is_nothrow_convertible_v<ThrowingConv, int>, false);
    expect_bool(
        "is_nothrow_convertible_v<NothrowConv, double>", asc::std::is_nothrow_convertible_v<NothrowConv, double>, true);
    expect_bool("is_nothrow_convertible_v<ThrowingConv, double>",
        asc::std::is_nothrow_convertible_v<ThrowingConv, double>, false);

    // Copy construction noexcept-ness
    expect_bool("is_nothrow_convertible_v<NothrowCopy, NothrowCopy>",
        asc::std::is_nothrow_convertible_v<NothrowCopy, NothrowCopy>, true);
    expect_bool("is_nothrow_convertible_v<ThrowingCopy, ThrowingCopy>",
        asc::std::is_nothrow_convertible_v<ThrowingCopy, ThrowingCopy>, false);

    // Non-convertible types
    expect_bool(
        "is_nothrow_convertible_v<int, std::string>", asc::std::is_nothrow_convertible_v<int, std::string>, false);
    expect_bool(
        "is_nothrow_convertible_v<std::string, int>", asc::std::is_nothrow_convertible_v<std::string, int>, false);

    // const char* to std::string is convertible but NOT noexcept (can throw bad_alloc)
    expect_bool("is_nothrow_convertible_v<const char*, std::string>",
        asc::std::is_nothrow_convertible_v<const char*, std::string>, false);

    // Using struct form (::value)
    expect_bool(
        "is_nothrow_convertible<int,double>::value", asc::std::is_nothrow_convertible<int, double>::value, true);
    expect_bool("is_nothrow_convertible<void,void>::value", asc::std::is_nothrow_convertible<void, void>::value, true);
    expect_bool(
        "is_nothrow_convertible<int*,double*>::value", asc::std::is_nothrow_convertible<int*, double*>::value, false);
    expect_bool("is_nothrow_convertible<ThrowingConv,int>::value",
        asc::std::is_nothrow_convertible<ThrowingConv, int>::value, false);

    return g_failures == 0 ? 0 : 1;
}
