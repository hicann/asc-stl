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

#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_trivially_move_constructible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_trivially_move_constructible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

struct TrivialStruct {
    int a;
    float b;
};

struct NonTrivialStruct {
    NonTrivialStruct(NonTrivialStruct&&) : a(0), b(0.0f)
    {}
    int a;
    float b;
};

struct WithNonTrivialMember {
    NonTrivialStruct m;
};

int main()
{
    expect_true("is_trivially_move_constructible_v<int>", asc::std::is_trivially_move_constructible_v<int>);
    expect_true("is_trivially_move_constructible_v<float>", asc::std::is_trivially_move_constructible_v<float>);
    expect_true(
        "is_trivially_move_constructible_v<TrivialStruct>", asc::std::is_trivially_move_constructible_v<TrivialStruct>);
    expect_true("is_trivially_move_constructible<int>::value", asc::std::is_trivially_move_constructible<int>::value);

    expect_false("is_trivially_move_constructible_v<NonTrivialStruct>",
        asc::std::is_trivially_move_constructible_v<NonTrivialStruct>);
    expect_false("is_trivially_move_constructible_v<WithNonTrivialMember>",
        asc::std::is_trivially_move_constructible_v<WithNonTrivialMember>);
    expect_false("is_trivially_move_constructible<NonTrivialStruct>::value",
        asc::std::is_trivially_move_constructible<NonTrivialStruct>::value);

    return g_failures == 0 ? 0 : 1;
}
