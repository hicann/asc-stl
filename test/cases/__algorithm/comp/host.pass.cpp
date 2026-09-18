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

#include <asc/std/__algorithm/comp.h>

#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][comp] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][comp] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

struct NothrowValue {
    int v;
    bool operator==(const NothrowValue& other) const noexcept
    {
        return v == other.v;
    }
    bool operator<(const NothrowValue& other) const noexcept
    {
        return v < other.v;
    }
};

struct ThrowingValue {
    int v;
    bool operator==(const ThrowingValue& other) const
    {
        return v == other.v;
    }
    bool operator<(const ThrowingValue& other) const
    {
        return v < other.v;
    }
};

static_assert(noexcept(asc::std::__equal_to{}(NothrowValue{}, NothrowValue{})));
static_assert(noexcept(asc::std::__less{}(NothrowValue{}, NothrowValue{})));
static_assert(!noexcept(asc::std::__equal_to{}(ThrowingValue{}, ThrowingValue{})));
static_assert(!noexcept(asc::std::__less{}(ThrowingValue{}, ThrowingValue{})));

int main()
{
    asc::std::__equal_to equal_to{};
    asc::std::__less less{};

    expect_true("__equal_to{}(1, 1)", equal_to(1, 1));
    expect_false("__equal_to{}(1, 2)", equal_to(1, 2));
    expect_true("__equal_to{}(1, 1.0)", equal_to(1, 1.0));
    expect_false("__equal_to{}(1, 2.0)", equal_to(1, 2.0));

    expect_true("__less{}(1, 2)", less(1, 2));
    expect_false("__less{}(2, 1)", less(2, 1));
    expect_false("__less{}(1, 1)", less(1, 1));
    expect_true("__less{}(-5, 0)", less(-5, 0));
    expect_true("__less{}(1, 2.5)", less(1, 2.5));
    expect_false("__less{}(3, 2.5)", less(3, 2.5));

    std::string abc = "abc";
    std::string abd = "abd";
    expect_true("__equal_to{}(abc, abc)", equal_to(abc, std::string("abc")));
    expect_false("__equal_to{}(abc, abd)", equal_to(abc, abd));
    expect_true("__less{}(abc, abd)", less(abc, abd));
    expect_false("__less{}(abd, abc)", less(abd, abc));

    NothrowValue a{5};
    NothrowValue b{5};
    NothrowValue c{10};
    expect_true("__equal_to{}(NothrowValue{5}, NothrowValue{5})", equal_to(a, b));
    expect_false("__equal_to{}(NothrowValue{5}, NothrowValue{10})", equal_to(a, c));
    expect_true("__less{}(NothrowValue{5}, NothrowValue{10})", less(a, c));
    expect_false("__less{}(NothrowValue{10}, NothrowValue{5})", less(c, a));

    return g_failures == 0 ? 0 : 1;
}
