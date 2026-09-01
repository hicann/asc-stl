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

#include <asc/std/__utility/move.h>
#include <type_traits>

struct ThrowingMove {
    ThrowingMove(const ThrowingMove&) noexcept = default;
    ThrowingMove(ThrowingMove&&) noexcept(false);
};

struct NothrowMove {
    NothrowMove(const NothrowMove&) = delete;
    NothrowMove(NothrowMove&&) noexcept = default;
};

static_assert(std::is_same_v<decltype(asc::std::move(*static_cast<int*>(nullptr))), int&&>);
static_assert(
    std::is_same_v<decltype(asc::std::move_if_noexcept(*static_cast<ThrowingMove*>(nullptr))), const ThrowingMove&>);
static_assert(std::is_same_v<decltype(asc::std::move_if_noexcept(*static_cast<NothrowMove*>(nullptr))), NothrowMove&&>);

int main()
{
    int value = 7;
    int&& moved = asc::std::move(value);  // NOLINT(build/include_what_you_use)
    return moved == 7 ? 0 : 1;
}
