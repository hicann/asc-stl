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

#include <asc/std/__expected/unexpect.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][unexpect] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // 1. unexpect_t is default-constructible (explicitly)
    {
        asc::std::unexpect_t u{};
        (void)u;
        expect_true("unexpect_t default-constructible", true);
    }

    // 2. unexpect is of type unexpect_t (constexpr implies const, so decltype is const unexpect_t)
    expect_true("is_same<remove_const_t<decltype(unexpect)>, unexpect_t>",
        std::is_same<std::remove_const_t<decltype(asc::std::unexpect)>, asc::std::unexpect_t>::value);

    // 3. unexpect_t is trivially default constructible
    //    An explicitly defaulted constructor (explicit unexpect_t() = default) is NOT user-provided,
    //    so the struct remains trivially default constructible. The 'explicit' keyword only
    //    affects implicit conversion, not triviality.
    expect_true("is_trivially_default_constructible<unexpect_t>",
        std::is_trivially_default_constructible<asc::std::unexpect_t>::value);

    // 4. unexpect_t is default constructible
    expect_true("is_default_constructible<unexpect_t>", std::is_default_constructible<asc::std::unexpect_t>::value);

    // 5. Two instances are the same type
    {
        asc::std::unexpect_t a{};
        asc::std::unexpect_t b{};
        expect_true("is_same<decltype(a), decltype(b)>", std::is_same<decltype(a), decltype(b)>::value);
    }

    // 6. unexpect global constant is usable as a tag
    {
        auto tag = asc::std::unexpect;
        expect_true("is_same<decltype(tag), unexpect_t>", std::is_same<decltype(tag), asc::std::unexpect_t>::value);
    }

    // 7. unexpect_t is constructible
    expect_true("is_constructible<unexpect_t>", std::is_constructible<asc::std::unexpect_t>::value);

    // 8. Verify address of unexpect is valid and stable
    {
        const asc::std::unexpect_t* p1 = &asc::std::unexpect;
        const asc::std::unexpect_t* p2 = &asc::std::unexpect;
        expect_true("&unexpect == &unexpect (same address)", p1 == p2);
    }

    return g_failures == 0 ? 0 : 1;
}
