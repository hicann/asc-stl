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

#include <asc/std/__concepts/totally_ordered.h>

struct NotBoolean {};

struct InvalidOrdering {
    friend constexpr bool operator==(InvalidOrdering, InvalidOrdering) noexcept
    {
        return true;
    }
    friend constexpr bool operator!=(InvalidOrdering, InvalidOrdering) noexcept
    {
        return false;
    }
    friend constexpr NotBoolean operator<(InvalidOrdering, InvalidOrdering) noexcept
    {
        return {};
    }
    friend constexpr NotBoolean operator>(InvalidOrdering, InvalidOrdering) noexcept
    {
        return {};
    }
    friend constexpr NotBoolean operator<=(InvalidOrdering, InvalidOrdering) noexcept
    {
        return {};
    }
    friend constexpr NotBoolean operator>=(InvalidOrdering, InvalidOrdering) noexcept
    {
        return {};
    }
};

static_assert(asc::std::totally_ordered<int>);
static_assert(asc::std::totally_ordered_with<int, long>);
static_assert(!asc::std::totally_ordered<InvalidOrdering>);

int main()
{
    return 0;
}
