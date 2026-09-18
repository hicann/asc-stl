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

#include <asc/std/__asc/attributes.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][attributes] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][attributes] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// ---- CANN_ASC_STL_DETAIL_ASSUME (from assume_attribute.pass.cpp) ----
bool f_assume(int x)
{
    CANN_ASC_STL_DETAIL_ASSUME(x > 3);
    return x > 3;
}

// ---- CANN_ASC_STL_DETAIL_PURE (from pure_const_attribute.pass.cpp) ----
CANN_ASC_STL_DETAIL_PURE int f_pure()
{
    return 42;
}

// ---- CANN_ASC_STL_DETAIL_CONST (from pure_const_attribute.pass.cpp) ----
CANN_ASC_STL_DETAIL_CONST int g_const()
{
    return 7;
}

// ---- CANN_ASC_STL_DETAIL_LIFETIMEBOUND (from lifetime_bound.compile.pass.cpp) ----
struct S_lifetimebound {
    int get() const CANN_ASC_STL_DETAIL_LIFETIMEBOUND
    {
        return 3;
    }
};

// ---- CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS (from no_specializations.pass.cpp) ----
#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS()
template <class T>
struct CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS StructNoSpec {
    static constexpr bool value = false;
};

template <class T>
CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS inline constexpr bool variableNoSpec = false;

template <class T>
CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS T functionNoSpec()
{
    return T{0};
}
#endif

// ---- CANN_ASC_STL_DETAIL_RESTRICT ----
void f_restrict(int* CANN_ASC_STL_DETAIL_RESTRICT p)
{
    *p = 10;
}

// ---- CANN_ASC_STL_DETAIL_NODEBUG ----
CANN_ASC_STL_DETAIL_NODEBUG int f_nodebug()
{
    return 1;
}

// ---- CANN_ASC_STL_DETAIL_ARTIFICIAL ----
CANN_ASC_STL_DETAIL_ARTIFICIAL inline int f_artificial()
{
    return 2;
}

// ---- CANN_ASC_STL_DETAIL_INTRINSIC ----
CANN_ASC_STL_DETAIL_INTRINSIC
int f_intrinsic()
{
    return 5;
}

// ---- CANN_ASC_STL_DETAIL_NO_SANITIZE ----
CANN_ASC_STL_DETAIL_NO_SANITIZE("undefined")
int f_no_sanitize()
{
    return 6;
}

// ---- CANN_ASC_STL_DETAIL_NO_CFI ----
CANN_ASC_STL_DETAIL_NO_CFI
int f_no_cfi()
{
    return 8;
}

// ---- CANN_ASC_STL_DETAIL_DIAGNOSE_IF ----
CANN_ASC_STL_DETAIL_DIAGNOSE_IF(true, "test message", "warning")
int f_diagnose_if()
{
    return 9;
}

// ---- CANN_ASC_STL_NO_UNIQUE_ADDRESS ----
struct Empty {};
struct WithNoUniqueAddress {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Empty e;
    int x;
};

// ---- CANN_ASC_STL_DETAIL_REQUIRE_CONSTANT_INITIALIZATION ----
CANN_ASC_STL_DETAIL_REQUIRE_CONSTANT_INITIALIZATION
static int g_const_init = 5;

// ---- CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES ----
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES Derived : Empty {
    int y;
};

int main()
{
    // CANN_ASC_STL_DETAIL_ASSUME
    expect_true("f_assume(5) returns true", f_assume(5));
    expect_true("f_assume(100) returns true", f_assume(100));

    // CANN_ASC_STL_DETAIL_PURE
    expect_eq("f_pure()", f_pure(), 42);

    // CANN_ASC_STL_DETAIL_CONST
    expect_eq("g_const()", g_const(), 7);

    // CANN_ASC_STL_DETAIL_LIFETIMEBOUND
    S_lifetimebound s;
    expect_eq("s.get()", s.get(), 3);

    // CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS
#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS()
    expect_true("StructNoSpec<int>::value is false", !StructNoSpec<int>::value);
    expect_true("variableNoSpec<int> is false", !variableNoSpec<int>);
    expect_eq("functionNoSpec<int>()", functionNoSpec<int>(), 0);
#else
    expect_true("CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS() is 0",
        !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS());
#endif

    // CANN_ASC_STL_DETAIL_RESTRICT
    int val = 0;
    f_restrict(&val);
    expect_eq("f_restrict sets *p to 10", val, 10);

    // CANN_ASC_STL_DETAIL_NODEBUG
    expect_eq("f_nodebug()", f_nodebug(), 1);

    // CANN_ASC_STL_DETAIL_ARTIFICIAL
    expect_eq("f_artificial()", f_artificial(), 2);

    // CANN_ASC_STL_DETAIL_INTRINSIC
    expect_eq("f_intrinsic()", f_intrinsic(), 5);

    // CANN_ASC_STL_DETAIL_NO_SANITIZE
    expect_eq("f_no_sanitize()", f_no_sanitize(), 6);

    // CANN_ASC_STL_DETAIL_NO_CFI
    expect_eq("f_no_cfi()", f_no_cfi(), 8);

    // CANN_ASC_STL_DETAIL_DIAGNOSE_IF
    expect_eq("f_diagnose_if()", f_diagnose_if(), 9);

    // CANN_ASC_STL_NO_UNIQUE_ADDRESS
    WithNoUniqueAddress w;
    w.x = 99;
    expect_eq("WithNoUniqueAddress.x", w.x, 99);

    // CANN_ASC_STL_DETAIL_REQUIRE_CONSTANT_INITIALIZATION
    expect_eq("g_const_init", g_const_init, 5);

    // CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES
    Derived d;
    d.y = 77;
    expect_eq("Derived.y", d.y, 77);

    return g_failures == 0 ? 0 : 1;
}
