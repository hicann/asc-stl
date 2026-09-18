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

#include <asc/std/__type_traits/is_move_constructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_move_constructible] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// Types with various move-construction semantics
struct MoveCtor {
    MoveCtor(MoveCtor&&) = default;
    MoveCtor() = default;
};
struct NoMoveCtor {
    NoMoveCtor(NoMoveCtor&&) = delete;
    NoMoveCtor() = default;
};
struct ExplicitMove {
    ExplicitMove() = default;
    ExplicitMove(ExplicitMove&&)
    {}
};
struct CopyOnlyDeletedMove {
    CopyOnlyDeletedMove() = default;
    CopyOnlyDeletedMove(const CopyOnlyDeletedMove&) = default;
    CopyOnlyDeletedMove(CopyOnlyDeletedMove&&) = delete;
};

int main()
{
    // --- Fundamental types: all move constructible ---
    expect_true("is_move_constructible_v<int>", asc::std::is_move_constructible_v<int>, true);
    expect_true("is_move_constructible_v<float>", asc::std::is_move_constructible_v<float>, true);
    expect_true("is_move_constructible_v<double>", asc::std::is_move_constructible_v<double>, true);
    expect_true("is_move_constructible_v<char>", asc::std::is_move_constructible_v<char>, true);
    expect_true("is_move_constructible_v<bool>", asc::std::is_move_constructible_v<bool>, true);
    expect_true("is_move_constructible_v<long>", asc::std::is_move_constructible_v<long>, true);
    expect_true("is_move_constructible_v<unsigned>", asc::std::is_move_constructible_v<unsigned>, true);

    // --- Pointer types ---
    expect_true("is_move_constructible_v<int*>", asc::std::is_move_constructible_v<int*>, true);
    expect_true("is_move_constructible_v<void*>", asc::std::is_move_constructible_v<void*>, true);

    // --- Reference types ---
    expect_true("is_move_constructible_v<int&>", asc::std::is_move_constructible_v<int&>, true);
    expect_true("is_move_constructible_v<int&&>", asc::std::is_move_constructible_v<int&&>, true);

    // --- void: not move constructible ---
    expect_true("is_move_constructible_v<void>", asc::std::is_move_constructible_v<void>, false);

    // --- Array types: not move constructible ---
    expect_true("is_move_constructible_v<int[5]>", asc::std::is_move_constructible_v<int[5]>, false);

    // --- User-defined types ---
    expect_true("is_move_constructible_v<MoveCtor>", asc::std::is_move_constructible_v<MoveCtor>, true);
    expect_true("is_move_constructible_v<NoMoveCtor>", asc::std::is_move_constructible_v<NoMoveCtor>, false);
    expect_true("is_move_constructible_v<ExplicitMove>", asc::std::is_move_constructible_v<ExplicitMove>, true);
    expect_true(
        "is_move_constructible_v<CopyOnlyDeletedMove>", asc::std::is_move_constructible_v<CopyOnlyDeletedMove>, false);

    // --- Using ::value form ---
    expect_true("is_move_constructible<int>::value", asc::std::is_move_constructible<int>::value, true);
    expect_true("is_move_constructible<NoMoveCtor>::value", asc::std::is_move_constructible<NoMoveCtor>::value, false);
    expect_true("is_move_constructible<void>::value", asc::std::is_move_constructible<void>::value, false);

    return g_failures == 0 ? 0 : 1;
}
