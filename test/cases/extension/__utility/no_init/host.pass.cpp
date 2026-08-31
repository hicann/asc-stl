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

#include <asc/__utility/no_init.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][no_init] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Verify the global constant 'no_init' has the correct type
    expect_true("std::is_same_v<decltype(asc::no_init), const asc::no_init_t>",
        std::is_same_v<decltype(asc::no_init), const asc::no_init_t>);

    // Verify no_init_t is default constructible (explicit constructor)
    expect_true("std::is_default_constructible_v<asc::no_init_t>", std::is_default_constructible_v<asc::no_init_t>);

    // Verify it is a non-empty complete object (size should be at least 1)
    expect_true("sizeof(asc::no_init_t) > 0", sizeof(asc::no_init_t) > 0);

    // Construct an instance explicitly
    asc::no_init_t ni{};
    (void)ni;
    expect_true("instance constructed", true);

    return g_failures == 0 ? 0 : 1;
}
