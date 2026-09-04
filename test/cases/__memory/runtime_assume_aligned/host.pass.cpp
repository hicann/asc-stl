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

#include <asc/std/__memory/runtime_assume_aligned.h>
#include <iostream>
#include <cstdint>
#include <cstddef>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][runtime_assume_aligned] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][runtime_assume_aligned] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Test 1: Basic identity — returned pointer equals input pointer (int, align 32)
    {
        alignas(32) int data[4] = {10, 20, 30, 40};
        int* ptr = data;
        int* result = asc::std::__runtime_assume_aligned(ptr, 32);
        expect_true("aligned(ptr,32)==ptr", result == ptr);
        expect_eq("*result", *result, 10);
    }

    // Test 2: Various alignment values on 32-aligned double data
    {
        alignas(32) double data[4] = {1.0, 2.0, 3.0, 4.0};
        double* ptr = data;
        for (std::size_t a : {1u, 2u, 4u, 8u, 16u, 32u}) {
            double* result = asc::std::__runtime_assume_aligned(ptr, a);
            expect_true("aligned(ptr,a)==ptr", result == ptr);
        }
        expect_eq("data[0] via aligned(ptr,8)", *asc::std::__runtime_assume_aligned(ptr, 8), 1.0);
    }

    // Test 3: Volatile type support (remove_volatile_t path)
    {
        alignas(32) volatile int data[4] = {100, 200, 300, 400};
        volatile int* ptr = data;
        volatile int* result = asc::std::__runtime_assume_aligned(ptr, 32);
        expect_true("volatile: result==ptr", result == ptr);
        expect_eq("volatile *result", static_cast<int>(*result), 100);
    }

    // Test 4: char type with alignment 1
    {
        alignas(32) char data[32] = {};
        data[0] = 'A';
        char* ptr = data;
        char* result = asc::std::__runtime_assume_aligned(ptr, 1);
        expect_true("char: aligned(ptr,1)==ptr", result == ptr);
        expect_eq("*result", static_cast<int>(*result), static_cast<int>('A'));
    }

    // Test 5: int64_t with alignment 8
    {
        alignas(32) int64_t data[4] = {0x123456789ABCDEF0LL, 0, 0, 0};
        int64_t* ptr = data;
        int64_t* result = asc::std::__runtime_assume_aligned(ptr, 8);
        expect_true("int64_t: aligned(ptr,8)==ptr", result == ptr);
        expect_eq("*result", *result, static_cast<int64_t>(0x123456789ABCDEF0LL));
    }

    // Test 6: [[nodiscard]] — result must be captured; verify identity on stack var
    {
        alignas(32) int x = 42;
        int* r = asc::std::__runtime_assume_aligned(&x, 4);
        expect_true("nodiscard: r==&x", r == &x);
        expect_eq("*r", *r, 42);
    }

    // Test 7: Pointer arithmetic through result — data[2] via offset
    {
        alignas(32) int data[4] = {5, 10, 15, 20};
        int* base = asc::std::__runtime_assume_aligned(data, 16);
        expect_eq("base[2]", base[2], 15);
    }

    return g_failures == 0 ? 0 : 1;
}
