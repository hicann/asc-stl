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

#include <asc/std/__type_traits/is_move_assignable.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_move_assignable] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_move_assignable] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// --- Test types ---

// Trivially move-assignable
struct Trivial {
    int x;
    float y;
};

// Has explicit move assignment
struct ExplicitMove {
    int val;
    ExplicitMove& operator=(ExplicitMove&& other) noexcept
    {
        val = other.val;
        return *this;
    }
};

// Deleted move assignment
struct DeletedMove {
    int val;
    DeletedMove& operator=(DeletedMove&&) = delete;
};

// Has user-provided copy assignment but no move assignment (move will fall back to copy)
struct CopyOnly {
    int val;
    CopyOnly& operator=(const CopyOnly& other)
    {
        val = other.val;
        return *this;
    }
};

// Non-assignable (has a reference member, implicitly deleted)
struct NonAssignable {
    int& ref;
    NonAssignable(int& r) : ref(r)  // NOLINT(runtime/explicit)
    {}
};

int main()
{
    // --- Fundamental types ---
    expect_true("is_move_assignable<int>::value", asc::std::is_move_assignable<int>::value);
    expect_true("is_move_assignable_v<int>", asc::std::is_move_assignable_v<int>);

    expect_true("is_move_assignable<double>::value", asc::std::is_move_assignable<double>::value);
    expect_true("is_move_assignable_v<double>", asc::std::is_move_assignable_v<double>);

    expect_true("is_move_assignable<float>::value", asc::std::is_move_assignable<float>::value);

    expect_true("is_move_assignable<int*>::value", asc::std::is_move_assignable<int*>::value);

    // --- const-qualified types: cannot assign to const lvalue ---
    expect_false("is_move_assignable<const int>::value", asc::std::is_move_assignable<const int>::value);
    expect_false("is_move_assignable_v<const int>", asc::std::is_move_assignable_v<const int>);

    // --- Reference types ---
    expect_true("is_move_assignable<int&>::value", asc::std::is_move_assignable<int&>::value);

    // --- void ---
    expect_false("is_move_assignable<void>::value", asc::std::is_move_assignable<void>::value);
    expect_false("is_move_assignable_v<void>", asc::std::is_move_assignable_v<void>);

    // --- User-defined types ---
    expect_true("is_move_assignable<Trivial>::value", asc::std::is_move_assignable<Trivial>::value);
    expect_true("is_move_assignable_v<Trivial>", asc::std::is_move_assignable_v<Trivial>);

    expect_true("is_move_assignable<ExplicitMove>::value", asc::std::is_move_assignable<ExplicitMove>::value);

    expect_false("is_move_assignable<DeletedMove>::value", asc::std::is_move_assignable<DeletedMove>::value);
    expect_false("is_move_assignable_v<DeletedMove>", asc::std::is_move_assignable_v<DeletedMove>);

    // CopyOnly: move assignment falls back to copy assignment, so it IS move-assignable
    expect_true("is_move_assignable<CopyOnly>::value", asc::std::is_move_assignable<CopyOnly>::value);

    // NonAssignable: has reference member, assignment is implicitly deleted
    expect_false("is_move_assignable<NonAssignable>::value", asc::std::is_move_assignable<NonAssignable>::value);

    return g_failures == 0 ? 0 : 1;
}
