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

#include <asc/std/__cstdlib/div.h>
#include <iostream>

static int g_failures = 0;

static void expect_div(const char* expr, asc::std::div_t got, int quot, int rem)
{
    bool ok = (got.quot == quot && got.rem == rem);
    std::cout << "[host][div] " << expr << " = {quot:" << got.quot << ", rem:" << got.rem
              << "} (expected {quot:" << quot << ", rem:" << rem << "}) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_ldiv(const char* expr, asc::std::ldiv_t got, long quot, long rem)
{
    bool ok = (got.quot == quot && got.rem == rem);
    std::cout << "[host][div] " << expr << " = {quot:" << got.quot << ", rem:" << got.rem
              << "} (expected {quot:" << quot << ", rem:" << rem << "}) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_lldiv(const char* expr, asc::std::lldiv_t got, long long quot, long long rem)
{
    bool ok = (got.quot == quot && got.rem == rem);
    std::cout << "[host][div] " << expr << " = {quot:" << got.quot << ", rem:" << got.rem
              << "} (expected {quot:" << quot << ", rem:" << rem << "}) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // div(int, int)
    expect_div("div(10, 3)", asc::std::div(10, 3), 3, 1);
    expect_div("div(-10, 3)", asc::std::div(-10, 3), -3, -1);
    expect_div("div(10, -3)", asc::std::div(10, -3), -3, 1);
    expect_div("div(-10, -3)", asc::std::div(-10, -3), 3, -1);
    expect_div("div(0, 5)", asc::std::div(0, 5), 0, 0);

    // ldiv(long, long)
    expect_ldiv("ldiv(100000000L, 3L)", asc::std::ldiv(100000000L, 3L), 33333333L, 1L);
    expect_ldiv("div(100000000L, 3L)", asc::std::div(100000000L, 3L), 33333333L, 1L);

    // lldiv(long long, long long)
    expect_lldiv("lldiv(1000000000000LL, 3LL)", asc::std::lldiv(1000000000000LL, 3LL), 333333333333LL, 1LL);
    expect_lldiv("div(1000000000000LL, 3LL)", asc::std::div(1000000000000LL, 3LL), 333333333333LL, 1LL);

    return g_failures == 0 ? 0 : 1;
}
