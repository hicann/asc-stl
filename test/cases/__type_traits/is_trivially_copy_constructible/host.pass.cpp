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

#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_trivially_copy_constructible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_trivially_copy_constructible] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// Trivially copyable struct
struct TrivialStruct {
    int a;
    float b;
};

// Struct with user-defined copy constructor (non-trivial)
struct NonTrivialCopy {
    int a;
    NonTrivialCopy(const NonTrivialCopy& other) : a(other.a)
    {}
};

// Struct with virtual function (non-trivial copy)
struct VirtualStruct {
    int a;
    virtual void foo()
    {}
};

// Enum type - trivially copy constructible
enum MyEnum { A, B, C };

int main()
{
    // Primitive types - trivially copy constructible
    expect_true("is_trivially_copy_constructible<int>::value", asc::std::is_trivially_copy_constructible<int>::value);
    expect_true(
        "is_trivially_copy_constructible<float>::value", asc::std::is_trivially_copy_constructible<float>::value);
    expect_true(
        "is_trivially_copy_constructible<double>::value", asc::std::is_trivially_copy_constructible<double>::value);
    expect_true("is_trivially_copy_constructible<char>::value", asc::std::is_trivially_copy_constructible<char>::value);
    expect_true("is_trivially_copy_constructible<long>::value", asc::std::is_trivially_copy_constructible<long>::value);
    expect_true("is_trivially_copy_constructible<bool>::value", asc::std::is_trivially_copy_constructible<bool>::value);

    // Pointer types - trivially copy constructible
    expect_true("is_trivially_copy_constructible<int*>::value", asc::std::is_trivially_copy_constructible<int*>::value);

    // Enum type - trivially copy constructible
    expect_true(
        "is_trivially_copy_constructible<MyEnum>::value", asc::std::is_trivially_copy_constructible<MyEnum>::value);

    // _v variable template
    expect_true("is_trivially_copy_constructible_v<int>", asc::std::is_trivially_copy_constructible_v<int>);
    expect_true("is_trivially_copy_constructible_v<float>", asc::std::is_trivially_copy_constructible_v<float>);

    // Trivially copyable struct
    expect_true("is_trivially_copy_constructible<TrivialStruct>::value",
        asc::std::is_trivially_copy_constructible<TrivialStruct>::value);
    expect_true(
        "is_trivially_copy_constructible_v<TrivialStruct>", asc::std::is_trivially_copy_constructible_v<TrivialStruct>);

    // Reference types - trivially copy constructible
    expect_true("is_trivially_copy_constructible<int&>::value", asc::std::is_trivially_copy_constructible<int&>::value);

    // Non-trivially copy constructible: user-defined copy constructor
    expect_false("is_trivially_copy_constructible<NonTrivialCopy>::value",
        asc::std::is_trivially_copy_constructible<NonTrivialCopy>::value);
    expect_false("is_trivially_copy_constructible_v<NonTrivialCopy>",
        asc::std::is_trivially_copy_constructible_v<NonTrivialCopy>);

    // Non-trivially copy constructible: virtual function
    expect_false("is_trivially_copy_constructible<VirtualStruct>::value",
        asc::std::is_trivially_copy_constructible<VirtualStruct>::value);

    // void - not trivially copy constructible
    expect_false(
        "is_trivially_copy_constructible<void>::value", asc::std::is_trivially_copy_constructible<void>::value);
    expect_false("is_trivially_copy_constructible_v<void>", asc::std::is_trivially_copy_constructible_v<void>);

    return g_failures == 0 ? 0 : 1;
}
