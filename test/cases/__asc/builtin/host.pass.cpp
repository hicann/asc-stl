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

#include <asc/std/__asc/builtin.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T, typename U>
void expect_eq(const char* expr, T got, U expected)
{
    if (got == expected) {
        std::cout << "[host][builtin] " << expr << " = " << got << " (expected " << expected << ") OK" << std::endl;
    } else {
        std::cout << "[host][builtin] " << expr << " = " << got << " (expected " << expected << ") FAIL" << std::endl;
        ++g_failures;
    }
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][builtin] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    expect_true("CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_abs) is boolean",
        CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_abs) == 0 || CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_abs) == 1);
    expect_true("CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_exceptions) is boolean",
        CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_exceptions) == 0 || CANN_ASC_STL_DETAIL_HAS_FEATURE(cxx_exceptions) == 1);
    expect_true("CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_expect) is boolean",
        CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_expect) == 0 ||
            CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_expect) == 1);

    // From compiler.h: on host (non-CCE), CANN_ASC_STL_DETAIL_HOST_COMPILATION() == 1,
    // CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() == 0
    expect_eq("CANN_ASC_STL_DETAIL_HOST_COMPILATION()", CANN_ASC_STL_DETAIL_HOST_COMPILATION(), 1);
    expect_eq("CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()", CANN_ASC_STL_DETAIL_DEVICE_COMPILATION(), 0);

    expect_eq("CANN_ASC_STL_DETAIL_AICORE_ARCH()", CANN_ASC_STL_DETAIL_AICORE_ARCH(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310()", CANN_ASC_STL_DETAIL_AICORE_ARCH_IS_C310(), 0);

    // From extended_data_types.h: on host, device-specific types are unavailable
    expect_eq("CANN_ASC_STL_DETAIL_HAS_HALF()", CANN_ASC_STL_DETAIL_HAS_HALF(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_BFLOAT16()", CANN_ASC_STL_DETAIL_HAS_BFLOAT16(), 0);
    expect_eq("CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()", CANN_ASC_STL_DETAIL_HAS_FP8_E4M3(), 0);

    // From host_std_lib.h: CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() should be 1 on hosted
    expect_eq("CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()", CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB(), 1);

    // CANN_ASC_STL_DETAIL_HOSTED() / CANN_ASC_STL_DETAIL_FREESTANDING() from compiler.h
    expect_eq("CANN_ASC_STL_DETAIL_HOSTED()", CANN_ASC_STL_DETAIL_HOSTED(), 1);
    expect_eq("CANN_ASC_STL_DETAIL_FREESTANDING()", CANN_ASC_STL_DETAIL_FREESTANDING(), 0);

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF
    {
        int value = 42;
        expect_true("CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF(value) == &value",
            CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF(value) == &value);
    }
#endif

    expect_eq("CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(7, 1)", CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(7, 1), 7);

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_MEMCMP
    expect_eq("CANN_ASC_STL_DETAIL_BUILTIN_MEMCMP(\"abc\", \"abd\", 2)",
        CANN_ASC_STL_DETAIL_BUILTIN_MEMCMP("abc", "abd", 2), 0);
#endif

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_STRLEN
    expect_eq("CANN_ASC_STL_DETAIL_BUILTIN_STRLEN(\"abcd\")",
        static_cast<int>(CANN_ASC_STL_DETAIL_BUILTIN_STRLEN("abcd")), 4);
#endif

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_IS_ARRAY
    expect_true("CANN_ASC_STL_DETAIL_BUILTIN_IS_ARRAY(int[2])", CANN_ASC_STL_DETAIL_BUILTIN_IS_ARRAY(int[2]));
    expect_true("!CANN_ASC_STL_DETAIL_BUILTIN_IS_ARRAY(int)", !CANN_ASC_STL_DETAIL_BUILTIN_IS_ARRAY(int));
#endif

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE
    expect_true("CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE(int, int)",
        CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE(int, int));
#endif

#ifdef CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_REFERENCE_T
    expect_true("CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_REFERENCE_T<int&> is int",
        (std::is_same<CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_REFERENCE_T(int&), int>::value));
#endif

    expect_true("CANN_ASC_STL_DETAIL_BUILTIN_PRETTY_FUNCTION() is non-empty",
        CANN_ASC_STL_DETAIL_BUILTIN_PRETTY_FUNCTION()[0] != '\0');
    return g_failures == 0 ? 0 : 1;
}
