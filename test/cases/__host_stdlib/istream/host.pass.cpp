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

#include <asc/std/__host_stdlib/istream>
#include <iostream>
#include <sstream>
#include <string>

int g_failures = 0;

template <typename T>
void expect_eq(const char* expr, const T& got, const T& expected)
{
    if (got != expected) {
        std::cout << "[host][istream] " << expr << " = " << got << " (expected " << expected << ") FAIL" << std::endl;
        g_failures++;
    } else {
        std::cout << "[host][istream] " << expr << " = " << got << " (expected " << expected << ") OK" << std::endl;
    }
}

int main()
{
    // Verify that std::istream is available and functional via std::istringstream
    std::istringstream iss("hello 42");
    std::string s;
    int i = 0;
    iss >> s >> i;

    expect_eq("s == \"hello\"", s, std::string("hello"));
    expect_eq("i == 42", i, 42);

    return g_failures == 0 ? 0 : 1;
}
