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

#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/type_traits>
namespace r = asc::std::ranges;
namespace s = asc::std;
struct positive {
    bool operator()(int n) const
    {
        return n > 0;
    }
};
struct negate {
    int operator()(int n) const
    {
        return -n;
    }
};
struct noncommon {
    int* first;
    auto begin() const
    {
        return s::counted_iterator(first, 3);
    }
    auto end() const
    {
        return s::default_sentinel;
    }
};
int main()
{
    int values[]{4, 1, -6};
    using ref = r::ref_view<int[3]>;
    r::ref_view referenced(values);
    r::owning_view owned(s::array<int, 2>{{2, 7}});
    r::single_view one(short{-3});
    r::iota_view count(-4, 1);
    r::repeat_view repeat(9, 2u);
    r::drop_view drop(values, 1);
    r::drop_while_view drop_while(values, positive{});
    r::filter_view filter(values, positive{});
    r::take_view take(values, 2);
    r::take_while_view take_while(values, positive{});
    r::reverse_view reversed(values);
    r::transform_view transformed(values, negate{});
    static_assert(s::is_same_v<decltype(referenced), ref>);
    static_assert(s::is_same_v<decltype(owned), r::owning_view<s::array<int, 2>>>);
    static_assert(s::is_same_v<decltype(one), r::single_view<short>>);
    static_assert(s::is_same_v<decltype(count), r::iota_view<int, int>>);
    static_assert(s::is_same_v<decltype(repeat), r::repeat_view<int, unsigned>>);
    static_assert(s::is_same_v<decltype(drop), r::drop_view<ref>>);
    static_assert(s::is_same_v<decltype(drop_while), r::drop_while_view<ref, positive>>);
    static_assert(s::is_same_v<decltype(filter), r::filter_view<ref, positive>>);
    static_assert(s::is_same_v<decltype(take), r::take_view<ref>>);
    static_assert(s::is_same_v<decltype(take_while), r::take_while_view<ref, positive>>);
    static_assert(s::is_same_v<decltype(reversed), r::reverse_view<ref>>);
    static_assert(s::is_same_v<decltype(transformed), r::transform_view<ref, negate>>);
    if (referenced.begin() != values || owned.back() != 7 || one.front() != -3 || count.size() != 5 ||
        repeat.size() != 2 || *repeat.begin() != 9 || drop.front() != 1 || drop_while.front() != -6 ||
        filter.front() != 4 || take.size() != 2 || r::distance(take_while) != 2 || reversed.front() != -6 ||
        transformed.front() != -4)
        return 1;
    noncommon range{values};
    r::common_view common(range);
    static_assert(s::is_same_v<decltype(common), r::common_view<r::ref_view<noncommon>>>);
    if (r::distance(common) != 3 || common.front() != 4)
        return 2;
    r::subrange endpoints(values, values + 3);
    r::subrange counted_endpoints(values + 1, values + 3, 2u);
    r::subrange from_range(values);
    r::subrange counted_range(range, 3u);
    static_assert(s::is_same_v<decltype(endpoints), r::subrange<int*>>);
    static_assert(s::is_same_v<decltype(counted_endpoints), r::subrange<int*>>);
    static_assert(s::is_same_v<decltype(from_range), r::subrange<int*>>);
    static_assert(s::is_same_v<decltype(counted_range),
        r::subrange<s::counted_iterator<int*>, s::default_sentinel_t, r::subrange_kind::sized>>);
    return endpoints.size() == 3 && counted_endpoints.front() == 1 && from_range.back() == -6 &&
            counted_range.size() == 3 && *counted_range.begin() == 4 ?
        0 :
        3;
}
