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

#include <asc/std/__type_traits/remove_const_ref.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T, typename Expected>
static void check_type(const char* expr)
{
    using Result = asc::std::__remove_const_ref_t<T>;
    bool ok = std::is_same<Result, Expected>::value;
    std::cout << "[host][remove_const_ref] " << expr << " -> " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    // Basic: no qualifiers
    check_type<int, int>("__remove_const_ref_t<int>");
    check_type<double, double>("__remove_const_ref_t<double>");

    // Reference only
    check_type<int&, int>("__remove_const_ref_t<int&>");
    check_type<int&&, int>("__remove_const_ref_t<int&&>");

    // Const only
    check_type<const int, int>("__remove_const_ref_t<const int>");

    // Const + reference (the key combination)
    check_type<const int&, int>("__remove_const_ref_t<const int&>");
    check_type<const int&&, int>("__remove_const_ref_t<const int&&>");

    // Const + volatile (volatile should survive)
    check_type<const volatile int, volatile int>("__remove_const_ref_t<const volatile int>");

    // Const + volatile + reference
    check_type<const volatile int&, volatile int>("__remove_const_ref_t<const volatile int&>");

    // Pointer to const (pointer itself is not const)
    check_type<const int*, const int*>("__remove_const_ref_t<const int*>");

    // Const pointer to const int
    check_type<const int* const, const int*>("__remove_const_ref_t<const int* const>");

    return g_failures == 0 ? 0 : 1;
}
