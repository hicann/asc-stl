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

#include <asc/std/__type_traits/is_unsigned.h>
#include <iostream>

static int g_failures = 0;

static void check_trait(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_unsigned] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

#define CHECK_TRAIT(expr, expected) check_trait(#expr, (expr), (expected))

int main()
{
    CHECK_TRAIT(asc::std::is_unsigned<unsigned int>::value, true);
    CHECK_TRAIT(asc::std::is_unsigned<int>::value, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<unsigned char>, true);
    CHECK_TRAIT(asc::std::is_unsigned_v<signed char>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<unsigned short>, true);
    CHECK_TRAIT(asc::std::is_unsigned_v<short>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<unsigned long>, true);
    CHECK_TRAIT(asc::std::is_unsigned_v<long>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<unsigned long long>, true);
    CHECK_TRAIT(asc::std::is_unsigned_v<long long>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<bool>, true);
    CHECK_TRAIT(asc::std::is_unsigned_v<float>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<double>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<void>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<int*>, false);
    CHECK_TRAIT(asc::std::is_unsigned_v<const unsigned int>, true);
    CHECK_TRAIT(asc::std::is_unsigned_v<volatile unsigned long>, true);

    return g_failures == 0 ? 0 : 1;
}
