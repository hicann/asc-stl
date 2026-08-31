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

#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_constant_evaluated] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// constexpr context: should return true
constexpr bool ce_test()
{
    return asc::std::is_constant_evaluated();
}

// runtime context: should return false
bool rt_test()
{
    return asc::std::is_constant_evaluated();
}

// constexpr context for default: should return true
constexpr bool ce_default_test()
{
    return asc::std::__accl_default_is_constant_evaluated();
}

// runtime context for default
bool rt_default_test()
{
    return asc::std::__accl_default_is_constant_evaluated();
}

int main()
{
    // static_assert: is_constant_evaluated() in constexpr context
    static_assert(asc::std::is_constant_evaluated(), "constexpr context should return true");
    std::cout << "[host][is_constant_evaluated] static_assert(is_constant_evaluated()) OK" << std::endl;

    // constexpr function called at compile time
    static_assert(ce_test(), "ce_test() should be true");
    std::cout << "[host][is_constant_evaluated] static_assert(ce_test()) OK" << std::endl;

    // runtime call: should be false (when builtin is available)
    expect_true("is_constant_evaluated() at runtime", rt_test(), false);

    // constexpr call to default
    static_assert(ce_default_test(), "ce_default_test() should be true");
    std::cout << "[host][is_constant_evaluated] static_assert(ce_default_test()) OK" << std::endl;

    // runtime call to default: should be false (when builtin is available)
    expect_true("__accl_default_is_constant_evaluated() at runtime", rt_default_test(), false);

    // Direct constexpr usage
    constexpr bool ce_direct = asc::std::is_constant_evaluated();
    expect_true("constexpr bool ce_direct", ce_direct, true);

    // noexcept check
    static_assert(noexcept(asc::std::is_constant_evaluated()), "should be noexcept");
    std::cout << "[host][is_constant_evaluated] noexcept check OK" << std::endl;

    return g_failures == 0 ? 0 : 1;
}
