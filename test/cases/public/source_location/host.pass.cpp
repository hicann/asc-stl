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

#include <asc/std/source_location>
#include <iostream>
#include <string_view>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <utility>

static int g_failures = 0;

static void expect_eq_u32(const char* expr, asc::std::uint_least32_t got, asc::std::uint_least32_t expected)
{
    bool ok = (got == expected);
    std::cout << "[host][source_location] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][source_location] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_str_empty(const char* expr, const char* got)
{
    bool ok = (got[0] == '\0');
    std::cout << "[host][source_location] " << expr << " = \"" << got << "\""
              << " (expected empty) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static bool compare_strings(const char* lhs, const char* rhs) noexcept
{
    return std::string_view(lhs) == std::string_view(rhs);
}

static bool find_substring(const char* source, const char* target) noexcept
{
    return std::string_view(source).find(target) != std::string_view::npos;
}

// Test 1: Default-constructed source_location has all zero/empty fields
static void test_default_constructed()
{
    constexpr asc::std::source_location empty{};
    expect_eq_u32("empty.line()", empty.line(), 0);
    expect_eq_u32("empty.column()", empty.column(), 0);
    expect_str_empty("empty.file_name()", empty.file_name());
    expect_str_empty("empty.function_name()", empty.function_name());
}

// Test 2: current() captures correct line, file, and function name
static void test_current_basic()
{
#line 2000
    auto local = asc::std::source_location::current();
    expect_eq_u32("local.line() (#line 2000)", local.line(), 2000);
    expect_true("local.file_name() == __FILE__", compare_strings(local.file_name(), __FILE__));
    expect_true("local.function_name() contains 'test_current_basic'",
        find_substring(local.function_name(), "test_current_basic"));
}

// Test 3: current() captures column (when __builtin_COLUMN is supported)
static void test_current_column()
{
    auto col_test = asc::std::source_location::current();
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_COLUMN) || CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 19, 27)
    expect_true("col_test.column() > 0", col_test.column() > 0);
#else
    expect_eq_u32("col_test.column() == 0 (no __builtin_COLUMN)", col_test.column(), 0);
#endif
}

// Test 4: Copy construction preserves all fields
static void test_copy_construction()
{
#line 4000
    auto src = asc::std::source_location::current();
    auto copied = src;
    expect_eq_u32("copied.line()", copied.line(), 4000);
    expect_true("copied.file_name() == src.file_name()", compare_strings(copied.file_name(), src.file_name()));
    expect_true(
        "copied.function_name() == src.function_name()", compare_strings(copied.function_name(), src.function_name()));
    expect_eq_u32("copied.column() == src.column()", copied.column(), src.column());
}

// Test 5: Copy assignment preserves all fields
static void test_copy_assignment()
{
#line 5000
    auto src = asc::std::source_location::current();
    asc::std::source_location dst;
    dst = src;
    expect_eq_u32("dst.line() after assignment", dst.line(), 5000);
    expect_true("dst.file_name() == src.file_name()", compare_strings(dst.file_name(), src.file_name()));
    expect_true(
        "dst.function_name() == src.function_name()", compare_strings(dst.function_name(), src.function_name()));
    expect_eq_u32("dst.column() == src.column()", dst.column(), src.column());
}

// Test 6: current() with explicit arguments stores exact values
static void test_current_with_explicit_args()
{
    auto sl = asc::std::source_location::current("custom.cpp", "my_func", 12345, 67);
    expect_eq_u32("sl.line() (explicit)", sl.line(), 12345);
    expect_eq_u32("sl.column() (explicit)", sl.column(), 67);
    expect_true("sl.file_name() == 'custom.cpp'", compare_strings(sl.file_name(), "custom.cpp"));
    expect_true("sl.function_name() == 'my_func'", compare_strings(sl.function_name(), "my_func"));
}

// Test 7: Type traits, noexcept, and return type checks
static void test_type_traits()
{
    static_assert(std::is_nothrow_move_constructible<asc::std::source_location>::value, "nothrow move constructible");
    static_assert(std::is_nothrow_move_assignable<asc::std::source_location>::value, "nothrow move assignable");
#if __cplusplus >= 201703L
    static_assert(std::is_nothrow_swappable<asc::std::source_location>::value, "nothrow swappable");
#endif

    constexpr asc::std::source_location empty{};
    static_assert(noexcept(asc::std::source_location()), "default ctor noexcept");
    static_assert(noexcept(asc::std::source_location::current()), "current() noexcept");
    static_assert(noexcept(empty.line()), "line() noexcept");
    static_assert(noexcept(empty.column()), "column() noexcept");
    static_assert(noexcept(empty.file_name()), "file_name() noexcept");
    static_assert(noexcept(empty.function_name()), "function_name() noexcept");

    static_assert(
        std::is_same<asc::std::uint_least32_t, decltype(empty.line())>::value, "line() returns uint_least32_t");
    static_assert(
        std::is_same<asc::std::uint_least32_t, decltype(empty.column())>::value, "column() returns uint_least32_t");
    static_assert(std::is_same<const char*, decltype(empty.file_name())>::value, "file_name() returns const char*");
    static_assert(
        std::is_same<const char*, decltype(empty.function_name())>::value, "function_name() returns const char*");

    std::cout << "[host][source_location] type traits and noexcept checks passed OK" << std::endl;
}

int main()
{
    test_default_constructed();
    test_current_basic();
    test_current_column();
    test_copy_construction();
    test_copy_assignment();
    test_current_with_explicit_args();
    test_type_traits();

    return g_failures == 0 ? 0 : 1;
}
