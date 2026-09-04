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

#include <asc/std/optional>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][optional] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool got)
{
    bool ok = got;
    std::cout << "[host][optional] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    bool ok = !got;
    std::cout << "[host][optional] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_)  // NOLINT(runtime/explicit)
    {}
};

static void check_part1()
{
    // Default construction
    asc::std::optional<int> o1;
    expect_false("optional<int>() has_value", o1.has_value());
    expect_false("(bool)optional<int>()", static_cast<bool>(o1));

    // nullopt construction
    asc::std::optional<int> o2(asc::std::nullopt);
    expect_false("optional<int>(nullopt) has_value", o2.has_value());

    // Value construction
    asc::std::optional<int> o3(42);
    expect_true("optional<int>(42) has_value", o3.has_value());
    expect_eq("optional<int>(42) value", *o3, 42);

    // in_place construction
    asc::std::optional<int> o4(asc::std::in_place, 100);
    expect_true("optional<int>(in_place, 100) has_value", o4.has_value());
    expect_eq("optional<int>(in_place, 100) value", *o4, 100);

    // in_place construction for struct
    asc::std::optional<Point> o5(asc::std::in_place, 1, 2);
    expect_eq("optional<Point>(in_place, 1, 2)->x", o5->x, 1);
    expect_eq("optional<Point>(in_place, 1, 2)->y", o5->y, 2);

    // Copy construction
    asc::std::optional<int> o6(o3);
    expect_eq("copy constructed value", *o6, 42);

    // Move construction
    asc::std::optional<int> o7(std::move(o6));
    expect_eq("move constructed value", *o7, 42);

    // Assignment value to empty
    o1 = o3;
    expect_eq("assign value to empty", *o1, 42);

    // Assignment empty to value
    o3 = o2;
    expect_false("assign empty to value", o3.has_value());

    // Assignment value to value
    o1 = 99;
    expect_eq("assign value to value", *o1, 99);

    // Assignment empty to empty
    o2 = asc::std::nullopt;
}

static void check_part2()
{
    asc::std::optional<int> o2(asc::std::nullopt);
    expect_false("assign empty to empty", o2.has_value());

    // value()
    asc::std::optional<int> o8(10);
    expect_eq("value() has value", o8.value(), 10);

    // value() throws
    try {
        asc::std::optional<int> o9;
        o9.value();
        expect_true("value() throws bad_optional_access", false);
    } catch (const asc::std::bad_optional_access&) {
        expect_true("value() throws bad_optional_access", true);
    } catch (...) {
        expect_true("value() throws bad_optional_access", false);
    }

    // value_or()
    expect_eq("value_or() has value", o8.value_or(0), 10);
    expect_eq("value_or() empty", o2.value_or(0), 0);

    // reset()
    o8.reset();
    expect_false("reset() has_value", o8.has_value());

    // emplace()
    o8.emplace(77);
    expect_eq("emplace() value", *o8, 77);

    // swap() member
    asc::std::optional<int> a(1), b(2);
    a.swap(b);
    expect_eq("swap() a", *a, 2);
    expect_eq("swap() b", *b, 1);
}

static void check_part3()
{
    asc::std::optional<int> a(2), b(1);
    asc::std::swap(a, b);  // NOLINT(build/include_what_you_use)
    expect_eq("free swap() a", *a, 1);
    expect_eq("free swap() b", *b, 2);

    // swap() with empty
    asc::std::optional<int> c(3), d;
    c.swap(d);
    expect_false("swap() c empty", c.has_value());
    expect_eq("swap() d value", *d, 3);

    // Comparisons
    asc::std::optional<int> e(1), f(2), g_empty;
    expect_false("e == f", e == f);
    expect_true("e != f", e != f);
    expect_true("e < f", e < f);
    expect_true("e <= f", e <= f);
    expect_false("e > f", e > f);
    expect_false("e >= f", e >= f);

    // Comparisons with empty
    expect_true("g_empty < e", g_empty < e);
    expect_false("g_empty > e", g_empty > e);

    // Comparisons with value
    expect_true("e == 1", e == 1);
    expect_false("e == 2", e == 2);
    expect_true("e < 2", e < 2);
    expect_false("e < 1", e < 1);

    // make_optional
    auto m1 = asc::std::make_optional(123);
    expect_eq("make_optional(123)", *m1, 123);
    auto m2 = asc::std::make_optional<int>(456);
    expect_eq("make_optional<int>(456)", *m2, 456);
    auto m3 = asc::std::make_optional<Point>(7, 8);
    expect_eq("make_optional<Point>(7, 8)->x", m3->x, 7);
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
