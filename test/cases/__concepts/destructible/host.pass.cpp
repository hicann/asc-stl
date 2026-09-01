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

#include <asc/std/__concepts/destructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][destructible] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][destructible] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

struct HasDestructor {};
struct HasVirtualDtor {
    virtual ~HasVirtualDtor()
    {}
};
struct ThrowingDtor {
    ~ThrowingDtor() noexcept(false)
    {}
};
struct ProtectedDtor {
protected:
    ~ProtectedDtor()
    {}
};
struct PrivateDtor {
private:
    ~PrivateDtor()
    {}
};
struct DeletedDtor {
    ~DeletedDtor() = delete;
};

int main()
{
    // Basic object types — destructible and noexcept
    expect_true("destructible<int>", asc::std::destructible<int>);
    expect_true("destructible<float>", asc::std::destructible<float>);
    expect_true("destructible<double>", asc::std::destructible<double>);
    expect_true("destructible<char>", asc::std::destructible<char>);
    expect_true("destructible<bool>", asc::std::destructible<bool>);
    expect_true("destructible<int*>", asc::std::destructible<int*>);

    // Reference types — always true per specialization
    expect_true("destructible<int&>", asc::std::destructible<int&>);
    expect_true("destructible<int&&>", asc::std::destructible<int&&>);

    // Array types — true if element type is destructible
    expect_true("destructible<int[5]>", asc::std::destructible<int[5]>);
    expect_true("destructible<int[1]>", asc::std::destructible<int[1]>);

    // Custom types with accessible noexcept destructors
    expect_true("destructible<HasDestructor>", asc::std::destructible<HasDestructor>);
    expect_true("destructible<HasVirtualDtor>", asc::std::destructible<HasVirtualDtor>);

    // Type with throwing destructor — not nothrow destructible
    expect_false("destructible<ThrowingDtor>", asc::std::destructible<ThrowingDtor>);

    // Types with inaccessible or deleted destructors
    expect_false("destructible<ProtectedDtor>", asc::std::destructible<ProtectedDtor>);
    expect_false("destructible<PrivateDtor>", asc::std::destructible<PrivateDtor>);
    expect_false("destructible<DeletedDtor>", asc::std::destructible<DeletedDtor>);

    // Non-object types
    expect_false("destructible<void>", asc::std::destructible<void>);
    expect_false("destructible<void()>", asc::std::destructible<void()>);

    return g_failures == 0 ? 0 : 1;
}
