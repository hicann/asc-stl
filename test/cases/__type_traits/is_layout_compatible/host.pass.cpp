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

#include <asc/std/__type_traits/is_layout_compatible.h>
#include <iostream>

static int g_failures = 0;

static void expect_bool(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_layout_compatible] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

#if !defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_LAYOUT_COMPATIBLE)
int main()
{
    std::cout << "[host][is_layout_compatible] SKIPPED: compiler does not support __is_layout_compatible" << std::endl;
    return 0;
}
#else

int main()
{
    // Same type is layout compatible with itself
    expect_bool("is_layout_compatible_v<int, int>", asc::std::is_layout_compatible_v<int, int>, true);
    expect_bool("is_layout_compatible_v<float, float>", asc::std::is_layout_compatible_v<float, float>, true);
    expect_bool("is_layout_compatible_v<double, double>", asc::std::is_layout_compatible_v<double, double>, true);

    // Different scalar types are not layout compatible
    expect_bool("is_layout_compatible_v<int, float>", asc::std::is_layout_compatible_v<int, float>, false);
    expect_bool("is_layout_compatible_v<int, unsigned>", asc::std::is_layout_compatible_v<int, unsigned>, false);
    expect_bool("is_layout_compatible_v<int, char>", asc::std::is_layout_compatible_v<int, char>, false);

    // cv-qualified versions of the same type are layout compatible
    expect_bool("is_layout_compatible_v<int, const int>", asc::std::is_layout_compatible_v<int, const int>, true);
    expect_bool("is_layout_compatible_v<int, volatile int>", asc::std::is_layout_compatible_v<int, volatile int>, true);
    expect_bool("is_layout_compatible_v<const int, volatile int>",
        asc::std::is_layout_compatible_v<const int, volatile int>, true);

    // Enum and its underlying type are NOT layout compatible per [basic.types.general] p8:
    // only two enumerations with the same underlying type are layout-compatible.
    enum E1 : int {};
    enum E2 : int {};
    enum E3 : unsigned {};
    expect_bool("is_layout_compatible_v<E1, E2>", asc::std::is_layout_compatible_v<E1, E2>, true);
    expect_bool("is_layout_compatible_v<E1, int>", asc::std::is_layout_compatible_v<E1, int>, false);
    expect_bool("is_layout_compatible_v<E1, E3>", asc::std::is_layout_compatible_v<E1, E3>, false);

    // Standard-layout structs with same member layout are compatible
    struct S1 {
        int a;
    };
    struct S2 {
        int a;
    };
    expect_bool("is_layout_compatible_v<S1, S2>", asc::std::is_layout_compatible_v<S1, S2>, true);

    // Structs with different member order/types are not compatible
    struct S3 {
        int a;
        double b;
    };
    struct S4 {
        double b;
        int a;
    };
    expect_bool("is_layout_compatible_v<S3, S4>", asc::std::is_layout_compatible_v<S3, S4>, false);

    // Struct with different member count is not compatible
    struct S5 {
        int a;
        int b;
    };
    struct S6 {
        int a;
    };
    expect_bool("is_layout_compatible_v<S5, S6>", asc::std::is_layout_compatible_v<S5, S6>, false);

    // Struct form (inherits from bool_constant)
    expect_bool("is_layout_compatible<int, int>::value", asc::std::is_layout_compatible<int, int>::value, true);
    expect_bool("is_layout_compatible<int, float>::value", asc::std::is_layout_compatible<int, float>::value, false);
    expect_bool("is_layout_compatible<S1, S2>::value", asc::std::is_layout_compatible<S1, S2>::value, true);

    return g_failures == 0 ? 0 : 1;
}

#endif
