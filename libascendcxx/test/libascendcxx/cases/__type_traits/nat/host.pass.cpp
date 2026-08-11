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

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    const bool ok = got == expected;
    std::cout << "[host][nat] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok) {
        ++g_failures;
    }
}

int main()
{
    using Nat = asc::std::__nat;

    expect_eq("is_default_constructible_v<__nat>", std::is_default_constructible_v<Nat>, false);
    expect_eq("is_copy_constructible_v<__nat>", std::is_copy_constructible_v<Nat>, false);
    expect_eq("is_move_constructible_v<__nat>", std::is_move_constructible_v<Nat>, false);
    expect_eq("is_copy_assignable_v<__nat>", std::is_copy_assignable_v<Nat>, false);
    expect_eq("is_move_assignable_v<__nat>", std::is_move_assignable_v<Nat>, false);
    expect_eq("is_destructible_v<__nat>", std::is_destructible_v<Nat>, false);
    expect_eq("is_trivially_destructible_v<__nat>", std::is_trivially_destructible_v<Nat>, false);

    expect_eq("is_empty_v<__nat>", std::is_empty_v<Nat>, true);
    expect_eq("is_class_v<__nat>", std::is_class_v<Nat>, true);
    expect_eq("sizeof(__nat) > 0", sizeof(Nat) > 0, true);

    expect_eq("is_constructible_v<__nat>", std::is_constructible_v<Nat>, false);
    expect_eq("is_constructible_v<__nat, int>", std::is_constructible_v<Nat, int>, false);
    expect_eq("is_assignable_v<__nat&, const __nat&>", std::is_assignable_v<Nat&, const Nat&>, false);

    static_assert(!std::is_default_constructible_v<Nat>, "");
    static_assert(!std::is_copy_constructible_v<Nat>, "");
    static_assert(!std::is_move_constructible_v<Nat>, "");
    static_assert(!std::is_copy_assignable_v<Nat>, "");
    static_assert(!std::is_move_assignable_v<Nat>, "");
    static_assert(!std::is_destructible_v<Nat>, "");

    return g_failures == 0 ? 0 : 1;
}
