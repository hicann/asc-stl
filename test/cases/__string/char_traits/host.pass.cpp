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

#include <asc/std/__string/char_traits.h>
#include <iostream>
#include <cstddef>

using ct = asc::std::char_traits<char>;

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][char_traits] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][char_traits] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void check_part1()
{
    // eq
    expect_true("eq('a','a')", ct::eq('a', 'a'));
    expect_true("!eq('a','b')", !ct::eq('a', 'b'));

    // lt (unsigned comparison for char)
    expect_true("lt('a','b')", ct::lt('a', 'b'));
    expect_true("!lt('b','a')", !ct::lt('b', 'a'));
    expect_true("lt(char(1),char(255))", ct::lt(static_cast<char>(1), static_cast<char>(255)));
    expect_true("!lt(char(255),char(1))", !ct::lt(static_cast<char>(255), static_cast<char>(1)));

    // assign(char_type&, const char_type&)
    {
        char c = 'x';
        ct::assign(c, 'z');
        expect_eq("assign(c,'z')", c, 'z');
    }

    // compare
    {
        expect_eq("compare(\"abc\",\"abc\",3)", ct::compare("abc", "abc", 3), 0);
        expect_true("compare(\"abc\",\"abd\",3) < 0", ct::compare("abc", "abd", 3) < 0);
        expect_true("compare(\"abd\",\"abc\",3) > 0", ct::compare("abd", "abc", 3) > 0);
        expect_eq("compare(\"ab\",\"abc\",2)", ct::compare("ab", "abc", 2), 0);
        expect_eq("compare(\"\",\"\",0)", ct::compare("", "", 0), 0);
    }

    // length
    expect_eq("length(\"hello\")", ct::length("hello"), static_cast<size_t>(5));
    expect_eq("length(\"\")", ct::length(""), static_cast<size_t>(0));
    expect_eq("length(\"a\")", ct::length("a"), static_cast<size_t>(1));

    // find
    {
        const char* s = "hello";
        expect_true("find(\"hello\",5,'l') != nullptr", ct::find(s, 5, 'l') != nullptr);
        expect_eq("find(\"hello\",5,'l')-s", static_cast<int>(ct::find(s, 5, 'l') - s), 2);
        expect_true("find(\"hello\",5,'z') == nullptr", ct::find(s, 5, 'z') == nullptr);
        expect_true("find(\"hello\",0,'h') == nullptr", ct::find(s, 0, 'h') == nullptr);
    }
}

static void check_part2()
{
    // move
    {
        char buf[10] = "abcdefghi";
        ct::move(buf + 2, buf, 3);
        expect_eq("move buf[2]", buf[2], 'a');
        expect_eq("move buf[3]", buf[3], 'b');
        expect_eq("move buf[4]", buf[4], 'c');
    }

    // copy
    {
        char src[10] = "abcdefghi";
        char dst[10] = {0};
        ct::copy(dst, src, 4);
        expect_eq("copy dst[0]", dst[0], 'a');
        expect_eq("copy dst[1]", dst[1], 'b');
        expect_eq("copy dst[2]", dst[2], 'c');
        expect_eq("copy dst[3]", dst[3], 'd');
    }

    // assign(char_type*, size_t, char_type)
    {
        char buf[5] = {0};
        ct::assign(buf, 3, 'x');
        expect_eq("assign(buf,3,'x')[0]", buf[0], 'x');
        expect_eq("assign(buf,3,'x')[1]", buf[1], 'x');
        expect_eq("assign(buf,3,'x')[2]", buf[2], 'x');
    }

    // to_char_type / to_int_type
    expect_eq("to_int_type('a')", ct::to_int_type('a'), 97);
    expect_eq("to_char_type(97)", ct::to_char_type(97), 'a');
}

static void check_part3()
{
    expect_eq("to_int_type(char(255))", ct::to_int_type(static_cast<char>(255)), 255);

    // eq_int_type
    expect_true("eq_int_type(97,97)", ct::eq_int_type(97, 97));
    expect_true("!eq_int_type(97,98)", !ct::eq_int_type(97, 98));
}

int main()
{
    check_part1();
    check_part2();
    check_part3();

    return g_failures == 0 ? 0 : 1;
}
