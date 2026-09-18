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

#include <asc/std/cfloat>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][cfloat] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][cfloat] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void test_flt_radix()
{
    // FLT_RADIX
    expect_eq("FLT_RADIX", (int)FLT_RADIX, 2);  // NOLINT(readability/casting)
}

static void test_decimal_dig_usable_exact()
{
    // DECIMAL_DIG (verify usable, exact value is implementation-defined)
#ifdef DECIMAL_DIG
    {
        constexpr auto decimal_dig = DECIMAL_DIG;
        std::cout << "[host][cfloat] DECIMAL_DIG = " << decimal_dig << " OK" << std::endl;
    }
#endif
}

static void test_flt_rounds_host_usable()
{
    // FLT_ROUNDS (host only, verify usable)
    {
        const auto flt_rounds = FLT_ROUNDS;
        std::cout << "[host][cfloat] FLT_ROUNDS = " << flt_rounds << " OK" << std::endl;
    }
}

static void test_flt_eval_method_usable()
{
    // FLT_EVAL_METHOD (verify usable)
    {
        constexpr auto flt_eval_method = FLT_EVAL_METHOD;
        std::cout << "[host][cfloat] FLT_EVAL_METHOD = " << flt_eval_method << " OK" << std::endl;
    }
}

static void test_flt_decimal_dig()
{
    // FLT_DECIMAL_DIG
#ifdef FLT_DECIMAL_DIG
    expect_eq("FLT_DECIMAL_DIG", (int)FLT_DECIMAL_DIG, 9);  // NOLINT(readability/casting)
#endif
}

static void test_flt_min()
{
    // FLT_MIN
    expect_eq("FLT_MIN", (float)FLT_MIN, 1.17549435082228750796873653722224568e-38f);  // NOLINT(readability/casting)
    expect_true("decltype(FLT_MIN) == float", std::is_same<decltype(FLT_MIN), float>::value);
}

static void test_flt_true_min()
{
    // FLT_TRUE_MIN
#ifdef FLT_TRUE_MIN
    expect_eq("FLT_TRUE_MIN", (float)FLT_TRUE_MIN,    // NOLINT(readability/casting)
        1.40129846432481707092372958328991613e-45f);  // NOLINT(readability/casting)
    expect_true("decltype(FLT_TRUE_MIN) == float", std::is_same<decltype(FLT_TRUE_MIN), float>::value);
#endif
}

static void test_flt_max()
{
    // FLT_MAX
    expect_eq("FLT_MAX", (float)FLT_MAX, 3.40282346638528859811704183484516925e+38f);  // NOLINT(readability/casting)
    expect_true("decltype(FLT_MAX) == float", std::is_same<decltype(FLT_MAX), float>::value);
}

static void test_flt_epsilon()
{
    // FLT_EPSILON
    expect_eq(
        "FLT_EPSILON", (float)FLT_EPSILON, 1.19209289550781250000000000000000000e-7f);  // NOLINT(readability/casting)
    expect_true("decltype(FLT_EPSILON) == float", std::is_same<decltype(FLT_EPSILON), float>::value);
}

static void test_flt_dig()
{
    // FLT_DIG
    expect_eq("FLT_DIG", (int)FLT_DIG, 6);  // NOLINT(readability/casting)
}

static void test_flt_mant_dig()
{
    // FLT_MANT_DIG
    expect_eq("FLT_MANT_DIG", (int)FLT_MANT_DIG, 24);  // NOLINT(readability/casting)
}

static void test_flt_min_exp()
{
    // FLT_MIN_EXP
    expect_eq("FLT_MIN_EXP", (int)FLT_MIN_EXP, -125);  // NOLINT(readability/casting)
}

static void test_flt_min_exp_2()
{
    // FLT_MIN_10_EXP
    expect_eq("FLT_MIN_10_EXP", (int)FLT_MIN_10_EXP, -37);  // NOLINT(readability/casting)
}

static void test_flt_max_exp()
{
    // FLT_MAX_EXP
    expect_eq("FLT_MAX_EXP", (int)FLT_MAX_EXP, 128);  // NOLINT(readability/casting)
}

static void test_flt_max_exp_2()
{
    // FLT_MAX_10_EXP
    expect_eq("FLT_MAX_10_EXP", (int)FLT_MAX_10_EXP, 38);  // NOLINT(readability/casting)
}

static void test_flt_subnorm()
{
    // FLT_HAS_SUBNORM
#ifdef FLT_HAS_SUBNORM
    expect_eq("FLT_HAS_SUBNORM", (int)FLT_HAS_SUBNORM, 1);  // NOLINT(readability/casting)
#endif
}

static void test_dbl_decimal_dig()
{
    // DBL_DECIMAL_DIG
#ifdef DBL_DECIMAL_DIG
    expect_eq("DBL_DECIMAL_DIG", (int)DBL_DECIMAL_DIG, 17);  // NOLINT(readability/casting)
#endif
}

static void test_dbl_min()
{
    // DBL_MIN
    expect_eq("DBL_MIN", (double)DBL_MIN, 2.22507385850720138309023271733240406e-308);  // NOLINT(readability/casting)
    expect_true("decltype(DBL_MIN) == double", std::is_same<decltype(DBL_MIN), double>::value);
}

static void test_dbl_true_min()
{
    // DBL_TRUE_MIN
#ifdef DBL_TRUE_MIN
    expect_eq("DBL_TRUE_MIN", (double)DBL_TRUE_MIN,   // NOLINT(readability/casting)
        4.94065645841246544176568792868221372e-324);  // NOLINT(readability/casting)
    expect_true("decltype(DBL_TRUE_MIN) == double", std::is_same<decltype(DBL_TRUE_MIN), double>::value);
#endif
}

static void test_dbl_max()
{
    // DBL_MAX
    expect_eq("DBL_MAX", (double)DBL_MAX, 1.79769313486231570814527423731704357e+308);  // NOLINT(readability/casting)
    expect_true("decltype(DBL_MAX) == double", std::is_same<decltype(DBL_MAX), double>::value);
}

static void test_dbl_epsilon()
{
    // DBL_EPSILON
    expect_eq(
        "DBL_EPSILON", (double)DBL_EPSILON, 2.22044604925031308084726333618164062e-16);  // NOLINT(readability/casting)
    expect_true("decltype(DBL_EPSILON) == double", std::is_same<decltype(DBL_EPSILON), double>::value);
}

static void test_dbl_dig()
{
    // DBL_DIG
    expect_eq("DBL_DIG", (int)DBL_DIG, 15);  // NOLINT(readability/casting)
}

static void test_dbl_mant_dig()
{
    // DBL_MANT_DIG
    expect_eq("DBL_MANT_DIG", (int)DBL_MANT_DIG, 53);  // NOLINT(readability/casting)
}

static void test_dbl_min_exp()
{
    // DBL_MIN_EXP
    expect_eq("DBL_MIN_EXP", (int)DBL_MIN_EXP, -1021);  // NOLINT(readability/casting)
}

static void test_dbl_min_exp_2()
{
    // DBL_MIN_10_EXP
    expect_eq("DBL_MIN_10_EXP", (int)DBL_MIN_10_EXP, -307);  // NOLINT(readability/casting)
}

static void test_dbl_max_exp()
{
    // DBL_MAX_EXP
    expect_eq("DBL_MAX_EXP", (int)DBL_MAX_EXP, 1024);  // NOLINT(readability/casting)
}

static void test_dbl_max_exp_2()
{
    // DBL_MAX_10_EXP
    expect_eq("DBL_MAX_10_EXP", (int)DBL_MAX_10_EXP, 308);  // NOLINT(readability/casting)
}

static void test_dbl_subnorm()
{
    // DBL_HAS_SUBNORM
#ifdef DBL_HAS_SUBNORM
    expect_eq("DBL_HAS_SUBNORM", (int)DBL_HAS_SUBNORM, 1);  // NOLINT(readability/casting)
#endif
}

static void test_ldbl_type_long_double()
{
    // LDBL type checks (long double available on host)
    expect_true("decltype(LDBL_MIN) == long double", std::is_same<decltype(LDBL_MIN), long double>::value);
    expect_true("decltype(LDBL_MAX) == long double", std::is_same<decltype(LDBL_MAX), long double>::value);
    expect_true("decltype(LDBL_EPSILON) == long double", std::is_same<decltype(LDBL_EPSILON), long double>::value);
#ifdef LDBL_TRUE_MIN
    expect_true("decltype(LDBL_TRUE_MIN) == long double", std::is_same<decltype(LDBL_TRUE_MIN), long double>::value);
#endif
    {
        [[maybe_unused]] constexpr auto ldbl_dig = LDBL_DIG;
        [[maybe_unused]] constexpr auto ldbl_mant_dig = LDBL_MANT_DIG;
        [[maybe_unused]] constexpr auto ldbl_min_exp = LDBL_MIN_EXP;
        [[maybe_unused]] constexpr auto ldbl_min_10_exp = LDBL_MIN_10_EXP;
        [[maybe_unused]] constexpr auto ldbl_max_exp = LDBL_MAX_EXP;
        [[maybe_unused]] constexpr auto ldbl_max_10_exp = LDBL_MAX_10_EXP;
        std::cout << "[host][cfloat] LDBL_* macros usable OK" << std::endl;
    }
#ifdef LDBL_HAS_SUBNORM
    {
        [[maybe_unused]] constexpr auto ldbl_has_subnorm = LDBL_HAS_SUBNORM;
    }
#endif
#ifdef LDBL_DECIMAL_DIG
    {
        [[maybe_unused]] constexpr auto ldbl_decimal_dig = LDBL_DECIMAL_DIG;
    }
#endif
}

static void test_host_cfloat_total()
{
    std::cout << "[host][cfloat] Total failures: " << g_failures << std::endl;
}

int main()
{
    test_flt_radix();
    test_decimal_dig_usable_exact();
    test_flt_rounds_host_usable();
    test_flt_eval_method_usable();
    test_flt_decimal_dig();
    test_flt_min();
    test_flt_true_min();
    test_flt_max();
    test_flt_epsilon();
    test_flt_dig();
    test_flt_mant_dig();
    test_flt_min_exp();
    test_flt_min_exp_2();
    test_flt_max_exp();
    test_flt_max_exp_2();
    test_flt_subnorm();
    test_dbl_decimal_dig();
    test_dbl_min();
    test_dbl_true_min();
    test_dbl_max();
    test_dbl_epsilon();
    test_dbl_dig();
    test_dbl_mant_dig();
    test_dbl_min_exp();
    test_dbl_min_exp_2();
    test_dbl_max_exp();
    test_dbl_max_exp_2();
    test_dbl_subnorm();
    test_ldbl_type_long_double();
    test_host_cfloat_total();

    return g_failures == 0 ? 0 : 1;
}
