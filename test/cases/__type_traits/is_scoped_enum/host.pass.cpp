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

#include <asc/std/__type_traits/is_scoped_enum.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_scoped_enum] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Scoped enums
enum class ScopedEnum { A, B, C };
enum class ScopedEnumInt : int { X, Y, Z };
enum class ScopedEnumUInt : unsigned int { U, V, W };
enum class ScopedEnumEmpty {};

// Unscoped enums
enum UnscopedEnum { UA, UB, UC };
enum UnscopedEnumInt : int { IA, IB, IC };

// Non-enum types
struct TestStruct {};
class TestClass {};
union TestUnion {};

int main()
{
    // Scoped enums -> true
    expect_eq("is_scoped_enum_v<ScopedEnum>", asc::std::is_scoped_enum_v<ScopedEnum>, true);
    expect_eq("is_scoped_enum_v<ScopedEnumInt>", asc::std::is_scoped_enum_v<ScopedEnumInt>, true);
    expect_eq("is_scoped_enum_v<ScopedEnumUInt>", asc::std::is_scoped_enum_v<ScopedEnumUInt>, true);
    expect_eq("is_scoped_enum_v<ScopedEnumEmpty>", asc::std::is_scoped_enum_v<ScopedEnumEmpty>, true);

    // CV-qualified scoped enums -> true
    expect_eq("is_scoped_enum_v<const ScopedEnum>", asc::std::is_scoped_enum_v<const ScopedEnum>, true);
    expect_eq("is_scoped_enum_v<volatile ScopedEnum>", asc::std::is_scoped_enum_v<volatile ScopedEnum>, true);

    // Unscoped enums -> false
    expect_eq("is_scoped_enum_v<UnscopedEnum>", asc::std::is_scoped_enum_v<UnscopedEnum>, false);
    expect_eq("is_scoped_enum_v<UnscopedEnumInt>", asc::std::is_scoped_enum_v<UnscopedEnumInt>, false);

    // Non-enum types -> false
    expect_eq("is_scoped_enum_v<int>", asc::std::is_scoped_enum_v<int>, false);
    expect_eq("is_scoped_enum_v<float>", asc::std::is_scoped_enum_v<float>, false);
    expect_eq("is_scoped_enum_v<double>", asc::std::is_scoped_enum_v<double>, false);
    expect_eq("is_scoped_enum_v<bool>", asc::std::is_scoped_enum_v<bool>, false);
    expect_eq("is_scoped_enum_v<char>", asc::std::is_scoped_enum_v<char>, false);
    expect_eq("is_scoped_enum_v<void>", asc::std::is_scoped_enum_v<void>, false);
    expect_eq("is_scoped_enum_v<TestStruct>", asc::std::is_scoped_enum_v<TestStruct>, false);
    expect_eq("is_scoped_enum_v<TestClass>", asc::std::is_scoped_enum_v<TestClass>, false);
    expect_eq("is_scoped_enum_v<TestUnion>", asc::std::is_scoped_enum_v<TestUnion>, false);
    expect_eq("is_scoped_enum_v<int*>", asc::std::is_scoped_enum_v<int*>, false);

    // Struct form (::value)
    expect_eq("is_scoped_enum<ScopedEnum>::value", asc::std::is_scoped_enum<ScopedEnum>::value, true);
    expect_eq("is_scoped_enum<ScopedEnumInt>::value", asc::std::is_scoped_enum<ScopedEnumInt>::value, true);
    expect_eq("is_scoped_enum<UnscopedEnum>::value", asc::std::is_scoped_enum<UnscopedEnum>::value, false);
    expect_eq("is_scoped_enum<int>::value", asc::std::is_scoped_enum<int>::value, false);

    // Compile-time checks
    static_assert(asc::std::is_scoped_enum<ScopedEnum>::value, "ScopedEnum should be a scoped enum");
    static_assert(!asc::std::is_scoped_enum<UnscopedEnum>::value, "UnscopedEnum should not be a scoped enum");
    static_assert(!asc::std::is_scoped_enum<int>::value, "int should not be a scoped enum");

    return g_failures == 0 ? 0 : 1;
}
