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

#include <asc/std/__type_traits/is_copy_constructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_bool(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_copy_constructible] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Copyable {
    int x;
};

struct ExplicitlyDeleted {
    ExplicitlyDeleted()
    {}
    ExplicitlyDeleted(const ExplicitlyDeleted&) = delete;
};

struct MoveOnly {
    MoveOnly()
    {}
    MoveOnly(MoveOnly&&)
    {}
};

int main()
{
    // Basic scalar types — copy constructible
    expect_bool("is_copy_constructible<int>::value", asc::std::is_copy_constructible<int>::value, true);
    expect_bool("is_copy_constructible_v<int>", asc::std::is_copy_constructible_v<int>, true);
    expect_bool("is_copy_constructible<double>::value", asc::std::is_copy_constructible<double>::value, true);
    expect_bool("is_copy_constructible<float>::value", asc::std::is_copy_constructible<float>::value, true);
    expect_bool("is_copy_constructible<char>::value", asc::std::is_copy_constructible<char>::value, true);
    expect_bool("is_copy_constructible<bool>::value", asc::std::is_copy_constructible<bool>::value, true);
    expect_bool("is_copy_constructible<long long>::value", asc::std::is_copy_constructible<long long>::value, true);

    // Pointer types — copy constructible
    expect_bool("is_copy_constructible<int*>::value", asc::std::is_copy_constructible<int*>::value, true);
    expect_bool(
        "is_copy_constructible<int(*)(int)>::value", asc::std::is_copy_constructible<int (*)(int)>::value, true);

    // Reference types — copy constructible
    expect_bool("is_copy_constructible<int&>::value", asc::std::is_copy_constructible<int&>::value, true);
    expect_bool("is_copy_constructible<const int&>::value", asc::std::is_copy_constructible<const int&>::value, true);

    // const-qualified scalar — copy constructible
    expect_bool("is_copy_constructible<const int>::value", asc::std::is_copy_constructible<const int>::value, true);

    // User-defined copyable type
    expect_bool("is_copy_constructible<Copyable>::value", asc::std::is_copy_constructible<Copyable>::value, true);
    expect_bool("is_copy_constructible_v<Copyable>", asc::std::is_copy_constructible_v<Copyable>, true);

    // Non-copyable types
    expect_bool("is_copy_constructible<ExplicitlyDeleted>::value",
        asc::std::is_copy_constructible<ExplicitlyDeleted>::value, false);
    expect_bool(
        "is_copy_constructible_v<ExplicitlyDeleted>", asc::std::is_copy_constructible_v<ExplicitlyDeleted>, false);
    expect_bool("is_copy_constructible<MoveOnly>::value", asc::std::is_copy_constructible<MoveOnly>::value, false);

    // void — not copy constructible
    expect_bool("is_copy_constructible<void>::value", asc::std::is_copy_constructible<void>::value, false);
    expect_bool("is_copy_constructible_v<void>", asc::std::is_copy_constructible_v<void>, false);

    // Array types — not copy constructible
    expect_bool("is_copy_constructible<int[3]>::value", asc::std::is_copy_constructible<int[3]>::value, false);

    // Function type — not copy constructible
    expect_bool("is_copy_constructible<int(int)>::value", asc::std::is_copy_constructible<int(int)>::value, false);

    return g_failures == 0 ? 0 : 1;
}
