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

#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_trivially_move_assignable] " << expr << " = " << (cond ? "true" : "false")
              << " (expected true) " << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_trivially_move_assignable] " << expr << " = " << (cond ? "true" : "false")
              << " (expected false) " << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Trivially move assignable types
struct TrivialStruct {
    int a;
    float b;
};
struct TrivialDerived : TrivialStruct {
    double c;
};

// Non-trivially move assignable types
struct NonTrivialMove {
    int a;
    NonTrivialMove& operator=(NonTrivialMove&& other) noexcept
    {
        a = other.a;
        return *this;
    }
};
struct NonTrivialCopy {
    int a;
    NonTrivialCopy& operator=(const NonTrivialCopy& other)
    {
        a = other.a;
        return *this;
    }
};

// User-declared destructor suppresses implicit move assignment, but the compiler
// falls back to the (trivial) copy assignment for T&&, so this type IS trivially
// move assignable.
struct WithUserDtor {
    int a;
    ~WithUserDtor()
    {}
};

// A type with a non-trivially-move-assignable member — genuinely not trivially
// move assignable.
struct WithNonTrivialMember {
    NonTrivialMove member;
};

int main()
{
    // Fundamental types — trivially move assignable
    expect_true("is_trivially_move_assignable<int>::value", asc::std::is_trivially_move_assignable<int>::value);
    expect_true("is_trivially_move_assignable<float>::value", asc::std::is_trivially_move_assignable<float>::value);
    expect_true("is_trivially_move_assignable<double>::value", asc::std::is_trivially_move_assignable<double>::value);
    expect_true("is_trivially_move_assignable<char>::value", asc::std::is_trivially_move_assignable<char>::value);
    expect_true("is_trivially_move_assignable<bool>::value", asc::std::is_trivially_move_assignable<bool>::value);
    expect_true(
        "is_trivially_move_assignable<long long>::value", asc::std::is_trivially_move_assignable<long long>::value);

    // Pointer types
    expect_true("is_trivially_move_assignable<int*>::value", asc::std::is_trivially_move_assignable<int*>::value);

    // _v variable
    expect_true("is_trivially_move_assignable_v<int>", asc::std::is_trivially_move_assignable_v<int>);
    expect_true("is_trivially_move_assignable_v<float>", asc::std::is_trivially_move_assignable_v<float>);

    // Trivial struct / derived
    expect_true("is_trivially_move_assignable<TrivialStruct>::value",
        asc::std::is_trivially_move_assignable<TrivialStruct>::value);
    expect_true("is_trivially_move_assignable<TrivialDerived>::value",
        asc::std::is_trivially_move_assignable<TrivialDerived>::value);
    expect_true(
        "is_trivially_move_assignable_v<TrivialStruct>", asc::std::is_trivially_move_assignable_v<TrivialStruct>);

    // Non-trivially move assignable types
    expect_false("is_trivially_move_assignable<NonTrivialMove>::value",
        asc::std::is_trivially_move_assignable<NonTrivialMove>::value);
    expect_false("is_trivially_move_assignable<NonTrivialCopy>::value",
        asc::std::is_trivially_move_assignable<NonTrivialCopy>::value);
    expect_false("is_trivially_move_assignable<WithNonTrivialMember>::value",
        asc::std::is_trivially_move_assignable<WithNonTrivialMember>::value);
    expect_false(
        "is_trivially_move_assignable_v<NonTrivialMove>", asc::std::is_trivially_move_assignable_v<NonTrivialMove>);

    // WithUserDtor: user-declared dtor suppresses implicit move ops, but
    // trivial copy assignment handles T&&, so it IS trivially move assignable.
    expect_true("is_trivially_move_assignable<WithUserDtor>::value",
        asc::std::is_trivially_move_assignable<WithUserDtor>::value);

    // Reference types — references are trivially assignable
    expect_true("is_trivially_move_assignable<int&>::value", asc::std::is_trivially_move_assignable<int&>::value);
    expect_true("is_trivially_move_assignable<int&&>::value", asc::std::is_trivially_move_assignable<int&&>::value);

    // Array types — not trivially move assignable (arrays are not assignable)
    expect_false("is_trivially_move_assignable<int[3]>::value", asc::std::is_trivially_move_assignable<int[3]>::value);

    // void — not referenceable, should be false
    expect_false("is_trivially_move_assignable<void>::value", asc::std::is_trivially_move_assignable<void>::value);

    // const-qualified — not assignable
    expect_false(
        "is_trivially_move_assignable<const int>::value", asc::std::is_trivially_move_assignable<const int>::value);

    return g_failures == 0 ? 0 : 1;
}
