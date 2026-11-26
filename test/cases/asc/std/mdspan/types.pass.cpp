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

#include <asc/std/mdspan>
#include <cstddef>
#include <type_traits>

namespace s = asc::std;

using shape = s::extents<int, 2, 3>;
template <class Layout>
constexpr bool mapping_types()
{
    using map = typename Layout::template mapping<shape>;
    static_assert(std::is_same_v<typename map::extents_type, shape>);
    static_assert(std::is_same_v<typename map::index_type, int>);
    static_assert(std::is_same_v<typename map::size_type, unsigned>);
    static_assert(std::is_same_v<typename map::rank_type, std::size_t>);
    static_assert(std::is_same_v<typename map::layout_type, Layout>);
    static_assert(std::is_base_of_v<typename map::base, map>);
    return true;
}
static_assert(mapping_types<s::layout_left>() && mapping_types<s::layout_right>() && mapping_types<s::layout_stride>());
using view = s::mdspan<const int, shape>;
static_assert(std::is_base_of_v<view::base, view>);
using slice = s::strided_slice<short, unsigned, long>;
static_assert(std::is_same_v<slice::offset_type, short>);
static_assert(std::is_same_v<slice::extent_type, unsigned>);
static_assert(std::is_same_v<slice::stride_type, long>);
static_assert(std::is_same_v<decltype(slice::offset), short> && std::is_same_v<decltype(slice::extent), unsigned> &&
    std::is_same_v<decltype(slice::stride), long>);

int main()
{}
