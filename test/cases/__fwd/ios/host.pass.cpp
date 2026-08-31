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

#include <asc/std/__fwd/ios.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][ios] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void test_char_based_type_aliases()
{
    // Verify char-based type aliases
    expect_true("ios == basic_ios<char>", std::is_same_v<asc::std::ios, asc::std::basic_ios<char>>);
    expect_true(
        "streambuf == basic_streambuf<char>", std::is_same_v<asc::std::streambuf, asc::std::basic_streambuf<char>>);
    expect_true("istream == basic_istream<char>", std::is_same_v<asc::std::istream, asc::std::basic_istream<char>>);
    expect_true("ostream == basic_ostream<char>", std::is_same_v<asc::std::ostream, asc::std::basic_ostream<char>>);
    expect_true("iostream == basic_iostream<char>", std::is_same_v<asc::std::iostream, asc::std::basic_iostream<char>>);

    expect_true(
        "stringbuf == basic_stringbuf<char>", std::is_same_v<asc::std::stringbuf, asc::std::basic_stringbuf<char>>);
    expect_true("istringstream == basic_istringstream<char>",
        std::is_same_v<asc::std::istringstream, asc::std::basic_istringstream<char>>);
    expect_true("ostringstream == basic_ostringstream<char>",
        std::is_same_v<asc::std::ostringstream, asc::std::basic_ostringstream<char>>);
    expect_true("stringstream == basic_stringstream<char>",
        std::is_same_v<asc::std::stringstream, asc::std::basic_stringstream<char>>);
}

static void test_filebuf_basic_filebuf()
{
    expect_true("filebuf == basic_filebuf<char>", std::is_same_v<asc::std::filebuf, asc::std::basic_filebuf<char>>);
    expect_true("ifstream == basic_ifstream<char>", std::is_same_v<asc::std::ifstream, asc::std::basic_ifstream<char>>);
    expect_true("ofstream == basic_ofstream<char>", std::is_same_v<asc::std::ofstream, asc::std::basic_ofstream<char>>);
    expect_true("fstream == basic_fstream<char>", std::is_same_v<asc::std::fstream, asc::std::basic_fstream<char>>);
}

static void test_wchar_based_type_aliases()
{
    // Verify wchar_t-based type aliases
    expect_true("wios == basic_ios<wchar_t>", std::is_same_v<asc::std::wios, asc::std::basic_ios<wchar_t>>);
    expect_true("wstreambuf == basic_streambuf<wchar_t>",
        std::is_same_v<asc::std::wstreambuf, asc::std::basic_streambuf<wchar_t>>);
    expect_true(
        "wistream == basic_istream<wchar_t>", std::is_same_v<asc::std::wistream, asc::std::basic_istream<wchar_t>>);
    expect_true(
        "wostream == basic_ostream<wchar_t>", std::is_same_v<asc::std::wostream, asc::std::basic_ostream<wchar_t>>);
    expect_true(
        "wiostream == basic_iostream<wchar_t>", std::is_same_v<asc::std::wiostream, asc::std::basic_iostream<wchar_t>>);

    expect_true("wstringbuf == basic_stringbuf<wchar_t>",
        std::is_same_v<asc::std::wstringbuf, asc::std::basic_stringbuf<wchar_t>>);
    expect_true("wistringstream == basic_istringstream<wchar_t>",
        std::is_same_v<asc::std::wistringstream, asc::std::basic_istringstream<wchar_t>>);
    expect_true("wostringstream == basic_ostringstream<wchar_t>",
        std::is_same_v<asc::std::wostringstream, asc::std::basic_ostringstream<wchar_t>>);
    expect_true("wstringstream == basic_stringstream<wchar_t>",
        std::is_same_v<asc::std::wstringstream, asc::std::basic_stringstream<wchar_t>>);

    expect_true(
        "wfilebuf == basic_filebuf<wchar_t>", std::is_same_v<asc::std::wfilebuf, asc::std::basic_filebuf<wchar_t>>);
    expect_true(
        "wifstream == basic_ifstream<wchar_t>", std::is_same_v<asc::std::wifstream, asc::std::basic_ifstream<wchar_t>>);
    expect_true(
        "wofstream == basic_ofstream<wchar_t>", std::is_same_v<asc::std::wofstream, asc::std::basic_ofstream<wchar_t>>);
    expect_true(
        "wfstream == basic_fstream<wchar_t>", std::is_same_v<asc::std::wfstream, asc::std::basic_fstream<wchar_t>>);
}

static void test_streamoff_type_long_long()
{
    // Verify streamoff type (long long on non-newlib platforms)
    expect_true("streamoff == long long", std::is_same_v<asc::std::streamoff, long long>);
}

static void test_ios_base_class_type()
{
    // Verify ios_base is a class type
    expect_true("ios_base is class", std::is_class_v<asc::std::ios_base>);
}

static void test_iterator_templates_declared()
{
    // Verify iterator templates are declared
    expect_true("istreambuf_iterator<char> is class", std::is_class_v<asc::std::istreambuf_iterator<char>>);
    expect_true("ostreambuf_iterator<char> is class", std::is_class_v<asc::std::ostreambuf_iterator<char>>);
}

int main()
{
    test_char_based_type_aliases();
    test_filebuf_basic_filebuf();
    test_wchar_based_type_aliases();
    test_streamoff_type_long_long();
    test_ios_base_class_type();
    test_iterator_templates_declared();

    return g_failures == 0 ? 0 : 1;
}
