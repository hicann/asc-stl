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

#include <asc/std/__utility/undefined.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][undefined] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // __undefined is a variadic template struct that is intentionally left undefined (incomplete type).
    // It serves as a compile-time type tag / SFINAE sentinel.

    // 1. Same instantiation yields same type
    expect_true("is_same(__undefined<int>, __undefined<int>)",
        std::is_same<asc::std::__undefined<int>, asc::std::__undefined<int>>::value);

    // 2. Different instantiations yield different types
    expect_true("!is_same(__undefined<int>, __undefined<float>)",
        !std::is_same<asc::std::__undefined<int>, asc::std::__undefined<float>>::value);

    // 3. Zero-arg instantiation is valid
    expect_true("!is_same(__undefined<>, __undefined<int>)",
        !std::is_same<asc::std::__undefined<>, asc::std::__undefined<int>>::value);

    // 4. Multi-arg instantiation is valid and distinct
    expect_true("!is_same(__undefined<int,float>, __undefined<int>)",
        !std::is_same<asc::std::__undefined<int, float>, asc::std::__undefined<int>>::value);

    expect_true("!is_same(__undefined<int,float>, __undefined<float,int>)",
        !std::is_same<asc::std::__undefined<int, float>, asc::std::__undefined<float, int>>::value);

    // 5. __undefined is not the same as other common types
    expect_true("!is_same(__undefined<int>, int)", !std::is_same<asc::std::__undefined<int>, int>::value);

    return g_failures == 0 ? 0 : 1;
}
