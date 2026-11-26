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

#include <asc/std/inplace_vector>
#include <cstddef>
#include <type_traits>

namespace s = asc::std;

template <class A>
constexpr bool aliases()
{
    static_assert(std::is_same_v<typename A::value_type, int>);
    static_assert(std::is_same_v<typename A::size_type, std::size_t>);
    static_assert(std::is_same_v<typename A::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<typename A::reference, int&>);
    static_assert(std::is_same_v<typename A::const_reference, const int&>);
    static_assert(std::is_same_v<typename A::pointer, int*>);
    static_assert(std::is_same_v<typename A::const_pointer, const int*>);
    static_assert(std::is_same_v<typename A::iterator, int*>);
    static_assert(std::is_same_v<typename A::const_iterator, const int*>);
    return true;
}
static_assert(aliases<s::inplace_vector<int, 0>>());
static_assert(aliases<s::inplace_vector<int, 3>>());

int main()
{}
