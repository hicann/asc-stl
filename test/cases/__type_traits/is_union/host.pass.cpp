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

#include <asc/std/__type_traits/is_union.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_union] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

union U1 {
    int a;
    double b;
};
union U2 {
    char c;
    float d;
};

struct S1 {
    int x;
    double y;
};
struct S2 {
    virtual ~S2()
    {}
};

class C1 {
public:
    int val;
};
enum E1 { A, B, C };

int main()
{
    // unions should be true
    expect_true("is_union<U1>::value", asc::std::is_union<U1>::value, true);
    expect_true("is_union<U2>::value", asc::std::is_union<U2>::value, true);
    expect_true("is_union_v<U1>", asc::std::is_union_v<U1>, true);
    expect_true("is_union_v<U2>", asc::std::is_union_v<U2>, true);

    // non-unions should be false
    expect_true("is_union<int>::value", asc::std::is_union<int>::value, false);
    expect_true("is_union<double>::value", asc::std::is_union<double>::value, false);
    expect_true("is_union<S1>::value", asc::std::is_union<S1>::value, false);
    expect_true("is_union<S2>::value", asc::std::is_union<S2>::value, false);
    expect_true("is_union<C1>::value", asc::std::is_union<C1>::value, false);
    expect_true("is_union<E1>::value", asc::std::is_union<E1>::value, false);
    expect_true("is_union<void>::value", asc::std::is_union<void>::value, false);
    expect_true("is_union<int*>::value", asc::std::is_union<int*>::value, false);
    expect_true("is_union<int&>::value", asc::std::is_union<int&>::value, false);
    expect_true("is_union<int[3]>::value", asc::std::is_union<int[3]>::value, false);

    // _v variant
    expect_true("is_union_v<int>", asc::std::is_union_v<int>, false);
    expect_true("is_union_v<S1>", asc::std::is_union_v<S1>, false);
    expect_true("is_union_v<void>", asc::std::is_union_v<void>, false);

    // cv-qualified unions
    expect_true("is_union<const U1>::value", asc::std::is_union<const U1>::value, true);
    expect_true("is_union<volatile U1>::value", asc::std::is_union<volatile U1>::value, true);
    expect_true("is_union<const volatile U2>::value", asc::std::is_union<const volatile U2>::value, true);
    expect_true("is_union_v<const U1>", asc::std::is_union_v<const U1>, true);

    // integral_constant inheritance: is_union<U1> should be derived from bool_constant<true>
    static_assert(asc::std::is_union<U1>::value == true, "is_union<U1> should be true");
    static_assert(asc::std::is_union<int>::value == false, "is_union<int> should be false");

    return g_failures == 0 ? 0 : 1;
}
