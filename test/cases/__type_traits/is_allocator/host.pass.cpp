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

#include <asc/std/__type_traits/is_allocator.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_allocator] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// A proper allocator-like type
struct MyAlloc {
    using value_type = int;
    int* allocate(size_t n)
    {
        return static_cast<int*>(::operator new(n * sizeof(int)));
    }
    void deallocate(int* p, size_t)
    {
        ::operator delete(p);
    }
};

// Has value_type but no allocate method
struct HasValueTypeOnly {
    using value_type = double;
};

// Has allocate method but no value_type
struct HasAllocateOnly {
    int* allocate(size_t n)
    {
        return static_cast<int*>(::operator new(n * sizeof(int)));
    }
};

// Empty type
struct Empty {};

// Non-allocator with unrelated members
struct RandomType {
    int x;
    double y;
};

int main()
{
    // true_type / false_type tests
    expect_true("__is_allocator<MyAlloc>::value", asc::std::__is_allocator<MyAlloc>::value, true);
    expect_true("__is_allocator<MyAlloc>()", asc::std::__is_allocator<MyAlloc>()(), true);

    expect_true("__is_allocator<HasValueTypeOnly>::value", asc::std::__is_allocator<HasValueTypeOnly>::value, false);
    expect_true("__is_allocator<HasAllocateOnly>::value", asc::std::__is_allocator<HasAllocateOnly>::value, false);
    expect_true("__is_allocator<Empty>::value", asc::std::__is_allocator<Empty>::value, false);
    expect_true("__is_allocator<RandomType>::value", asc::std::__is_allocator<RandomType>::value, false);
    expect_true("__is_allocator<int>::value", asc::std::__is_allocator<int>::value, false);
    expect_true("__is_allocator<double>::value", asc::std::__is_allocator<double>::value, false);

    // Standard allocator types
    expect_true(
        "__is_allocator<std::allocator<int>>::value", asc::std::__is_allocator<std::allocator<int>>::value, true);
    expect_true(
        "__is_allocator<std::allocator<double>>::value", asc::std::__is_allocator<std::allocator<double>>::value, true);
    expect_true("__is_allocator<std::vector<int>::allocator_type>::value",
        asc::std::__is_allocator<std::vector<int>::allocator_type>::value, true);
    expect_true("__is_allocator<std::string::allocator_type>::value",
        asc::std::__is_allocator<std::string::allocator_type>::value, true);

    // Inherited true_type / false_type semantics
    expect_true("__is_allocator<MyAlloc> inherits true_type",
        std::is_base_of<asc::std::true_type, asc::std::__is_allocator<MyAlloc>>::value, true);
    expect_true("__is_allocator<Empty> inherits false_type",
        std::is_base_of<asc::std::false_type, asc::std::__is_allocator<Empty>>::value, true);

    return g_failures == 0 ? 0 : 1;
}
