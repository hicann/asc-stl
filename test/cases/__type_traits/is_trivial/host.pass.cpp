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

#include <asc/std/__type_traits/is_trivial.h>
#include <iostream>

static int g_failures = 0;

template <typename T>
static void expect_true(const char* expr, T cond)
{
    bool ok = (cond == true);
    std::cout << "[host][is_trivial] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

template <typename T>
static void expect_false(const char* expr, T cond)
{
    bool ok = (cond == false);
    std::cout << "[host][is_trivial] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Trivial types
struct TrivialStruct {};
struct TrivialWithMembers {
    int a;
    double b;
};

// Non-trivial types
struct NonTrivialCtor {
    NonTrivialCtor()
    {}
};
struct NonTrivialDtor {
    ~NonTrivialDtor()
    {}
};
struct NonTrivialCopy {
    NonTrivialCopy(const NonTrivialCopy&)
    {}
};
struct VirtualClass {
    virtual void foo()
    {}
};

int main()
{
    // Scalar types are trivial
    expect_true("is_trivial<int>", asc::std::is_trivial<int>::value);
    expect_true("is_trivial<float>", asc::std::is_trivial<float>::value);
    expect_true("is_trivial<double>", asc::std::is_trivial<double>::value);
    expect_true("is_trivial<char>", asc::std::is_trivial<char>::value);
    expect_true("is_trivial<bool>", asc::std::is_trivial<bool>::value);
    expect_true("is_trivial<int*>", asc::std::is_trivial<int*>::value);
    expect_true("is_trivial<unsigned long>", asc::std::is_trivial<unsigned long>::value);

    // _v convenience variable
    expect_true("is_trivial_v<int>", asc::std::is_trivial_v<int>);
    expect_true("is_trivial_v<float>", asc::std::is_trivial_v<float>);
    expect_true("is_trivial_v<double>", asc::std::is_trivial_v<double>);

    // Trivial structs (no user-defined special members)
    expect_true("is_trivial<TrivialStruct>", asc::std::is_trivial<TrivialStruct>::value);
    expect_true("is_trivial<TrivialWithMembers>", asc::std::is_trivial<TrivialWithMembers>::value);
    expect_true("is_trivial_v<TrivialStruct>", asc::std::is_trivial_v<TrivialStruct>);
    expect_true("is_trivial_v<TrivialWithMembers>", asc::std::is_trivial_v<TrivialWithMembers>);

    // Arrays of trivial types are trivial
    expect_true("is_trivial<int[10]>", asc::std::is_trivial<int[10]>::value);
    expect_true("is_trivial_v<TrivialStruct[5]>", asc::std::is_trivial_v<TrivialStruct[5]>);

    // Non-trivial: user-defined default constructor
    expect_false("is_trivial<NonTrivialCtor>", asc::std::is_trivial<NonTrivialCtor>::value);
    expect_false("is_trivial_v<NonTrivialCtor>", asc::std::is_trivial_v<NonTrivialCtor>);

    // Non-trivial: user-defined destructor
    expect_false("is_trivial<NonTrivialDtor>", asc::std::is_trivial<NonTrivialDtor>::value);
    expect_false("is_trivial_v<NonTrivialDtor>", asc::std::is_trivial_v<NonTrivialDtor>);

    // Non-trivial: user-defined copy constructor
    expect_false("is_trivial<NonTrivialCopy>", asc::std::is_trivial<NonTrivialCopy>::value);
    expect_false("is_trivial_v<NonTrivialCopy>", asc::std::is_trivial_v<NonTrivialCopy>);

    // Non-trivial: virtual function
    expect_false("is_trivial<VirtualClass>", asc::std::is_trivial<VirtualClass>::value);
    expect_false("is_trivial_v<VirtualClass>", asc::std::is_trivial_v<VirtualClass>);

    return g_failures == 0 ? 0 : 1;
}
