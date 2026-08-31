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

#include <asc/std/__utility/piecewise_construct.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][piecewise_construct] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// A test struct that uses piecewise_construct_t as a tag for overload resolution
struct Widget {
    int mode;
    Widget() : mode(0)
    {}
    Widget(asc::std::piecewise_construct_t) : mode(1)  // NOLINT(runtime/explicit)
    {}
};

int main()
{
    // 1. Type identity of the global constant (constexpr => const-qualified)
    expect_true("is_same<remove_const_t<decltype(piecewise_construct)>, piecewise_construct_t>",
        (std::is_same<std::remove_const_t<decltype(asc::std::piecewise_construct)>,
            asc::std::piecewise_construct_t>::value));

    // 2. Default constructibility (explicit)
    expect_true("is_default_constructible<piecewise_construct_t>",
        std::is_default_constructible<asc::std::piecewise_construct_t>::value);

    // 3. The type is empty (no data members)
    expect_true("is_empty<piecewise_construct_t>", std::is_empty<asc::std::piecewise_construct_t>::value);

    // 4. Explicit construction works
    asc::std::piecewise_construct_t t{};
    (void)t;

    // 5. The global constant is usable as a value
    asc::std::piecewise_construct_t t2 = asc::std::piecewise_construct;
    (void)t2;
    expect_true("global constant usable", true);

    // 6. Tag-based overload resolution
    Widget w1;
    expect_true("default ctor mode == 0", w1.mode == 0);

    Widget w2(asc::std::piecewise_construct);
    expect_true("piecewise ctor mode == 1", w2.mode == 1);

    Widget w3{asc::std::piecewise_construct_t{}};
    expect_true("piecewise ctor (explicit type) mode == 1", w3.mode == 1);

    return g_failures == 0 ? 0 : 1;
}
