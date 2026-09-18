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

#include <asc/std/__type_traits/type_set.h>
#include <iostream>
#include <cstddef>

using namespace asc::std;  // NOLINT(build/namespaces)

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    std::cout << "[host][type_set] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (got ? "OK" : "FAIL") << std::endl;
    if (!got)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    std::cout << "[host][type_set] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (!got ? "OK" : "FAIL") << std::endl;
    if (got)
        ++g_failures;
}

static void expect_eq_size(const char* expr, size_t got, size_t expected)
{
    bool ok = (got == expected);
    std::cout << "[host][type_set] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_type_set_empty_set()
{
    // === __type_set: empty set ===
    {
        using empty_set = __type_set<>;
        expect_eq_size("__type_set<>::__size()", empty_set::__size(), 0);
    }
}

static void test_type_set_distinct_types()
{
    // === __type_set: distinct types ===
    {
        using s = __type_set<int, char, double>;
        expect_eq_size("__type_set<int,char,double>::__size()", s::__size(), 3);
    }
}

static void test_type_set_contains_single()
{
    // === __type_set_contains_v: single type in set ===
    {
        using s = __type_set<int, char, double>;
        expect_true("__type_set_contains_v<s, int>", __type_set_contains_v<s, int>);
        expect_true("__type_set_contains_v<s, char>", __type_set_contains_v<s, char>);
        expect_true("__type_set_contains_v<s, double>", __type_set_contains_v<s, double>);
        expect_false("__type_set_contains_v<s, float>", __type_set_contains_v<s, float>);
    }
}

static void test_type_set_contains_multiple()
{
    // === __type_set_contains_v: multiple types ===
    {
        using s = __type_set<int, char, double>;
        expect_true("__type_set_contains_v<s, int, char>", __type_set_contains_v<s, int, char>);
        expect_true("__type_set_contains_v<s, int, char, double>", __type_set_contains_v<s, int, char, double>);
        expect_false("__type_set_contains_v<s, int, float>", __type_set_contains_v<s, int, float>);
    }
}

static void test_type_set_contains_empty()
{
    // === __type_set_contains_v: empty pack (vacuously true) ===
    {
        using s = __type_set<int>;
        expect_true("__type_set_contains_v<s> (empty pack)", __type_set_contains_v<s>);
    }
}

static void test_make_type_set_deduplication()
{
    // === __make_type_set: deduplication ===
    {
        using s = __make_type_set<int, char, int, double, char>;
        expect_eq_size("__make_type_set<int,char,int,double,char>::__size()", s::__size(), 3);
        expect_true("__type_set_contains_v<s, int>", __type_set_contains_v<s, int>);
        expect_true("__type_set_contains_v<s, char>", __type_set_contains_v<s, char>);
        expect_true("__type_set_contains_v<s, double>", __type_set_contains_v<s, double>);
    }
}

static void test_make_type_set_empty()
{
    // === __make_type_set: empty ===
    {
        using s = __make_type_set<>;
        expect_eq_size("__make_type_set<>::__size()", s::__size(), 0);
    }
}

static void test_make_type_set_single()
{
    // === __make_type_set: single type ===
    {
        using s = __make_type_set<int>;
        expect_eq_size("__make_type_set<int>::__size()", s::__size(), 1);
    }
}

static void test_make_type_set_same()
{
    // === __make_type_set: all same types ===
    {
        using s = __make_type_set<int, int, int>;
        expect_eq_size("__make_type_set<int,int,int>::__size()", s::__size(), 1);
    }
}

static void test_type_set_equal_sets()
{
    // === __type_set_eq_v: equal sets (order-independent) ===
    {
        using s = __make_type_set<int, char, double>;
        expect_true("__type_set_eq_v<s, int, char, double>", __type_set_eq_v<s, int, char, double>);
        expect_true("__type_set_eq_v<s, char, int, double>", __type_set_eq_v<s, char, int, double>);
        expect_true("__type_set_eq_v<s, double, char, int>", __type_set_eq_v<s, double, char, int>);
    }
}

static void test_type_set_equal_extra()
{
    // === __type_set_eq_v: not equal (extra type) ===
    {
        using s = __make_type_set<int, char>;
        expect_false("__type_set_eq_v<s, int, char, double> (extra)", __type_set_eq_v<s, int, char, double>);
    }
}

static void test_type_set_equal_missing()
{
    // === __type_set_eq_v: not equal (missing type) ===
    {
        using s = __make_type_set<int, char, double>;
        expect_false("__type_set_eq_v<s, int, char> (missing)", __type_set_eq_v<s, int, char>);
    }
}

static void test_type_set_empty_set_2()
{
    // === __type_set_eq_v: empty set vs empty pack ===
    {
        using s = __make_type_set<>;
        expect_true("__type_set_eq_v<empty_set> (empty pack)", __type_set_eq_v<s>);
    }
}

static void test_type_set_empty_set_3()
{
    // === __type_set_eq_v: empty set vs non-empty pack ===
    {
        using s = __make_type_set<>;
        expect_false("__type_set_eq_v<empty_set, int> (size mismatch)", __type_set_eq_v<s, int>);
    }
}

static void test_type_set_insert_insert()
{
    // === __type_set_insert: insert new type ===
    {
        using s = __type_set<int, char>;
        using s2 = __type_set_insert<s, double>;
        expect_eq_size("__type_set_insert<s, double>::__size()", s2::__size(), 3);
        expect_true("__type_set_contains_v<s2, double>", __type_set_contains_v<s2, double>);
    }
}

static void test_type_set_insert_insert_2()
{
    // === __type_set_insert: insert existing type (no change) ===
    {
        using s = __type_set<int, char>;
        using s2 = __type_set_insert<s, int>;
        expect_eq_size("__type_set_insert<s, int>::__size() (no dup)", s2::__size(), 2);
    }
}

static void test_type_set_insert_insert_3()
{
    // === __type_set_insert: insert multiple types with dedup ===
    {
        using s = __type_set<int>;
        using s2 = __type_set_insert<s, char, int, double>;
        expect_eq_size("__type_set_insert<s, char, int, double>::__size()", s2::__size(), 3);
    }
}

static void test_type_set_insert_insert_4()
{
    // === __type_set_insert: insert empty pack (no change) ===
    {
        using s = __type_set<int, char>;
        using s2 = __type_set_insert<s>;
        expect_eq_size("__type_set_insert<s> (empty pack)", s2::__size(), 2);
    }
}

static void test_included_type_pack()
{
    // === __is_included_in_v: type in pack ===
    {
        expect_true("__is_included_in_v<int, int, char, double>", __is_included_in_v<int, int, char, double>);
        expect_true("__is_included_in_v<char, int, char, double>", __is_included_in_v<char, int, char, double>);
        expect_false("__is_included_in_v<float, int, char, double>", __is_included_in_v<float, int, char, double>);
    }
}

static void test_included_empty_pack_false()
{
    // === __is_included_in_v: empty pack (false) ===
    {
        expect_false("__is_included_in_v<int> (empty pack)", __is_included_in_v<int>);
    }
}

static void test_set_tupl_maybe_insert()
{
    // === __set::__tupl::__maybe_insert: new type ===
    {
        using t = __set::__tupl<int, char>;
        using t2 = t::__maybe_insert<double>;
        expect_eq_size("__maybe_insert<double> on {int,char}", t2::__size(), 3);
    }
}

static void test_set_tupl_maybe_insert_2()
{
    // === __set::__tupl::__maybe_insert: existing type (no change) ===
    {
        using t = __set::__tupl<int, char>;
        using t2 = t::__maybe_insert<int>;
        expect_eq_size("__maybe_insert<int> on {int,char} (no dup)", t2::__size(), 2);
    }
}

static void test_set_tupl_maybe_insert_3()
{
    // === __set::__tupl<>::__maybe_insert: insert into empty ===
    {
        using t = __set::__tupl<>;
        using t2 = t::__maybe_insert<int>;
        expect_eq_size("__maybe_insert<int> on empty set", t2::__size(), 1);
    }
}

static void test_set_tupl_size()
{
    // === __set::__tupl<>::__size() ===
    {
        expect_eq_size("__set::__tupl<>::__size()", __set::__tupl<>::__size(), 0);
    }
}

static void test_set_tupl_int_size()
{
    // === __set::__tupl<int>::__size() ===
    {
        expect_eq_size("__set::__tupl<int>::__size()", __set::__tupl<int>::__size(), 1);
    }
}

int main()
{
    test_type_set_empty_set();
    test_type_set_distinct_types();
    test_type_set_contains_single();
    test_type_set_contains_multiple();
    test_type_set_contains_empty();
    test_make_type_set_deduplication();
    test_make_type_set_empty();
    test_make_type_set_single();
    test_make_type_set_same();
    test_type_set_equal_sets();
    test_type_set_equal_extra();
    test_type_set_equal_missing();
    test_type_set_empty_set_2();
    test_type_set_empty_set_3();
    test_type_set_insert_insert();
    test_type_set_insert_insert_2();
    test_type_set_insert_insert_3();
    test_type_set_insert_insert_4();
    test_included_type_pack();
    test_included_empty_pack_false();
    test_set_tupl_maybe_insert();
    test_set_tupl_maybe_insert_2();
    test_set_tupl_maybe_insert_3();
    test_set_tupl_size();
    test_set_tupl_int_size();

    return g_failures == 0 ? 0 : 1;
}
