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

#include <asc/std/span>
#include <cstddef>
#include <type_traits>

namespace s = asc::std;

template <class A>
constexpr bool aliases()
{
    static_assert(std::is_same_v<typename A::element_type, const int>);
    static_assert(std::is_same_v<typename A::value_type, int>);
    static_assert(std::is_same_v<typename A::size_type, std::size_t>);
    static_assert(std::is_same_v<typename A::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<typename A::pointer, const int*>);
    static_assert(std::is_same_v<typename A::reference, const int&>);
    static_assert(std::is_same_v<typename A::iterator, const int*>);
    static_assert(std::is_same_v<typename A::reverse_iterator, s::reverse_iterator<const int*>>);
    return true;
}
static_assert(aliases<s::span<const int, 3>>());
static_assert(aliases<s::span<const int>>());
using fixed = s::span<int, 3>;
static_assert(std::is_same_v<fixed::const_pointer, const int*>);
static_assert(std::is_same_v<fixed::const_reference, const int&>);
static_assert(fixed::extent == 3 && s::span<int>::extent == s::dynamic_extent);

constexpr bool conversions()
{
    const s::array<int, 3> data{{7, -2, 4}};
    s::span<const int> dynamic(data);
    s::span<const int, 3> fixed_extent(dynamic);
    return dynamic.data() == data.data() && dynamic.size() == 3 && fixed_extent.data() == data.data() &&
        fixed_extent.size() == 3 && fixed_extent[1] == -2;
}
static_assert(conversions());

int main()
{
    return conversions() ? 0 : 1;
}
