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

#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_nothrow_assignable] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// A type with a noexcept copy assignment
struct NoexceptAssignable {
    int v;
    NoexceptAssignable& operator=(const NoexceptAssignable&) noexcept
    {
        v = 0;
        return *this;
    }
};

// A type with a potentially-throwing copy assignment
struct ThrowingAssignable {
    int v;
    ThrowingAssignable& operator=(const ThrowingAssignable&)
    {
        v = 0;
        return *this;
    }
};

// A type with deleted assignment
struct NoAssignable {
    NoAssignable& operator=(const NoAssignable&) = delete;
};

int main()
{
    // --- Scalar types ---
    // Assigning to int& from int is noexcept
    expect_true("is_nothrow_assignable<int&, int>::value", asc::std::is_nothrow_assignable<int&, int>::value, true);
    expect_true("is_nothrow_assignable_v<int&, int>", asc::std::is_nothrow_assignable_v<int&, int>, true);

    // Assigning to int& from int& is noexcept
    expect_true("is_nothrow_assignable<int&, int&>::value", asc::std::is_nothrow_assignable<int&, int&>::value, true);

    // Assigning to int& from double is noexcept
    expect_true(
        "is_nothrow_assignable<int&, double>::value", asc::std::is_nothrow_assignable<int&, double>::value, true);

    // --- Not-assignable cases ---
    // Cannot assign to an rvalue int -> not assignable -> false
    expect_true("is_nothrow_assignable<int, int>::value", asc::std::is_nothrow_assignable<int, int>::value, false);

    // void is not assignable -> false
    expect_true("is_nothrow_assignable<void, int>::value", asc::std::is_nothrow_assignable<void, int>::value, false);

    // --- User-defined types ---
    // Type with noexcept assignment operator
    expect_true("is_nothrow_assignable<NoexceptAssignable&, const NoexceptAssignable&>::value",
        asc::std::is_nothrow_assignable<NoexceptAssignable&, const NoexceptAssignable&>::value, true);
    expect_true("is_nothrow_assignable_v<NoexceptAssignable&, const NoexceptAssignable&>",
        asc::std::is_nothrow_assignable_v<NoexceptAssignable&, const NoexceptAssignable&>, true);

    // Type with throwing assignment operator
    expect_true("is_nothrow_assignable<ThrowingAssignable&, const ThrowingAssignable&>::value",
        asc::std::is_nothrow_assignable<ThrowingAssignable&, const ThrowingAssignable&>::value, false);
    expect_true("is_nothrow_assignable_v<ThrowingAssignable&, const ThrowingAssignable&>",
        asc::std::is_nothrow_assignable_v<ThrowingAssignable&, const ThrowingAssignable&>, false);

    // Type with deleted assignment -> not assignable -> false
    expect_true("is_nothrow_assignable<NoAssignable&, const NoAssignable&>::value",
        asc::std::is_nothrow_assignable<NoAssignable&, const NoAssignable&>::value, false);

    // --- Pointer types ---
    expect_true("is_nothrow_assignable<int*&, int*>::value", asc::std::is_nothrow_assignable<int*&, int*>::value, true);

    expect_true("is_nothrow_assignable<char&, char>::value", asc::std::is_nothrow_assignable<char&, char>::value, true);

    return g_failures == 0 ? 0 : 1;
}
