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

#include <asc/std/__functional/operations.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][operations] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][operations] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][operations] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

static void check_part1()
{
    // --- Arithmetic operations (typed) ---
    {
        asc::std::plus<int> f;
        expect_eq("plus<int>()(3, 4)", f(3, 4), 7);
        expect_eq("plus<int>()(-2, 5)", f(-2, 5), 3);
    }
    {
        asc::std::minus<int> f;
        expect_eq("minus<int>()(10, 4)", f(10, 4), 6);
        expect_eq("minus<int>()(2, 5)", f(2, 5), -3);
    }
    {
        asc::std::multiplies<int> f;
        expect_eq("multiplies<int>()(3, 4)", f(3, 4), 12);
        expect_eq("multiplies<int>()(-2, 5)", f(-2, 5), -10);
    }
    {
        asc::std::divides<int> f;
        expect_eq("divides<int>()(10, 4)", f(10, 4), 2);
        expect_eq("divides<int>()(-10, 3)", f(-10, 3), -3);
    }
    {
        asc::std::modulus<int> f;
        expect_eq("modulus<int>()(10, 3)", f(10, 3), 1);
        expect_eq("modulus<int>()(-10, 3)", f(-10, 3), -1);
    }
    {
        asc::std::negate<int> f;
        expect_eq("negate<int>()(5)", f(5), -5);
        expect_eq("negate<int>()(-7)", f(-7), 7);
    }

    // --- Arithmetic operations (void) ---
    {
        asc::std::plus<> f;
        expect_eq("plus<>()(3, 4)", f(3, 4), 7);
        expect_eq("plus<>()(2.5, 1.5)", f(2.5, 1.5), 4.0);
    }
    {
        asc::std::minus<> f;
        expect_eq("minus<>()(10.5, 0.5)", f(10.5, 0.5), 10.0);
    }
}

static void check_part2()
{
    {
        asc::std::multiplies<> f;
        expect_eq("multiplies<>()(2.5, 2.0)", f(2.5, 2.0), 5.0);
    }
    {
        asc::std::divides<> f;
        expect_eq("divides<>()(7.5, 2.5)", f(7.5, 2.5), 3.0);
    }
    {
        asc::std::modulus<> f;
        expect_eq("modulus<>()(10, 3)", f(10, 3), 1);
    }
    {
        asc::std::negate<> f;
        expect_eq("negate<>()(5)", f(5), -5);
        expect_eq("negate<>()(-3.5)", f(-3.5), 3.5);
    }

    // --- Bitwise operations (typed) ---
    {
        asc::std::bit_and<int> f;
        expect_eq("bit_and<int>()(0b1100, 0b1010)", f(0b1100, 0b1010), 0b1000);
    }
    {
        asc::std::bit_or<int> f;
        expect_eq("bit_or<int>()(0b1100, 0b1010)", f(0b1100, 0b1010), 0b1110);
    }
    {
        asc::std::bit_xor<int> f;
        expect_eq("bit_xor<int>()(0b1100, 0b1010)", f(0b1100, 0b1010), 0b0110);
    }
    {
        asc::std::bit_not<int> f;
        expect_eq("bit_not<int>()(0b1100)", f(0b1100), ~0b1100);
    }

    // --- Bitwise operations (void) ---
    {
        asc::std::bit_and<> f;
        expect_eq("bit_and<>()(0b1100, 0b1010)", f(0b1100, 0b1010), 0b1000);
    }
}

static void check_part3()
{
    {
        asc::std::bit_or<> f;
        expect_eq("bit_or<>()(0b1100, 0b1010)", f(0b1100, 0b1010), 0b1110);
    }
    {
        asc::std::bit_xor<> f;
        expect_eq("bit_xor<>()(0b1100, 0b1010)", f(0b1100, 0b1010), 0b0110);
    }
    {
        asc::std::bit_not<> f;
        expect_eq("bit_not<>()(0b1100)", f(0b1100), ~0b1100);
    }

    // --- Comparison operations (typed) ---
    {
        asc::std::equal_to<int> f;
        expect_true("equal_to<int>()(3, 3)", f(3, 3));
        expect_false("equal_to<int>()(3, 4)", f(3, 4));
    }
    {
        asc::std::not_equal_to<int> f;
        expect_true("not_equal_to<int>()(3, 4)", f(3, 4));
        expect_false("not_equal_to<int>()(3, 3)", f(3, 3));
    }
    {
        asc::std::less<int> f;
        expect_true("less<int>()(3, 4)", f(3, 4));
        expect_false("less<int>()(4, 3)", f(4, 3));
        expect_false("less<int>()(3, 3)", f(3, 3));
    }
    {
        asc::std::less_equal<int> f;
        expect_true("less_equal<int>()(3, 4)", f(3, 4));
        expect_true("less_equal<int>()(3, 3)", f(3, 3));
        expect_false("less_equal<int>()(4, 3)", f(4, 3));
    }
    {
        asc::std::greater_equal<int> f;
        expect_true("greater_equal<int>()(4, 3)", f(4, 3));
        expect_true("greater_equal<int>()(3, 3)", f(3, 3));
        expect_false("greater_equal<int>()(3, 4)", f(3, 4));
    }
}

static void check_part4()
{
    {
        asc::std::greater<int> f;
        expect_true("greater<int>()(4, 3)", f(4, 3));
        expect_false("greater<int>()(3, 4)", f(3, 4));
        expect_false("greater<int>()(3, 3)", f(3, 3));
    }

    // --- Comparison operations (void) ---
    {
        asc::std::equal_to<> f;
        expect_true("equal_to<>()(3, 3)", f(3, 3));
        expect_false("equal_to<>()(3, 4)", f(3, 4));
    }
    {
        asc::std::less<> f;
        expect_true("less<>()(3, 4)", f(3, 4));
        expect_false("less<>()(4, 3)", f(4, 3));
    }
    {
        asc::std::greater<> f;
        expect_true("greater<>()(4, 3)", f(4, 3));
        expect_false("greater<>()(3, 4)", f(3, 4));
    }

    // --- Logical operations (typed) ---
    {
        asc::std::logical_and<int> f;
        expect_true("logical_and<int>()(1, 1)", f(1, 1));
        expect_false("logical_and<int>()(1, 0)", f(1, 0));
        expect_false("logical_and<int>()(0, 1)", f(0, 1));
    }
    {
        asc::std::logical_or<int> f;
        expect_true("logical_or<int>()(1, 0)", f(1, 0));
        expect_true("logical_or<int>()(0, 1)", f(0, 1));
        expect_false("logical_or<int>()(0, 0)", f(0, 0));
    }
    {
        asc::std::logical_not<int> f;
        expect_true("logical_not<int>()(0)", f(0));
        expect_false("logical_not<int>()(5)", f(5));
    }
}

static void check_part5()
{
    // --- Logical operations (void) ---
    {
        asc::std::logical_and<> f;
        expect_true("logical_and<>()(true, true)", f(true, true));
        expect_false("logical_and<>()(true, false)", f(true, false));
    }
    {
        asc::std::logical_or<> f;
        expect_true("logical_or<>()(true, false)", f(true, false));
        expect_false("logical_or<>()(false, false)", f(false, false));
    }
    {
        asc::std::logical_not<> f;
        expect_true("logical_not<>()(false)", f(false));
        expect_false("logical_not<>()(true)", f(true));
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();
    check_part4();
    check_part5();

    return g_failures == 0 ? 0 : 1;
}
