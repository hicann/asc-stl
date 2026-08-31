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

#include <asc/__type_traits/is_specialization_of.h>
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <tuple>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_specialization_of] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    expect_eq("asc::__is_specialization_of_v<std::vector<int>, std::vector>",
        asc::__is_specialization_of_v<std::vector<int>, std::vector>, true);

    expect_eq("asc::__is_specialization_of_v<std::vector<int>, std::list>",
        asc::__is_specialization_of_v<std::vector<int>, std::list>, false);

    expect_eq("asc::__is_specialization_of_v<std::pair<int,float>, std::pair>",
        asc::__is_specialization_of_v<std::pair<int, float>, std::pair>, true);

    expect_eq(
        "asc::__is_specialization_of_v<int, std::vector>", asc::__is_specialization_of_v<int, std::vector>, false);

    expect_eq("asc::__is_specialization_of_v<std::tuple<int,double,char>, std::tuple>",
        asc::__is_specialization_of_v<std::tuple<int, double, char>, std::tuple>, true);

    return g_failures == 0 ? 0 : 1;
}
