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

#include <asc/std/__new/allocate.h>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstddef>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][allocate] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][allocate] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static size_t compute_threshold()
{
#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
    return __STDCPP_DEFAULT_NEW_ALIGNMENT__;
#else
    return alignof(max_align_t);
#endif
}

static void check_part1()
{
    size_t threshold = compute_threshold();

    // Test __is_overaligned_for_new with various alignments
    expect_eq("__is_overaligned_for_new(1)", asc::std::__is_overaligned_for_new(1), false);
    expect_eq("__is_overaligned_for_new(8)", asc::std::__is_overaligned_for_new(8), false);
    expect_eq("__is_overaligned_for_new(threshold)", asc::std::__is_overaligned_for_new(threshold), false);
    expect_eq("__is_overaligned_for_new(threshold * 2)", asc::std::__is_overaligned_for_new(threshold * 2), true);
    expect_eq("__is_overaligned_for_new(256)", asc::std::__is_overaligned_for_new(256), true);
    expect_eq("__is_overaligned_for_new(1024)", asc::std::__is_overaligned_for_new(1024), true);

    // Test __asc_allocate / __asc_deallocate with normal alignment
    {
        size_t size = 128;
        size_t align = 16;
        void* ptr = asc::std::__asc_allocate(size, align);
        expect_true("__asc_allocate(128, 16) != nullptr", ptr != nullptr);
        if (ptr) {
            std::fill_n(static_cast<unsigned char*>(ptr), size, 0xAB);
            expect_true("ptr aligned to 16", (reinterpret_cast<uintptr_t>(ptr) % align) == 0);
            asc::std::__asc_deallocate(ptr, size, align);
        }
    }

    // Test __asc_allocate / __asc_deallocate with larger alignment
    {
        size_t size = 256;
        size_t align = 64;
        void* ptr = asc::std::__asc_allocate(size, align);
        expect_true("__asc_allocate(256, 64) != nullptr", ptr != nullptr);
        if (ptr) {
            std::fill_n(static_cast<unsigned char*>(ptr), size, 0xCD);
            expect_true("ptr aligned to 64", (reinterpret_cast<uintptr_t>(ptr) % align) == 0);
            asc::std::__asc_deallocate(ptr, size, align);
        }
    }

    // Test __asc_deallocate_unsized
    {
        size_t size = 64;
        size_t align = 8;
        void* ptr = asc::std::__asc_allocate(size, align);
        expect_true("__asc_allocate(64, 8) for unsized dealloc != nullptr", ptr != nullptr);
        if (ptr) {
            std::fill_n(static_cast<unsigned char*>(ptr), size, 0);
            asc::std::__asc_deallocate_unsized(ptr, align);
        }
        std::cout << "[host][allocate] __asc_deallocate_unsized OK" << std::endl;
    }
}

static void check_part2()
{
    // Test __asc_operator_new / __asc_operator_delete
    {
        void* ptr = asc::std::__asc_operator_new(32);
        expect_true("__asc_operator_new(32) != nullptr", ptr != nullptr);
        if (ptr) {
            std::fill_n(static_cast<unsigned char*>(ptr), 32, 0x42);
            asc::std::__asc_operator_delete(ptr);
        }
    }

    // Test allocate with size 0 (edge case)
    {
        void* ptr = asc::std::__asc_allocate(0, 1);
        if (ptr != nullptr) {
            asc::std::__asc_deallocate(ptr, 0, 1);
        }
        std::cout << "[host][allocate] __asc_allocate(0, 1) edge case OK" << std::endl;
    }

    // Test multiple allocate/deallocate cycles
    {
        for (int i = 0; i < 10; ++i) {
            size_t sz = static_cast<size_t>(i + 1) * 16;
            void* ptr = asc::std::__asc_allocate(sz, 16);
            expect_true("cycle allocate != nullptr", ptr != nullptr);
            if (ptr) {
                std::fill_n(static_cast<unsigned char*>(ptr), sz, i);
                asc::std::__asc_deallocate(ptr, sz, 16);
            }
        }
    }
}

int main()
{
    check_part1();
    check_part2();

    return g_failures == 0 ? 0 : 1;
}
