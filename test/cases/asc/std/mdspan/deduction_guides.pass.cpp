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
#include <asc/std/type_traits>
namespace s = asc::std;
int main()
{
    int values[] = {2, 4, 6, 8, 10, 12};
    int* ptr = values;
    s::extents dynamic(2, 3u);
    static_assert(s::is_same_v<decltype(dynamic), s::dextents<s::size_t, 2>>);
    s::mdspan mixed(ptr, 2u, s::integral_constant<int, 3>{});
    static_assert(s::is_same_v<decltype(mixed), s::mdspan<int, s::extents<s::size_t, s::dynamic_extent, 3>>>);
    s::mdspan scalar(ptr);
    static_assert(s::is_same_v<decltype(scalar), s::mdspan<int, s::extents<s::size_t>>>);
    s::mdspan fixed(values);
    static_assert(s::is_same_v<decltype(fixed), s::mdspan<int, s::extents<s::size_t, 6>>>);
    const s::array<short, 2> shape{{2, 3}};
    s::mdspan from_array(ptr, shape);
    static_assert(s::is_same_v<decltype(from_array), s::mdspan<int, s::dextents<s::size_t, 2>>>);
    s::mdspan from_span(ptr, s::span<const short, 2>(shape));
    static_assert(s::is_same_v<decltype(from_span), decltype(from_array)>);
    using dims = s::extents<short, 2, s::dynamic_extent>;
    const dims extents(3);
    s::mdspan from_extents(ptr, extents);
    static_assert(s::is_same_v<decltype(from_extents), s::mdspan<int, dims>>);
    const s::layout_left::mapping<dims> columns(extents);
    s::mdspan from_mapping(ptr, columns);
    static_assert(s::is_same_v<decltype(from_mapping), s::mdspan<int, dims, s::layout_left>>);
    s::mdspan from_accessor(ptr, columns, s::default_accessor<const int>{});
    static_assert(s::is_same_v<decltype(from_accessor), s::mdspan<const int, dims, s::layout_left>>);
    s::strided_slice slice{1u, 4L, short{2}};
    static_assert(s::is_same_v<decltype(slice), s::strided_slice<unsigned, long, short>>);
    if (dynamic.extent(0) != 2 || dynamic.extent(1) != 3 || mixed(1, 0) != 8 || scalar() != 2 || fixed(5) != 12)
        return 1;
    if (from_array(1, 0) != 8 || from_span(0, 2) != 6 || from_extents(1, 1) != 10)
        return 2;
    return from_mapping(1, 0) == 4 && from_accessor(0, 2) == 10 && slice.offset == 1 && slice.extent == 4 &&
            slice.stride == 2 ?
        0 :
        3;
}
