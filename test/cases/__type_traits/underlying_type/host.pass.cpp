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

#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][underlying_type] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][underlying_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// relaxed_underlying_type: if T is an enum, yields underlying_type_t<T>; otherwise yields T
template <class T, class = void>
struct relaxed_underlying_type {
    using type = T;
};

template <class T>
struct relaxed_underlying_type<T, asc::std::void_t<asc::std::underlying_type_t<T>>> {
    using type = asc::std::underlying_type_t<T>;
};

enum Enum1 : short { E1 = 0, E2 = 1, E3 = 64, E4 = 78 };

enum class Enum2 : long { C1 = 0, C2 = 1, C3 = 64, C4 = 78 };

int main()
{
    // Test 1: underlying_type_t for unscoped enum with short underlying type
    expect_true("is_same<underlying_type_t<Enum1>, short>",
        (asc::std::is_same<asc::std::underlying_type_t<Enum1>, short>::value));

    // Test 2: underlying_type_t for scoped enum with long underlying type
    expect_true("is_same<underlying_type_t<Enum2>, long>",
        (asc::std::is_same<asc::std::underlying_type_t<Enum2>, long>::value));

    // Test 3: relaxed_underlying_type for Enum1 yields short
    expect_true("is_same<relaxed_underlying_type<Enum1>::type, short>",
        (asc::std::is_same<relaxed_underlying_type<Enum1>::type, short>::value));

    // Test 4: relaxed_underlying_type for Enum2 yields long
    expect_true("is_same<relaxed_underlying_type<Enum2>::type, long>",
        (asc::std::is_same<relaxed_underlying_type<Enum2>::type, long>::value));

    // Test 5: relaxed_underlying_type for non-enum int yields int
    expect_true("is_same<relaxed_underlying_type<int>::type, int>",
        (asc::std::is_same<relaxed_underlying_type<int>::type, int>::value));

    // Test 6: Cast enum value to underlying type and check numeric value
    {
        short val = static_cast<asc::std::underlying_type_t<Enum1>>(E3);
        expect_eq("static_cast<underlying_type_t<Enum1>>(E3)", val, static_cast<short>(64));
    }

    // Test 7: Cast scoped enum value to underlying type and check numeric value
    {
        long val = static_cast<asc::std::underlying_type_t<Enum2>>(Enum2::C4);
        expect_eq("static_cast<underlying_type_t<Enum2>>(C4)", val, static_cast<long>(78));
    }

    // Test 8: underlying_type_t<Enum1> used in arithmetic
    {
        asc::std::underlying_type_t<Enum1> sum =
            static_cast<asc::std::underlying_type_t<Enum1>>(E1) + static_cast<asc::std::underlying_type_t<Enum1>>(E2);
        expect_eq("underlying_type_t<Enum1>(E1) + underlying_type_t<Enum1>(E2)", sum, static_cast<short>(1));
    }

    // Test 9: is_enum_v checks
    expect_true("is_enum_v<Enum1>", asc::std::is_enum_v<Enum1>);
    expect_true("is_enum_v<Enum2>", asc::std::is_enum_v<Enum2>);
    expect_true("!is_enum_v<int>", !asc::std::is_enum_v<int>);

    // Test 10: underlying_type_t for a char-enum
    enum EnumChar : char { EC_A = 'a', EC_B = 'b' };
    expect_true("is_same<underlying_type_t<EnumChar>, char>",
        (asc::std::is_same<asc::std::underlying_type_t<EnumChar>, char>::value));

    // Test 11: underlying_type_t for unsigned int enum
    enum EnumUInt : unsigned int { EU0 = 0u, EU1 = 1u };
    expect_true("is_same<underlying_type_t<EnumUInt>, unsigned int>",
        (asc::std::is_same<asc::std::underlying_type_t<EnumUInt>, unsigned int>::value));

    return g_failures == 0 ? 0 : 1;
}
