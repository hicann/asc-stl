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

#include <asc/std/__type_traits/is_referenceable.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_referenceable] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Incomplete;

int main()
{
    expect_eq("__asc_is_referenceable<int>::value", asc::std::__asc_is_referenceable<int>::value, true);
    expect_eq("__asc_is_referenceable<void>::value", asc::std::__asc_is_referenceable<void>::value, false);
    expect_eq("__asc_is_referenceable<int&>::value", asc::std::__asc_is_referenceable<int&>::value, true);
    expect_eq("__asc_is_referenceable<Incomplete>::value", asc::std::__asc_is_referenceable<Incomplete>::value, true);
    expect_eq("__asc_is_referenceable<void()>::value", asc::std::__asc_is_referenceable<void()>::value, true);
    expect_eq("__asc_is_referenceable<int(int)>::value", asc::std::__asc_is_referenceable<int(int)>::value, true);

    return g_failures == 0 ? 0 : 1;
}
