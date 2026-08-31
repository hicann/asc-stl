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

#include <asc/std/__type_traits/is_literal_type.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_literal_type] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_literal_type] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

struct LiteralStruct {
    int x;
    float y;
};

struct NonTrivialDtor {
    ~NonTrivialDtor()
    {}
};

int main()
{
    // Scalar types are literal types
    expect_true("is_literal_type<int>::value", asc::std::is_literal_type<int>::value);
    expect_true("is_literal_type<float>::value", asc::std::is_literal_type<float>::value);
    expect_true("is_literal_type<double>::value", asc::std::is_literal_type<double>::value);
    expect_true("is_literal_type<char>::value", asc::std::is_literal_type<char>::value);
    expect_true("is_literal_type<bool>::value", asc::std::is_literal_type<bool>::value);

    // Pointer types
    expect_true("is_literal_type<int*>::value", asc::std::is_literal_type<int*>::value);

    // Reference types
    expect_true("is_literal_type<int&>::value", asc::std::is_literal_type<int&>::value);

    // Array of literal type
    expect_true("is_literal_type<int[5]>::value", asc::std::is_literal_type<int[5]>::value);

    // Literal struct (trivial destructor, all members literal)
    expect_true("is_literal_type<LiteralStruct>::value", asc::std::is_literal_type<LiteralStruct>::value);

    // Struct with non-trivial destructor is NOT a literal type
    expect_false("is_literal_type<NonTrivialDtor>::value", asc::std::is_literal_type<NonTrivialDtor>::value);

    // _v variable
    expect_true("is_literal_type_v<int>", asc::std::is_literal_type_v<int>);
    expect_false("is_literal_type_v<NonTrivialDtor>", asc::std::is_literal_type_v<NonTrivialDtor>);

    // Inheritance from bool_constant - can be used as bool
    expect_true("is_literal_type<int>() == true", asc::std::is_literal_type<int>() == true);
    expect_true("is_literal_type<NonTrivialDtor>() == false", asc::std::is_literal_type<NonTrivialDtor>() == false);

    // const-qualified literal type
    expect_true("is_literal_type<const int>::value", asc::std::is_literal_type<const int>::value);

    return g_failures == 0 ? 0 : 1;
}
