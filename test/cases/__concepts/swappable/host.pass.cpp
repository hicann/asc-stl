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

#include <asc/std/__concepts/swappable.h>

namespace custom {
struct Number {
    int value;
};

constexpr void swap(Number& lhs, Number& rhs) noexcept  // NOLINT(build/include_what_you_use)
{
    int temporary = lhs.value;
    lhs.value = rhs.value;
    rhs.value = temporary;
}
}  // namespace custom

static_assert(asc::std::swappable<int>);
static_assert(asc::std::swappable<custom::Number>);

constexpr bool verify_ranges_swap()
{
    int lhs[] = {1, 2, 3};
    int rhs[] = {4, 5, 6};
    asc::std::ranges::swap(lhs, rhs);
    custom::Number first{7};
    custom::Number second{8};
    asc::std::ranges::swap(first, second);
    return lhs[0] == 4 && lhs[2] == 6 && rhs[0] == 1 && rhs[2] == 3 && first.value == 8 && second.value == 7;
}

static_assert(verify_ranges_swap());

int main()
{
    return verify_ranges_swap() ? 0 : 1;
}
