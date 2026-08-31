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

#include <asc/std/__type_traits/is_primary_template.h>
#include <iterator>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_primary_template] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// A user-defined iterator that does NOT have __accl_primary_template
struct UserIter {
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;
    int& operator*() const;
    UserIter& operator++();
    UserIter operator++(int);
    bool operator==(const UserIter&) const;
};

// A custom traits type for __select_traits testing
struct CustomTraits {};

static void test_primary_accl_template_int()
{
    // __is_primary_accl_template: for int*, iterator_traits<int*> should be the
    // primary template if it has __accl_primary_template member.
    // Result depends on whether asc::std::iterator_traits<int*> defines __accl_primary_template.
    // We test that it compiles and yields a bool.
    {
        bool val = asc::std::__is_primary_accl_template<int*>::value;
        std::cout << "[host][is_primary_template] __is_primary_accl_template<int*>::value = " << val << std::endl;
    }
}

static void test_user_iterator_without_accl()
{
    // For a user-defined iterator without __accl_primary_template, should be false
    {
        bool val = asc::std::__is_primary_accl_template<UserIter>::value;
        expect_eq("__is_primary_accl_template<UserIter>::value", val, false);
    }
}

static void test_primary_std_template_int()
{
    // __is_primary_std_template: for int* (a pointer), should be true
    // because the pointer specialization forces __is_primary_std_template_impl<Iter, true> = true
    {
        bool val = asc::std::__is_primary_std_template<int*>::value;
        expect_eq("__is_primary_std_template<int*>::value", val, true);
    }
}

static void test_user_iterator_standard_iterator()
{
    // For a user-defined iterator with standard iterator_traits, __is_primary_std_template
    // checks if std::iterator_traits<UserIter> is the primary template.
    // Since UserIter has the 5 required typedefs, std::iterator_traits<UserIter> should be primary.
    {
        bool val = asc::std::__is_primary_std_template<UserIter>::value;
        std::cout << "[host][is_primary_template] __is_primary_std_template<UserIter>::value = " << val << std::endl;
    }
}

static void test_select_traits_both_primary()
{
    // __select_traits: when both __is_primary_std_template and __is_primary_accl_template are true,
    // it should select _OtherTraits (CustomTraits).
    // For int*: __is_primary_std_template<int*> is true.
    // If __is_primary_accl_template<int*> is also true, select_traits picks CustomTraits.
    // If __is_primary_accl_template<int*> is false, select_traits picks iterator_traits<int*>.
    {
        using Selected = asc::std::__select_traits<int*, CustomTraits>;
        bool is_custom = std::is_same<Selected, CustomTraits>::value;
        bool is_iter_traits = std::is_same<Selected, asc::std::iterator_traits<int*>>::value;
        std::cout << "[host][is_primary_template] select_traits<int*, CustomTraits> is CustomTraits: " << is_custom
                  << std::endl;
        std::cout << "[host][is_primary_template] select_traits<int*, CustomTraits> is iterator_traits<int*>: "
                  << is_iter_traits << std::endl;
        // At least one must be true
        if (!is_custom && !is_iter_traits) {
            std::cout << "[host][is_primary_template] FAIL: select_traits selected neither CustomTraits nor "
                         "iterator_traits<int*>"
                      << std::endl;
            ++g_failures;
        }
    }
}

static void test_select_traits_useriter_primary()
{
    // __select_traits with UserIter: __is_primary_std_template<UserIter> may be true,
    // but __is_primary_accl_template<UserIter> is false, so it should select iterator_traits<UserIter>
    {
        using Selected = asc::std::__select_traits<UserIter, CustomTraits>;
        bool is_iter_traits = std::is_same<Selected, asc::std::iterator_traits<UserIter>>::value;
        bool is_custom = std::is_same<Selected, CustomTraits>::value;
        std::cout << "[host][is_primary_template] select_traits<UserIter, CustomTraits> is iterator_traits<UserIter>: "
                  << is_iter_traits << std::endl;
        std::cout << "[host][is_primary_template] select_traits<UserIter, CustomTraits> is CustomTraits: " << is_custom
                  << std::endl;
        // UserIter doesn't have __accl_primary_template, so __is_primary_accl_template is false,
        // meaning select_traits should NOT pick CustomTraits
        if (is_custom) {
            std::cout
                << "[host][is_primary_template] FAIL: select_traits<UserIter, CustomTraits> should not be CustomTraits"
                << std::endl;
            ++g_failures;
        }
    }
}

int main()
{
    test_primary_accl_template_int();
    test_user_iterator_without_accl();
    test_primary_std_template_int();
    test_user_iterator_standard_iterator();
    test_select_traits_both_primary();
    test_select_traits_useriter_primary();

    return g_failures == 0 ? 0 : 1;
}
