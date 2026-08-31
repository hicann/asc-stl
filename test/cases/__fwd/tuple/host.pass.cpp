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

#include <asc/std/__fwd/tuple.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][tuple] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][tuple] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // 1. tuple forward declaration is usable as a type (incomplete type — no sizeof)
    {
        using T0 = asc::std::tuple<>;
        using T1 = asc::std::tuple<int>;
        using T2 = asc::std::tuple<int, double>;
        using T3 = asc::std::tuple<int, double, char>;
        // Forming pointers to incomplete types is valid.
        T0* p0 = nullptr;
        T1* p1 = nullptr;
        T2* p2 = nullptr;
        T3* p3 = nullptr;
        (void)p0;
        (void)p1;
        (void)p2;
        (void)p3;
        std::cout << "[host][tuple] forward-declared tuple types usable as types OK" << std::endl;
    }

    // 2. __is_asc_std_tuple is true for asc::std::tuple specializations
    expect_true("__is_asc_std_tuple<asc::std::tuple<>>", asc::std::__is_asc_std_tuple<asc::std::tuple<>>);
    expect_true("__is_asc_std_tuple<asc::std::tuple<int>>", asc::std::__is_asc_std_tuple<asc::std::tuple<int>>);
    expect_true("__is_asc_std_tuple<asc::std::tuple<int,double,char>>",
        asc::std::__is_asc_std_tuple<asc::std::tuple<int, double, char>>);

    // 3. __is_asc_std_tuple is false for non-tuple types
    expect_false("__is_asc_std_tuple<int>", asc::std::__is_asc_std_tuple<int>);
    expect_false("__is_asc_std_tuple<double>", asc::std::__is_asc_std_tuple<double>);

    // 4. __is_tuple_of_iterator_references_v defaults to false for all types
    expect_false("__is_tuple_of_iterator_references_v<int>", asc::std::__is_tuple_of_iterator_references_v<int>);
    expect_false("__is_tuple_of_iterator_references_v<asc::std::tuple<int>>",
        asc::std::__is_tuple_of_iterator_references_v<asc::std::tuple<int>>);

    // 5. Can form pointer / reference to forward-declared tuple
    {
        asc::std::tuple<int>* ptr = nullptr;
        (void)ptr;
        std::cout << "[host][tuple] pointer to asc::std::tuple<int> formed OK" << std::endl;
    }

    return g_failures == 0 ? 0 : 1;
}
