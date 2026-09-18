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

#include <asc/std/__type_traits/is_integral.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    bool ok = got;
    std::cout << "[host][is_integral] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    bool ok = !got;
    std::cout << "[host][is_integral] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

#define CHECK_TRUE(T)                                                               \
    do {                                                                            \
        expect_true("is_integral<" #T ">::value", asc::std::is_integral<T>::value); \
        expect_true("is_integral_v<" #T ">", asc::std::is_integral_v<T>);           \
    } while (0)

#define CHECK_FALSE(T)                                                               \
    do {                                                                             \
        expect_false("is_integral<" #T ">::value", asc::std::is_integral<T>::value); \
        expect_false("is_integral_v<" #T ">", asc::std::is_integral_v<T>);           \
    } while (0)

struct Dummy {};

int main()
{
    CHECK_TRUE(bool);
    CHECK_TRUE(char);
    CHECK_TRUE(signed char);
    CHECK_TRUE(unsigned char);
    CHECK_TRUE(wchar_t);
    CHECK_TRUE(char16_t);
    CHECK_TRUE(char32_t);
    CHECK_TRUE(short);
    CHECK_TRUE(unsigned short);
    CHECK_TRUE(int);
    CHECK_TRUE(unsigned int);
    CHECK_TRUE(long);
    CHECK_TRUE(unsigned long);
    CHECK_TRUE(long long);
    CHECK_TRUE(unsigned long long);

    CHECK_TRUE(const int);
    CHECK_TRUE(volatile int);
    CHECK_TRUE(const volatile int);

    CHECK_FALSE(float);
    CHECK_FALSE(double);
    CHECK_FALSE(long double);
    CHECK_FALSE(void);
    CHECK_FALSE(int*);
    CHECK_FALSE(const int*);
    CHECK_FALSE(int&);
    CHECK_FALSE(int&&);
    CHECK_FALSE(Dummy);

    return g_failures == 0 ? 0 : 1;
}
