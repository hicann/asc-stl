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
#include <asc/std/array>
#include <asc/std/type_traits>
namespace s = asc::std;
struct buffer {
    int* first;
    int* begin() const
    {
        return first;
    }
    int* end() const
    {
        return first + 3;
    }
    int* data() const
    {
        return first;
    }
    s::size_t size() const
    {
        return 3;
    }
};
int main()
{
    const long native[]{-7, 4, 8};
    s::array<int, 3> data{{1, 2, 3}};
    const auto& const_data = data;
    s::span from_native(native);
    s::span from_array(data);
    s::span from_const_array(const_data);
    s::span from_iter(data.begin(), s::integral_constant<int, 2>{});
    s::span from_end(data.begin() + 1, data.end());
    buffer range{data.begin()};
    s::span from_range(range);
    static_assert(s::is_same_v<decltype(from_native), s::span<const long, 3>>);
    static_assert(s::is_same_v<decltype(from_array), s::span<int, 3>>);
    static_assert(s::is_same_v<decltype(from_const_array), s::span<const int, 3>>);
    static_assert(s::is_same_v<decltype(from_iter), s::span<int, 2>>);
    static_assert(s::is_same_v<decltype(from_end), s::span<int>> && s::is_same_v<decltype(from_range), s::span<int>>);
    from_range[1] = 11;
    return from_native[0] == -7 && from_array[1] == 11 && from_const_array[1] == 11 && from_iter.size() == 2 &&
            from_iter[1] == 11 && from_end.size() == 2 && from_end.front() == 11 && from_range.size() == 3 ?
        0 :
        1;
}
