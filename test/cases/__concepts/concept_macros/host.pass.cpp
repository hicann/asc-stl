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

#include <asc/std/__concepts/concept_macros.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][concept_macros] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Test CANN_ASC_STL_DETAIL_ACCL_TEMPLATE / CANN_ASC_STL_DETAIL_ACCL_REQUIRES
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class T)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(std::is_integral<T>::value)
T increment(T t)
{
    return t + 1;
}

// Test CANN_ASC_STL_DETAIL_ACCL_CONCEPT
template <class T>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT IsIntegral = std::is_integral<T>::value;

int main()
{
    expect_true("__asc_enable_if_t<true, int> is int", std::is_same<__asc_enable_if_t<true, int>, int>::value);
    expect_true("__asc_enable_if_t<true> is void", std::is_same<__asc_enable_if_t<true>, void>::value);

    expect_true("increment(1) == 2", increment(1) == 2);

    expect_true("IsIntegral<int>", IsIntegral<int>);
    expect_true("!IsIntegral<float>", !IsIntegral<float>);

    // Test __asc_unused
    __asc_unused(42);

    return g_failures == 0 ? 0 : 1;
}
