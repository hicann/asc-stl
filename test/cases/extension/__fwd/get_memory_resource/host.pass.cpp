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

#include <asc/__fwd/get_memory_resource.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][get_memory_resource] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Verify that asc::mr::__get_memory_resource_t is declared
    asc::mr::__get_memory_resource_t* p = nullptr;
    expect_true("asc::mr::__get_memory_resource_t* p == nullptr", p == nullptr);

    // Verify it is the correct type
    using T = decltype(p);
    expect_true("std::is_same<T, asc::mr::__get_memory_resource_t*>::value",
        (std::is_same<T, asc::mr::__get_memory_resource_t*>::value));

    return g_failures == 0 ? 0 : 1;
}
