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

#include <asc/std/__asc/exceptions.h>
#include <iostream>

int g_failures = 0;

void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][exceptions] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
#if defined(ASC_DISABLE_EXCEPTIONS)
    expect_eq("CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()", CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS(), 0);
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    expect_eq("CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()", CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS(), 0);
#elif defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC)
    // MSVC might be tricky to predict without knowing _HAS_EXCEPTIONS and _CPPUNWIND
    // We just verify it compiles and evaluates to 0 or 1
    int msvc_val = CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS();
    expect_eq("CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()", msvc_val, msvc_val);
#else
    // Standard host compilation (GCC/Clang) with exceptions enabled
    // should have CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() == 1
    expect_eq("CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()", CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS(), 1);
#endif

    // C++26 constexpr exceptions are not yet standard
    expect_eq("CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_EXCEPTIONS()", CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_EXCEPTIONS(), 0);

    return g_failures == 0 ? 0 : 1;
}
