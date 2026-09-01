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

#include <asc/std/__functional/operations_traits.h>
#include <iostream>
#include <functional>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][operations_traits] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][operations_traits] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Compile-time verification
static_assert(asc::std::__is_plus_op_v<asc::std::plus<>>, "plus<> should be recognized as plus op");
static_assert(!asc::std::__is_plus_op_v<asc::std::minus<>>, "minus<> should not be recognized as plus op");
static_assert(
    asc::std::__is_multiplies_op_v<asc::std::multiplies<>>, "multiplies<> should be recognized as multiplies op");
static_assert(asc::std::__is_bit_and_op_v<asc::std::bit_and<>>, "bit_and<> should be recognized as bit_and op");
static_assert(asc::std::__is_bit_or_op_v<asc::std::bit_or<>>, "bit_or<> should be recognized as bit_or op");
static_assert(asc::std::__is_bit_xor_op_v<asc::std::bit_xor<>>, "bit_xor<> should be recognized as bit_xor op");

int main()
{
    // === __is_plus_op_v ===
    expect_true("__is_plus_op_v<asc::std::plus<>>", asc::std::__is_plus_op_v<asc::std::plus<>>);
    expect_true("__is_plus_op_v<std::plus<void>>", asc::std::__is_plus_op_v<std::plus<void>>);
    expect_false("__is_plus_op_v<asc::std::minus<>>", asc::std::__is_plus_op_v<asc::std::minus<>>);
    expect_false("__is_plus_op_v<asc::std::multiplies<>>", asc::std::__is_plus_op_v<asc::std::multiplies<>>);
    expect_false("__is_plus_op_v<asc::std::plus<int>>", asc::std::__is_plus_op_v<asc::std::plus<int>>);
    expect_false("__is_plus_op_v<int>", asc::std::__is_plus_op_v<int>);

    // === __is_multiplies_op_v ===
    expect_true("__is_multiplies_op_v<asc::std::multiplies<>>", asc::std::__is_multiplies_op_v<asc::std::multiplies<>>);
    expect_true("__is_multiplies_op_v<std::multiplies<void>>", asc::std::__is_multiplies_op_v<std::multiplies<void>>);
    expect_false("__is_multiplies_op_v<asc::std::plus<>>", asc::std::__is_multiplies_op_v<asc::std::plus<>>);
    expect_false("__is_multiplies_op_v<asc::std::divides<>>", asc::std::__is_multiplies_op_v<asc::std::divides<>>);
    expect_false(
        "__is_multiplies_op_v<asc::std::multiplies<int>>", asc::std::__is_multiplies_op_v<asc::std::multiplies<int>>);
    expect_false("__is_multiplies_op_v<double>", asc::std::__is_multiplies_op_v<double>);

    // === __is_bit_and_op_v ===
    expect_true("__is_bit_and_op_v<asc::std::bit_and<>>", asc::std::__is_bit_and_op_v<asc::std::bit_and<>>);
    expect_true("__is_bit_and_op_v<std::bit_and<void>>", asc::std::__is_bit_and_op_v<std::bit_and<void>>);
    expect_false("__is_bit_and_op_v<asc::std::bit_or<>>", asc::std::__is_bit_and_op_v<asc::std::bit_or<>>);
    expect_false("__is_bit_and_op_v<asc::std::plus<>>", asc::std::__is_bit_and_op_v<asc::std::plus<>>);
    expect_false("__is_bit_and_op_v<asc::std::bit_and<int>>", asc::std::__is_bit_and_op_v<asc::std::bit_and<int>>);
    expect_false("__is_bit_and_op_v<char>", asc::std::__is_bit_and_op_v<char>);

    // === __is_bit_or_op_v ===
    expect_true("__is_bit_or_op_v<asc::std::bit_or<>>", asc::std::__is_bit_or_op_v<asc::std::bit_or<>>);
    expect_true("__is_bit_or_op_v<std::bit_or<void>>", asc::std::__is_bit_or_op_v<std::bit_or<void>>);
    expect_false("__is_bit_or_op_v<asc::std::bit_and<>>", asc::std::__is_bit_or_op_v<asc::std::bit_and<>>);
    expect_false("__is_bit_or_op_v<asc::std::bit_xor<>>", asc::std::__is_bit_or_op_v<asc::std::bit_xor<>>);
    expect_false("__is_bit_or_op_v<asc::std::bit_or<int>>", asc::std::__is_bit_or_op_v<asc::std::bit_or<int>>);
    expect_false("__is_bit_or_op_v<long>", asc::std::__is_bit_or_op_v<long>);

    // === __is_bit_xor_op_v ===
    expect_true("__is_bit_xor_op_v<asc::std::bit_xor<>>", asc::std::__is_bit_xor_op_v<asc::std::bit_xor<>>);
    expect_true("__is_bit_xor_op_v<std::bit_xor<void>>", asc::std::__is_bit_xor_op_v<std::bit_xor<void>>);
    expect_false("__is_bit_xor_op_v<asc::std::bit_or<>>", asc::std::__is_bit_xor_op_v<asc::std::bit_or<>>);
    expect_false("__is_bit_xor_op_v<asc::std::bit_and<>>", asc::std::__is_bit_xor_op_v<asc::std::bit_and<>>);
    expect_false("__is_bit_xor_op_v<asc::std::bit_xor<int>>", asc::std::__is_bit_xor_op_v<asc::std::bit_xor<int>>);
    expect_false("__is_bit_xor_op_v<short>", asc::std::__is_bit_xor_op_v<short>);

    return g_failures == 0 ? 0 : 1;
}
