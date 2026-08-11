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

#include <asc/std/__type_traits/dependent_type.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][dependent_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][dependent_type] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][dependent_type] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct CustomBase {
    using type = long;
    static constexpr int value = 17;
    int member = 23;
};

int main()
{
    using asc_true = asc::std::true_type;
    using asc_false = asc::std::false_type;

    // 1. __dependent_type<T, B> inherits from T regardless of B
    //    Use std::is_base_of as independent oracle
    expect_true("is_base_of<true_type, __dependent_type<true_type, true>>",
        (std::is_base_of<asc_true, asc::std::__dependent_type<asc_true, true>>::value));
    expect_true("is_base_of<true_type, __dependent_type<true_type, false>>",
        (std::is_base_of<asc_true, asc::std::__dependent_type<asc_true, false>>::value));
    expect_true("is_base_of<false_type, __dependent_type<false_type, true>>",
        (std::is_base_of<asc_false, asc::std::__dependent_type<asc_false, true>>::value));
    expect_true("is_base_of<false_type, __dependent_type<false_type, false>>",
        (std::is_base_of<asc_false, asc::std::__dependent_type<asc_false, false>>::value));

    // 2. The bool parameter does NOT affect the inherited value
    expect_true("__dependent_type<true_type, true>::value", asc::std::__dependent_type<asc_true, true>::value);
    expect_true("__dependent_type<true_type, false>::value", asc::std::__dependent_type<asc_true, false>::value);
    expect_false("__dependent_type<false_type, true>::value", asc::std::__dependent_type<asc_false, true>::value);
    expect_false("__dependent_type<false_type, false>::value", asc::std::__dependent_type<asc_false, false>::value);

    // 3. __dependent_type preserves integral_constant value
    using IC42 = asc::std::integral_constant<int, 42>;
    expect_eq("__dependent_type<IC42, true>::value", asc::std::__dependent_type<IC42, true>::value, 42);
    expect_eq("__dependent_type<IC42, false>::value", asc::std::__dependent_type<IC42, false>::value, 42);

    // 4. __dependent_type is convertible to its base (derived-to-base)
    expect_true("is_convertible<__dependent_type<true_type,true>, true_type>",
        std::is_convertible<asc::std::__dependent_type<asc_true, true>, asc_true>::value);
    expect_true("is_convertible<__dependent_type<IC42,false>, IC42>",
        std::is_convertible<asc::std::__dependent_type<IC42, false>, IC42>::value);

    // 5. __dependent_type is NOT the same type as T (it's a derived type)
    expect_false("is_same<__dependent_type<true_type,true>, true_type>",
        std::is_same<asc::std::__dependent_type<asc_true, true>, asc_true>::value);
    expect_false("is_same<__dependent_type<true_type,false>, true_type>",
        std::is_same<asc::std::__dependent_type<asc_true, false>, asc_true>::value);
    expect_false("true and false dependent instances are distinct",
        std::is_same<asc::std::__dependent_type<asc_true, true>, asc::std::__dependent_type<asc_true, false>>::value);

    // 6. Cross-check with std::is_base_of on a non-bool integral_constant
    expect_true("std::is_base_of<IC42, __dependent_type<IC42,true>> (oracle)",
        std::is_base_of<IC42, asc::std::__dependent_type<IC42, true>>::value);
    expect_true("std::is_base_of<IC42, __dependent_type<IC42,false>> (oracle)",
        std::is_base_of<IC42, asc::std::__dependent_type<IC42, false>>::value);

    // 7. A general base's nested type, static value, and instance member are inherited.
    using CustomTrue = asc::std::__dependent_type<CustomBase, true>;
    using CustomFalse = asc::std::__dependent_type<CustomBase, false>;
    expect_true("CustomTrue::type is long", std::is_same<typename CustomTrue::type, long>::value);
    expect_true("CustomFalse::type is long", std::is_same<typename CustomFalse::type, long>::value);
    expect_eq("CustomTrue::value", CustomTrue::value, 17);
    expect_eq("CustomFalse::value", CustomFalse::value, 17);
    expect_eq("CustomTrue{}.member", CustomTrue{}.member, 23);
    expect_eq("CustomFalse{}.member", CustomFalse{}.member, 23);

    return g_failures == 0 ? 0 : 1;
}
