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

#include <asc/std/__type_traits/is_copy_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_copy_assignable] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Test types
struct CopyAssignable {
    int x;
    CopyAssignable& operator=(const CopyAssignable&) = default;
};

struct NotCopyAssignable {
    int x;
    NotCopyAssignable& operator=(const NotCopyAssignable&) = delete;
};

struct CopyAssignableWithMembers {
    int a;
    double b;
};

struct WithPrivate {
private:
    int x;

public:
    WithPrivate() : x(0)
    {}
};

struct Abstract {
    virtual void f() = 0;
};

struct WithRef {
    int& ref;
    WithRef(int& r) : ref(r)  // NOLINT(runtime/explicit)
    {}
    WithRef& operator=(const WithRef&) = default;
};

int main()
{
    // Basic types
    expect_true("is_copy_assignable_v<int>", asc::std::is_copy_assignable_v<int>, true);
    expect_true("is_copy_assignable_v<float>", asc::std::is_copy_assignable_v<float>, true);
    expect_true("is_copy_assignable_v<double>", asc::std::is_copy_assignable_v<double>, true);
    expect_true("is_copy_assignable_v<char>", asc::std::is_copy_assignable_v<char>, true);
    expect_true("is_copy_assignable_v<bool>", asc::std::is_copy_assignable_v<bool>, true);

    // Pointer types
    expect_true("is_copy_assignable_v<int*>", asc::std::is_copy_assignable_v<int*>, true);
    expect_true("is_copy_assignable_v<void*>", asc::std::is_copy_assignable_v<void*>, true);

    // Reference types - references are copy-assignable (assigning through reference)
    expect_true("is_copy_assignable_v<int&>", asc::std::is_copy_assignable_v<int&>, true);

    // Array types - arrays are not copy assignable
    expect_true("is_copy_assignable_v<int[5]>", asc::std::is_copy_assignable_v<int[5]>, false);

    // void is not copy assignable
    expect_true("is_copy_assignable_v<void>", asc::std::is_copy_assignable_v<void>, false);

    // User-defined types
    expect_true("is_copy_assignable_v<CopyAssignable>", asc::std::is_copy_assignable_v<CopyAssignable>, true);
    expect_true("is_copy_assignable_v<NotCopyAssignable>", asc::std::is_copy_assignable_v<NotCopyAssignable>, false);
    expect_true("is_copy_assignable_v<CopyAssignableWithMembers>",
        asc::std::is_copy_assignable_v<CopyAssignableWithMembers>, true);

    // const-qualified types are not copy assignable (cannot assign to const)
    expect_true("is_copy_assignable_v<const int>", asc::std::is_copy_assignable_v<const int>, false);

    // Function types are not copy assignable
    expect_true("is_copy_assignable_v<void()>", asc::std::is_copy_assignable_v<void()>, false);

    // struct with ::value form
    expect_true("is_copy_assignable<int>::value", asc::std::is_copy_assignable<int>::value, true);
    expect_true(
        "is_copy_assignable<NotCopyAssignable>::value", asc::std::is_copy_assignable<NotCopyAssignable>::value, false);

    return g_failures == 0 ? 0 : 1;
}
