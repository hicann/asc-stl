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

#include <asc/__utility/inherit.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][inherit] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][inherit] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

struct Empty1 {};
struct Empty2 {};
struct Empty3 {};

struct WithInt {
    int x;
};
struct WithDouble {
    double y;
};

int main()
{
    // __inherit<> — no bases
    using I0 = asc::__inherit<>;
    expect_true("is_empty(__inherit<>)", std::is_empty<I0>::value);
    expect_true("is_default_constructible(__inherit<>)", std::is_default_constructible<I0>::value);

    // __inherit<Empty1> — single empty base
    using I1 = asc::__inherit<Empty1>;
    expect_true("is_empty(__inherit<Empty1>)", std::is_empty<I1>::value);
    expect_true("is_base_of<Empty1, __inherit<Empty1>>", std::is_base_of<Empty1, I1>::value);

    // __inherit<Empty1, Empty2> — two empty bases, EBO should keep it empty
    using I2 = asc::__inherit<Empty1, Empty2>;
    expect_true("is_empty(__inherit<Empty1, Empty2>)", std::is_empty<I2>::value);
    expect_true("is_base_of<Empty1, __inherit<Empty1,Empty2>>", std::is_base_of<Empty1, I2>::value);
    expect_true("is_base_of<Empty2, __inherit<Empty1,Empty2>>", std::is_base_of<Empty2, I2>::value);

    // __inherit<Empty1, Empty2, Empty3> — three empty bases
    using I3 = asc::__inherit<Empty1, Empty2, Empty3>;
    expect_true("is_empty(__inherit<Empty1,Empty2,Empty3>)", std::is_empty<I3>::value);
    expect_true("is_base_of<Empty1, __inherit<...3>>", std::is_base_of<Empty1, I3>::value);
    expect_true("is_base_of<Empty2, __inherit<...3>>", std::is_base_of<Empty2, I3>::value);
    expect_true("is_base_of<Empty3, __inherit<...3>>", std::is_base_of<Empty3, I3>::value);

    // __inherit with non-empty base — member access through cast
    using I4 = asc::__inherit<WithInt>;
    expect_true("is_base_of<WithInt, __inherit<WithInt>>", std::is_base_of<WithInt, I4>::value);
    I4 obj4;
    static_cast<WithInt&>(obj4).x = 42;
    expect_eq("WithInt::x via __inherit<WithInt>", static_cast<WithInt&>(obj4).x, 42);

    // __inherit with two non-empty bases — both members accessible
    using I5 = asc::__inherit<WithInt, WithDouble>;
    expect_true("is_base_of<WithInt, __inherit<WithInt,WithDouble>>", std::is_base_of<WithInt, I5>::value);
    expect_true("is_base_of<WithDouble, __inherit<WithInt,WithDouble>>", std::is_base_of<WithDouble, I5>::value);
    I5 obj5;
    static_cast<WithInt&>(obj5).x = 7;
    static_cast<WithDouble&>(obj5).y = 2.5;
    expect_eq("WithInt::x via __inherit<WithInt,WithDouble>", static_cast<WithInt&>(obj5).x, 7);
    double got_y = static_cast<WithDouble&>(obj5).y;
    bool y_ok = (got_y == 2.5);
    std::cout << "[host][inherit] WithDouble::y via __inherit<WithInt,WithDouble> = " << got_y << " (expected 2.5) "
              << (y_ok ? "OK" : "FAIL") << std::endl;
    if (!y_ok)
        ++g_failures;

    // default constructibility
    expect_true("is_default_constructible<__inherit<Empty1,Empty2>>", std::is_default_constructible<I2>::value);

    return g_failures == 0 ? 0 : 1;
}
