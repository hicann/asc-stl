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

#include <asc/std/__string/string_view.h>
#include <iostream>
#include <cstddef>

using asc::std::__string_view;

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][string_view] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][string_view] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][string_view] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

static void check_part1()
{
    // Test 1: Construction from pointer + length
    {
        const char* s = "hello";
        __string_view sv(s, 5);
        expect_eq("sv.size()", sv.size(), size_t(5));
        expect_true("sv.data() == s", sv.data() == s);
    }

    // Test 2: Construction from C-string (explicit constructor)
    {
        const char* s = "world";
        __string_view sv(s);
        expect_eq("sv.size() from c-string", sv.size(), size_t(5));
        expect_true("sv.data() == s", sv.data() == s);
    }

    // Test 3: operator[]
    {
        const char* s = "abcde";
        __string_view sv(s, 5);
        expect_eq("sv[0]", static_cast<int>(sv[0]), static_cast<int>('a'));
        expect_eq("sv[4]", static_cast<int>(sv[4]), static_cast<int>('e'));
    }

    // Test 4: begin/end iterators
    {
        const char* s = "test";
        __string_view sv(s, 4);
        expect_true("sv.begin() == s", sv.begin() == s);
        expect_true("sv.end() == s + 4", sv.end() == s + 4);
    }
}

static void check_part2()
{
    // Test 5: substr (note: takes start and stop, not start and length)
    {
        const char* s = "hello world";
        __string_view sv(s, 11);
        auto sub = sv.substr(0, 5);
        expect_eq("substr(0,5).size()", sub.size(), size_t(5));
        expect_eq("substr(0,5)[0]", int(sub[0]), static_cast<int>('h'));  // NOLINT(readability/casting)
        expect_eq("substr(0,5)[4]", int(sub[4]), static_cast<int>('o'));  // NOLINT(readability/casting)

        auto sub2 = sv.substr(6, 11);
        expect_eq("substr(6,11).size()", sub2.size(), size_t(5));
        expect_eq("substr(6,11)[0]", int(sub2[0]), static_cast<int>('w'));  // NOLINT(readability/casting)
        expect_eq("substr(6,11)[4]", int(sub2[4]), static_cast<int>('d'));  // NOLINT(readability/casting)

        auto sub3 = sv.substr(0, 0);
        expect_eq("substr(0,0).size()", sub3.size(), size_t(0));

        auto sub4 = sv.substr(0, 11);
        expect_eq("substr(0,11).size()", sub4.size(), size_t(11));
    }

    // Test 6: find
    {
        const char* s = "hello world";
        __string_view sv(s, 11);
        expect_eq("find(\"hello\")", sv.find("hello"), ptrdiff_t(0));
        expect_eq("find(\"world\")", sv.find("world"), ptrdiff_t(6));
        expect_eq("find(\"xyz\")", sv.find("xyz"), ptrdiff_t(-1));
        expect_eq("find(\"o\")", sv.find("o"), ptrdiff_t(4));
        expect_eq("find(\"l\")", sv.find("l"), ptrdiff_t(2));
    }
}

static void check_part3()
{
    // Test 7: find_end
    {
        const char* s = "hello world";
        __string_view sv(s, 11);
        expect_eq("find_end(\"o\")", sv.find_end("o"), ptrdiff_t(7));
        expect_eq("find_end(\"l\")", sv.find_end("l"), ptrdiff_t(9));
        expect_eq("find_end(\"xyz\")", sv.find_end("xyz"), ptrdiff_t(-1));
        expect_eq("find_end(\"world\")", sv.find_end("world"), ptrdiff_t(6));
        expect_eq("find_end(\"ll\")", sv.find_end("ll"), ptrdiff_t(2));
    }

    // Test 8: compare
    {
        const char* s1 = "abc";
        const char* s2 = "abd";
        const char* s3 = "abc";
        const char* s4 = "ab";
        __string_view sv1(s1, 3);
        __string_view sv2(s2, 3);
        __string_view sv3(s3, 3);
        __string_view sv4(s4, 2);

        expect_eq("compare(abc, abd)", sv1.compare(sv2), -1);
        expect_eq("compare(abc, abc)", sv1.compare(sv3), 0);
        expect_eq("compare(abd, abc)", sv2.compare(sv1), 1);
        expect_eq("compare(abc, ab)", sv1.compare(sv4), 1);
        expect_eq("compare(ab, abc)", sv4.compare(sv1), -1);
    }

    // Test 9: Comparison operators
    {
        const char* s1 = "abc";
        const char* s2 = "abd";
        const char* s3 = "abc";
        __string_view sv1(s1, 3);
        __string_view sv2(s2, 3);
        __string_view sv3(s3, 3);

        expect_true("sv1 == sv3", sv1 == sv3);
        expect_false("sv1 == sv2", sv1 == sv2);
        expect_true("sv1 != sv2", sv1 != sv2);
        expect_false("sv1 != sv3", sv1 != sv3);
        expect_true("sv1 < sv2", sv1 < sv2);
        expect_false("sv2 < sv1", sv2 < sv1);
        expect_true("sv1 <= sv3", sv1 <= sv3);
        expect_true("sv1 <= sv2", sv1 <= sv2);
        expect_true("sv2 > sv1", sv2 > sv1);
        expect_false("sv1 > sv2", sv1 > sv2);
        expect_true("sv2 >= sv1", sv2 >= sv1);
        expect_true("sv1 >= sv3", sv1 >= sv3);
    }
}

static void check_part4()
{
    // Test 10: Empty string view
    {
        const char* s = "";
        __string_view sv(s, 0);
        expect_eq("empty.size()", sv.size(), size_t(0));
    }

    // Test 11: find with needle longer than haystack
    {
        const char* s = "hi";
        __string_view sv(s, 2);
        expect_eq("find(\"hello\") in \"hi\"", sv.find("hello"), ptrdiff_t(-1));
    }

    // Test 12: Same underlying pointer comparison
    {
        const char* s = "abc";
        __string_view sv1(s, 3);
        __string_view sv2(s, 3);
        expect_eq("same-ptr compare", sv1.compare(sv2), 0);
        expect_true("same-ptr ==", sv1 == sv2);
    }

    // Test 13: Construction from C-string with explicit keyword
    {
        const char* s = "test123";
        __string_view sv(s);
        expect_eq("explicit c-string size", sv.size(), size_t(7));
    }
}

int main()
{
    check_part1();
    check_part2();
    check_part3();
    check_part4();

    return g_failures == 0 ? 0 : 1;
}
