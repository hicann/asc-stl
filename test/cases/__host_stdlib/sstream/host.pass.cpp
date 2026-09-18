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

#include <asc/std/__host_stdlib/sstream>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_eq(const char* expr, const std::string& got, const std::string& expected)
{
    bool ok = (got == expected);
    std::cout << "[host][sstream] " << expr << " = \"" << got << "\" (expected \"" << expected << "\") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][sstream] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void test_basic_stringstream_write_read()
{
    // Test basic stringstream: write and read back
    {
        std::stringstream ss;
        ss << "hello " << 42;
        expect_eq("ss.str()", ss.str(), std::string("hello 42"));
    }
}

static void test_istringstream_parse_integers_string()
{
    // Test istringstream: parse integers from string
    {
        std::istringstream iss("100 200");
        int a = 0, b = 0;
        iss >> a >> b;
        expect_eq("istringstream a", a, 100);
        expect_eq("istringstream b", b, 200);
    }
}

static void test_ostringstream_format_string()
{
    // Test ostringstream: format to string
    {
        std::ostringstream oss;
        oss << 3.14;
        expect_eq("ostringstream str", oss.str(), std::string("3.14"));
    }
}

static void test_str_setter_getter()
{
    // Test str() setter and getter
    {
        std::stringstream ss;
        ss.str("abc");
        expect_eq("str() getter", ss.str(), std::string("abc"));
    }
}

static void test_clear_reuse()
{
    // Test clear and reuse
    {
        std::stringstream ss;
        ss << "first";
        ss.str("");
        ss << "second";
        expect_eq("clear and reuse", ss.str(), std::string("second"));
    }
}

static void test_integer_round_trip_via()
{
    // Test integer round-trip via stringstream
    {
        std::stringstream ss;
        int val = 9999;
        ss << val;
        int back = 0;
        ss >> back;
        expect_eq("int round-trip", back, 9999);
    }
}

static void test_istringstream_mixed_types()
{
    // Test istringstream with mixed types
    {
        std::istringstream iss("42 hello");
        int n = 0;
        std::string s;
        iss >> n >> s;
        expect_eq("mixed int", n, 42);
        expect_eq("mixed string", s, std::string("hello"));
    }
}

int main()
{
    test_basic_stringstream_write_read();
    test_istringstream_parse_integers_string();
    test_ostringstream_format_string();
    test_str_setter_getter();
    test_clear_reuse();
    test_integer_round_trip_via();
    test_istringstream_mixed_types();

    return g_failures == 0 ? 0 : 1;
}
