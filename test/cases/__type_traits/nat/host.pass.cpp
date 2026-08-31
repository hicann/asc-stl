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

#include <asc/std/__type_traits/nat.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][nat] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][nat] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    using N = asc::std::__nat;

    // __nat must not be default constructible
    expect_false("is_default_constructible<__nat>", std::is_default_constructible<N>::value);

    // __nat must not be copy constructible
    expect_false("is_copy_constructible<__nat>", std::is_copy_constructible<N>::value);

    // __nat must not be copy assignable
    expect_false("is_copy_assignable<__nat>", std::is_copy_assignable<N>::value);

    // __nat must not be destructible (deleted destructor)
    expect_false("is_destructible<__nat>", std::is_destructible<N>::value);

    // __nat must not be move constructible (suppressed by deleted copy ctor)
    expect_false("is_move_constructible<__nat>", std::is_move_constructible<N>::value);

    // __nat must not be move assignable (suppressed by deleted copy assignment)
    expect_false("is_move_assignable<__nat>", std::is_move_assignable<N>::value);

    // __nat is a complete type
    expect_true("sizeof(__nat) >= 1", sizeof(N) >= 1);

    // In C++17, deleted special members are not user-provided, so __nat is
    // still an aggregate (no user-provided/explicit/inherited constructors,
    // no private/protected data members, no virtual functions, no base classes).
    expect_true("is_aggregate<__nat>", std::is_aggregate<N>::value);

    // __nat is not trivially default constructible (default ctor is deleted)
    expect_false("is_trivially_default_constructible<__nat>", std::is_trivially_default_constructible<N>::value);

    return g_failures == 0 ? 0 : 1;
}
