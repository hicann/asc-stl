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

#include <asc/std/__fwd/extents.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][extents] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][extents] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // __is_asc_std_extents_v trait — positive cases
    expect_true("__is_asc_std_extents_v<extents<size_t>>", asc::std::__is_asc_std_extents_v<asc::std::extents<size_t>>);
    expect_true("__is_asc_std_extents_v<extents<int, 3>>", asc::std::__is_asc_std_extents_v<asc::std::extents<int, 3>>);
    expect_true("__is_asc_std_extents_v<extents<size_t, 2, 3, dynamic_extent>>",
        asc::std::__is_asc_std_extents_v<asc::std::extents<size_t, 2, 3, asc::std::dynamic_extent>>);

    // __is_asc_std_extents_v trait — negative cases
    expect_false("__is_asc_std_extents_v<int>", asc::std::__is_asc_std_extents_v<int>);
    expect_false("__is_asc_std_extents_v<size_t>", asc::std::__is_asc_std_extents_v<size_t>);
    expect_false("__is_asc_std_extents_v<void>", asc::std::__is_asc_std_extents_v<void>);

    // dextents alias — rank 0
    expect_true("dextents<size_t, 0> == extents<size_t>",
        std::is_same_v<asc::std::dextents<size_t, 0>, asc::std::extents<size_t>>);
    // dextents alias — rank 1
    expect_true("dextents<size_t, 1> == extents<size_t, dynamic_extent>",
        std::is_same_v<asc::std::dextents<size_t, 1>, asc::std::extents<size_t, asc::std::dynamic_extent>>);
    // dextents alias — rank 2
    expect_true("dextents<size_t, 2> == extents<size_t, dynamic_extent, dynamic_extent>",
        std::is_same_v<asc::std::dextents<size_t, 2>,
            asc::std::extents<size_t, asc::std::dynamic_extent, asc::std::dynamic_extent>>);
    // dextents alias — rank 3
    expect_true("dextents<size_t, 3> == extents<size_t, dynamic_extent, dynamic_extent, dynamic_extent>",
        std::is_same_v<asc::std::dextents<size_t, 3>,
            asc::std::extents<size_t, asc::std::dynamic_extent, asc::std::dynamic_extent, asc::std::dynamic_extent>>);

    // dextents with different index type
    expect_true("dextents<int, 2> == extents<int, dynamic_extent, dynamic_extent>",
        std::is_same_v<asc::std::dextents<int, 2>,
            asc::std::extents<int, asc::std::dynamic_extent, asc::std::dynamic_extent>>);

    // dims alias (defaults IndexType = size_t)
    expect_true("dims<0> == extents<size_t>", std::is_same_v<asc::std::dims<0>, asc::std::extents<size_t>>);
    expect_true("dims<1> == extents<size_t, dynamic_extent>",
        std::is_same_v<asc::std::dims<1>, asc::std::extents<size_t, asc::std::dynamic_extent>>);
    expect_true("dims<2> == extents<size_t, dynamic_extent, dynamic_extent>",
        std::is_same_v<asc::std::dims<2>,
            asc::std::extents<size_t, asc::std::dynamic_extent, asc::std::dynamic_extent>>);
    expect_true("dims<3> == extents<size_t, dynamic_extent, dynamic_extent, dynamic_extent>",
        std::is_same_v<asc::std::dims<3>,
            asc::std::extents<size_t, asc::std::dynamic_extent, asc::std::dynamic_extent, asc::std::dynamic_extent>>);

    // dims with explicit index type
    expect_true("dims<2, int> == extents<int, dynamic_extent, dynamic_extent>",
        std::is_same_v<asc::std::dims<2, int>,
            asc::std::extents<int, asc::std::dynamic_extent, asc::std::dynamic_extent>>);

    // dynamic_extent value
    expect_true("dynamic_extent == static_cast<size_t>(-1)", asc::std::dynamic_extent == static_cast<size_t>(-1));

    return g_failures == 0 ? 0 : 1;
}
