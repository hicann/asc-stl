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

#include <asc/std/__type_traits/is_swappable.h>

struct MoveOnly {
    MoveOnly() = default;
    MoveOnly(MoveOnly&&) noexcept = default;
    MoveOnly& operator=(MoveOnly&&) noexcept = default;
};

struct ThrowingMove {
    ThrowingMove() = default;
    ThrowingMove(ThrowingMove&&) noexcept(false);
    ThrowingMove& operator=(ThrowingMove&&) noexcept(false);
};

struct Immovable {
    Immovable() = default;
    Immovable(Immovable&&) = delete;
    Immovable& operator=(Immovable&&) = delete;
};

namespace adl {
struct Hidden {
    friend void swap(Hidden&, Hidden&) noexcept
    {}
};

struct Throwing {};

void swap(Throwing&, Throwing&) noexcept(false);  // NOLINT(build/include_what_you_use)
}  // namespace adl

struct Incomplete;

static_assert(asc::std::is_swappable_v<int>);
static_assert(asc::std::is_nothrow_swappable_v<int>);
static_assert(asc::std::is_swappable_v<MoveOnly>);
static_assert(asc::std::is_nothrow_swappable_v<MoveOnly>);
static_assert(asc::std::is_swappable_v<ThrowingMove>);
static_assert(!asc::std::is_nothrow_swappable_v<ThrowingMove>);
static_assert(!asc::std::is_swappable_v<Immovable>);
static_assert(asc::std::is_swappable_v<adl::Hidden>);
static_assert(asc::std::is_nothrow_swappable_v<adl::Hidden>);
static_assert(asc::std::is_swappable_v<adl::Throwing>);
static_assert(!asc::std::is_nothrow_swappable_v<adl::Throwing>);
static_assert(asc::std::is_swappable_v<int[3]>);
static_assert(!asc::std::is_swappable_v<void>);
static_assert(!asc::std::__is_complete_and_nothrow_swappable_v<Incomplete>);

int main()
{
    return 0;
}
