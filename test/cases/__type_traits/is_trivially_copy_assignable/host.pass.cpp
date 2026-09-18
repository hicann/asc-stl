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

#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    bool ok = got;
    std::cout << "[host][is_trivially_copy_assignable] " << expr << " = " << (got ? "true" : "false")
              << " (expected true) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    bool ok = !got;
    std::cout << "[host][is_trivially_copy_assignable] " << expr << " = " << (got ? "true" : "false")
              << " (expected false) " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Trivially copy assignable types
struct TrivialStruct {
    int a;
    float b;
};

struct TrivialStructWithDefaultCtor {
    int a;
    float b;
    TrivialStructWithDefaultCtor() = default;
};

// Non-trivially copy assignable types
struct NonTrivialCopyAssign {
    int a;
    NonTrivialCopyAssign& operator=(const NonTrivialCopyAssign& other)
    {
        a = other.a;
        return *this;
    }
};

struct WithReference {
    int& ref;
    WithReference(int& r) : ref(r)  // NOLINT(runtime/explicit)
    {}
};

int main()
{
    // Basic scalar types - trivially copy assignable
    expect_true("is_trivially_copy_assignable<int>::value", asc::std::is_trivially_copy_assignable<int>::value);
    expect_true("is_trivially_copy_assignable_v<int>", asc::std::is_trivially_copy_assignable_v<int>);
    expect_true("is_trivially_copy_assignable<float>::value", asc::std::is_trivially_copy_assignable<float>::value);
    expect_true("is_trivially_copy_assignable_v<float>", asc::std::is_trivially_copy_assignable_v<float>);
    expect_true("is_trivially_copy_assignable<double>::value", asc::std::is_trivially_copy_assignable<double>::value);
    expect_true("is_trivially_copy_assignable_v<double>", asc::std::is_trivially_copy_assignable_v<double>);
    expect_true("is_trivially_copy_assignable<char>::value", asc::std::is_trivially_copy_assignable<char>::value);
    expect_true("is_trivially_copy_assignable<long>::value", asc::std::is_trivially_copy_assignable<long>::value);
    expect_true("is_trivially_copy_assignable<bool>::value", asc::std::is_trivially_copy_assignable<bool>::value);

    // Pointer types - trivially copy assignable
    expect_true("is_trivially_copy_assignable<int*>::value", asc::std::is_trivially_copy_assignable<int*>::value);
    expect_true("is_trivially_copy_assignable_v<int*>", asc::std::is_trivially_copy_assignable_v<int*>);

    // Trivial struct
    expect_true("is_trivially_copy_assignable<TrivialStruct>::value",
        asc::std::is_trivially_copy_assignable<TrivialStruct>::value);
    expect_true(
        "is_trivially_copy_assignable_v<TrivialStruct>", asc::std::is_trivially_copy_assignable_v<TrivialStruct>);
    expect_true("is_trivially_copy_assignable<TrivialStructWithDefaultCtor>::value",
        asc::std::is_trivially_copy_assignable<TrivialStructWithDefaultCtor>::value);

    // Non-trivially copy assignable types
    expect_false("is_trivially_copy_assignable<NonTrivialCopyAssign>::value",
        asc::std::is_trivially_copy_assignable<NonTrivialCopyAssign>::value);
    expect_false("is_trivially_copy_assignable_v<NonTrivialCopyAssign>",
        asc::std::is_trivially_copy_assignable_v<NonTrivialCopyAssign>);

    // const int is NOT trivially copy assignable (can't assign to const)
    expect_false(
        "is_trivially_copy_assignable<const int>::value", asc::std::is_trivially_copy_assignable<const int>::value);
    expect_false("is_trivially_copy_assignable_v<const int>", asc::std::is_trivially_copy_assignable_v<const int>);

    // Type with reference member - copy assignment is deleted, so not trivially copy assignable
    expect_false("is_trivially_copy_assignable<WithReference>::value",
        asc::std::is_trivially_copy_assignable<WithReference>::value);
    expect_false(
        "is_trivially_copy_assignable_v<WithReference>", asc::std::is_trivially_copy_assignable_v<WithReference>);

    return g_failures == 0 ? 0 : 1;
}
