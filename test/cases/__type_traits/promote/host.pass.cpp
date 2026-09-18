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

#include <asc/std/__type_traits/promote.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][promote] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][promote] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

struct NonNumeric {};

static void check_part1()
{
    // === __numeric_type value tests ===
    expect_true("__numeric_type<float>::value", asc::std::__numeric_type<float>::value);
    expect_true("__numeric_type<int>::value", asc::std::__numeric_type<int>::value);
    expect_true("__numeric_type<char>::value", asc::std::__numeric_type<char>::value);
    expect_true("__numeric_type<unsigned>::value", asc::std::__numeric_type<unsigned>::value);
    expect_true("__numeric_type<long>::value", asc::std::__numeric_type<long>::value);
    expect_true("__numeric_type<unsigned long>::value", asc::std::__numeric_type<unsigned long>::value);
    expect_true("__numeric_type<long long>::value", asc::std::__numeric_type<long long>::value);
    expect_true("__numeric_type<unsigned long long>::value", asc::std::__numeric_type<unsigned long long>::value);
    expect_true("__numeric_type<double>::value", asc::std::__numeric_type<double>::value);
    expect_true("__numeric_type<long double>::value", asc::std::__numeric_type<long double>::value);
    expect_false("__numeric_type<NonNumeric>::value", asc::std::__numeric_type<NonNumeric>::value);
    expect_true("__numeric_type<void>::value", asc::std::__numeric_type<void>::value);

    // === __numeric_type type tests ===
    expect_true("__numeric_type<float>::type is float", std::is_same_v<asc::std::__numeric_type<float>::type, float>);
    expect_true("__numeric_type<int>::type is double", std::is_same_v<asc::std::__numeric_type<int>::type, double>);
    expect_true("__numeric_type<char>::type is double", std::is_same_v<asc::std::__numeric_type<char>::type, double>);
    expect_true(
        "__numeric_type<unsigned>::type is double", std::is_same_v<asc::std::__numeric_type<unsigned>::type, double>);
    expect_true("__numeric_type<long>::type is double", std::is_same_v<asc::std::__numeric_type<long>::type, double>);
    expect_true("__numeric_type<unsigned long>::type is double",
        std::is_same_v<asc::std::__numeric_type<unsigned long>::type, double>);
    expect_true(
        "__numeric_type<long long>::type is double", std::is_same_v<asc::std::__numeric_type<long long>::type, double>);
    expect_true("__numeric_type<unsigned long long>::type is double",
        std::is_same_v<asc::std::__numeric_type<unsigned long long>::type, double>);
    expect_true(
        "__numeric_type<double>::type is double", std::is_same_v<asc::std::__numeric_type<double>::type, double>);
    expect_true("__numeric_type<long double>::type is long double",
        std::is_same_v<asc::std::__numeric_type<long double>::type, long double>);

    // === __promote single-arg tests ===
    expect_true("__promote<float>::value", asc::std::__promote<float>::value);
    expect_true("__promote<int>::value", asc::std::__promote<int>::value);
    expect_true("__promote<char>::value", asc::std::__promote<char>::value);
    expect_true("__promote<double>::value", asc::std::__promote<double>::value);
    expect_true("__promote<long double>::value", asc::std::__promote<long double>::value);
    expect_false("__promote<NonNumeric>::value", asc::std::__promote<NonNumeric>::value);

    expect_true("__promote<float>::type is float", std::is_same_v<asc::std::__promote<float>::type, float>);
    expect_true("__promote<int>::type is double", std::is_same_v<asc::std::__promote<int>::type, double>);
    expect_true("__promote<char>::type is double", std::is_same_v<asc::std::__promote<char>::type, double>);
    expect_true("__promote<unsigned>::type is double", std::is_same_v<asc::std::__promote<unsigned>::type, double>);
    expect_true("__promote<long long>::type is double", std::is_same_v<asc::std::__promote<long long>::type, double>);
    expect_true("__promote<double>::type is double", std::is_same_v<asc::std::__promote<double>::type, double>);
}

static void check_part2()
{
    expect_true("__promote<long double>::type is long double",
        std::is_same_v<asc::std::__promote<long double>::type, long double>);

    // __promote_t single-arg
    expect_true("__promote_t<float> is float", std::is_same_v<asc::std::__promote_t<float>, float>);
    expect_true("__promote_t<int> is double", std::is_same_v<asc::std::__promote_t<int>, double>);
    expect_true(
        "__promote_t<long double> is long double", std::is_same_v<asc::std::__promote_t<long double>, long double>);

    // === __promote two-arg tests ===
    expect_true("__promote<int, int>::value", asc::std::__promote<int, int>::value);
    expect_true("__promote<int, float>::value", asc::std::__promote<int, float>::value);
    expect_true("__promote<float, float>::value", asc::std::__promote<float, float>::value);
    expect_false("__promote<NonNumeric, int>::value", asc::std::__promote<NonNumeric, int>::value);
    expect_false("__promote<int, NonNumeric>::value", asc::std::__promote<int, NonNumeric>::value);

    expect_true("__promote<int, int>::type is double", std::is_same_v<asc::std::__promote<int, int>::type, double>);
    expect_true("__promote<int, float>::type is double", std::is_same_v<asc::std::__promote<int, float>::type, double>);
    expect_true(
        "__promote<float, float>::type is float", std::is_same_v<asc::std::__promote<float, float>::type, float>);
    expect_true(
        "__promote<float, double>::type is double", std::is_same_v<asc::std::__promote<float, double>::type, double>);
    expect_true("__promote<long double, float>::type is long double",
        std::is_same_v<asc::std::__promote<long double, float>::type, long double>);
    expect_true("__promote<char, int>::type is double", std::is_same_v<asc::std::__promote<char, int>::type, double>);
    expect_true("__promote<unsigned long long, long double>::type is long double",
        std::is_same_v<asc::std::__promote<unsigned long long, long double>::type, long double>);

    // __promote_t two-arg
    expect_true("__promote_t<int, float> is double", std::is_same_v<asc::std::__promote_t<int, float>, double>);
    expect_true("__promote_t<float, float> is float", std::is_same_v<asc::std::__promote_t<float, float>, float>);
    expect_true("__promote_t<long double, int> is long double",
        std::is_same_v<asc::std::__promote_t<long double, int>, long double>);

    // === __promote three-arg tests ===
    expect_true("__promote<int, int, int>::value", asc::std::__promote<int, int, int>::value);
    expect_true("__promote<float, int, double>::value", asc::std::__promote<float, int, double>::value);
    expect_false("__promote<NonNumeric, int, float>::value", asc::std::__promote<NonNumeric, int, float>::value);

    expect_true(
        "__promote<int, int, int>::type is double", std::is_same_v<asc::std::__promote<int, int, int>::type, double>);
    expect_true("__promote<float, int, double>::type is double",
        std::is_same_v<asc::std::__promote<float, int, double>::type, double>);
    expect_true("__promote<float, float, float>::type is float",
        std::is_same_v<asc::std::__promote<float, float, float>::type, float>);
    expect_true("__promote<long double, float, int>::type is long double",
        std::is_same_v<asc::std::__promote<long double, float, int>::type, long double>);
    expect_true("__promote<char, int, long>::type is double",
        std::is_same_v<asc::std::__promote<char, int, long>::type, double>);

    // __promote_t three-arg
    expect_true("__promote_t<int, int, int> is double", std::is_same_v<asc::std::__promote_t<int, int, int>, double>);
}

static void check_part3()
{
    expect_true(
        "__promote_t<float, float, float> is float", std::is_same_v<asc::std::__promote_t<float, float, float>, float>);
    expect_true("__promote_t<long double, int, float> is long double",
        std::is_same_v<asc::std::__promote_t<long double, int, float>, long double>);
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
