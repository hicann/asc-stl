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

#include <asc/std/__iterator/default_sentinel.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][default_sentinel] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // 1. default_sentinel_t is default-constructible
    expect_true("std::is_default_constructible<default_sentinel_t>",
        std::is_default_constructible<asc::std::default_sentinel_t>::value);

    // 2. default_sentinel is a constexpr variable of type default_sentinel_t
    {
        constexpr asc::std::default_sentinel_t sentinel_copy = asc::std::default_sentinel;
        (void)sentinel_copy;
        expect_true("default_sentinel is usable in a constant expression", true);
    }

    // 3. default_sentinel_t is empty and trivially copyable
    expect_true("std::is_empty<default_sentinel_t>", std::is_empty<asc::std::default_sentinel_t>::value);
    expect_true("std::is_trivially_copyable<default_sentinel_t>",
        std::is_trivially_copyable<asc::std::default_sentinel_t>::value);

    // 4. default_sentinel_t is copy-constructible and move-constructible
    expect_true("std::is_copy_constructible<default_sentinel_t>",
        std::is_copy_constructible<asc::std::default_sentinel_t>::value);
    expect_true("std::is_move_constructible<default_sentinel_t>",
        std::is_move_constructible<asc::std::default_sentinel_t>::value);

    // 5. sizeof(default_sentinel_t) == 1 (empty class)
    expect_true("sizeof(default_sentinel_t) == 1", sizeof(asc::std::default_sentinel_t) == 1);

    // 6. default_sentinel can be used to copy-construct a default_sentinel_t
    {
        asc::std::default_sentinel_t s = asc::std::default_sentinel;
        (void)s;
        expect_true("default_sentinel_t copy from default_sentinel", true);
    }

    // 7. The global default_sentinel address is stable
    {
        const asc::std::default_sentinel_t* p1 = &asc::std::default_sentinel;
        const asc::std::default_sentinel_t* p2 = &asc::std::default_sentinel;
        expect_true("&default_sentinel == &default_sentinel (same address)", p1 == p2);
    }

    // 8. default_sentinel_t can be default-constructed independently
    {
        asc::std::default_sentinel_t a{};
        asc::std::default_sentinel_t b{};
        (void)a;
        (void)b;
        expect_true("default_sentinel_t default-constructed instances", true);
    }

    return g_failures == 0 ? 0 : 1;
}
