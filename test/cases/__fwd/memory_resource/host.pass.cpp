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

#include <asc/std/__fwd/memory_resource.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][memory_resource] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Custom SFINAE helper to detect whether a type is complete
template <class T, class = void>
struct is_complete : std::false_type {};

template <class T>
struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

int main()
{
    // Verify the forward-declared class template exists in asc::std::pmr
    using A = asc::std::pmr::polymorphic_allocator<int>;
    expect_true("is class template (instantiable as incomplete type)",
        std::is_same<A, asc::std::pmr::polymorphic_allocator<int>>::value);

    // Can form pointer / reference to incomplete type
    asc::std::pmr::polymorphic_allocator<char>* p = nullptr;
    expect_true("pointer to polymorphic_allocator<char> is null", p == nullptr);

    // Different instantiations are different types
    using B = asc::std::pmr::polymorphic_allocator<double>;
    expect_true("polymorphic_allocator<int> != polymorphic_allocator<double>", !std::is_same<A, B>::value);

    // Verify it is indeed incomplete (forward-declared only)
    expect_true("polymorphic_allocator<int> is incomplete (forward-declared)",
        !is_complete<asc::std::pmr::polymorphic_allocator<int>>::value);

    // Verify nested namespace pmr exists under asc::std
    expect_true("pmr is a namespace under asc::std",
        std::is_same<asc::std::pmr::polymorphic_allocator<int>, asc::std::pmr::polymorphic_allocator<int>>::value);

    return g_failures == 0 ? 0 : 1;
}
