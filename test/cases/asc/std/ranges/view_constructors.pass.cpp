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
#include <asc/std/tuple>
#include <list>

namespace r = asc::std::ranges;
namespace s = asc::std;

struct integer {
    int value = 13;
};
struct positive {
    bool operator()(int x) const
    {
        return x > 0;
    }
};
struct increment {
    int operator()(int x) const
    {
        return x + 1;
    }
};

template <class V>
bool starts_empty()
{
    V v{};
    return v.begin() == v.end();
}

int cvref_overloads()
{
    using array = s::array<int, 3>;
    using own = r::owning_view<array>;
    r::owning_view<s::array<int, 0>> default_owner{};
    if (!default_owner.empty())
        return 10;
    r::dangling dangling{};
    s::from_range_t tag{};
    (void)dangling;
    (void)tag;
    array data{{3, 1, -4}};
    r::drop_view<own> dropped(own(array(data)), 1);
    r::take_view<own> taken(own(array(data)), 2);
    r::take_while_view<own, positive> positives(own(array(data)), positive{});
    auto it = positives.begin();
    if (*it++ != 3 || *it++ != 1 || it != positives.end() || dropped.end() - dropped.begin() != 2 ||
        *dropped.begin() != 1 || taken.end() - taken.begin() != 2)
        return 11;
    const auto zipped = r::views::zip(data, data);
    if (zipped.end() - zipped.begin() != 3 || s::get<1>(zipped.begin()[2]) != -4)
        return 12;
    r::iota_view<int, int> iota(0, 3);
    decltype(iota.begin()) initial{};
    if (*initial != 0 || *(2 + iota.begin()) != 2 || *(iota.end() - 1) != 2)
        return 13;
    std::list<int> list{7, 1, -5};
    using iterator = decltype(list.begin());
    r::subrange<iterator, iterator, r::subrange_kind::sized> stored_size(list);
    return stored_size.size() == 3 && stored_size.next().size() == 2 && stored_size.front() == 7 ? 0 : 14;
}

int main()
{
    if (int failure = cvref_overloads())
        return failure;
    using base = r::empty_view<int>;
    if (!starts_empty<r::take_view<base>>() || !starts_empty<r::drop_view<base>>() ||
        !starts_empty<r::take_while_view<base, positive>>() || !starts_empty<r::drop_while_view<base, positive>>() ||
        !starts_empty<r::filter_view<base, positive>>() || !starts_empty<r::transform_view<base, increment>>() ||
        !starts_empty<r::reverse_view<base>>() || !starts_empty<r::zip_view<base, base>>() ||
        !starts_empty<r::repeat_view<int, unsigned>>() || !starts_empty<r::iota_view<int, int>>())
        return 1;
    r::single_view<integer> single{};
    if (single.begin() == single.end() || single.front().value != 13)
        return 2;
    int input[] = {-4, 2, 8};
    using counted = s::counted_iterator<int*>;
    using src = r::subrange<counted, s::default_sentinel_t>;
    if (!starts_empty<src>() || !starts_empty<r::common_view<src>>())
        return 3;
    r::common_view<src> common(src(counted(input, 3), s::default_sentinel));
    const auto& c = common;
    auto it = c.begin();
    if (c.size() != 3 || common.size() != 3 || *it++ != -4 || *it++ != 2 || *it++ != 8 || it != c.end() ||
        common.base().begin().base() != input || static_cast<decltype(common)&&>(common).base().size() != 3)
        return 4;
    r::subrange<int*, int*> slice(input, input + 3);
    r::subrange<int*, int*> explicit_size(slice, 3);
    if (explicit_size.size() != 3 || explicit_size.back() != 8)
        return 5;
    r::repeat_view<int, int> repeated(s::piecewise_construct, s::tuple<int>(-4), s::tuple<int>(3));
    if (repeated.size() != 3 || repeated.begin()[2] != -4 || &*repeated.begin() != &repeated.begin()[1])
        return 6;
    r::iota_view<int, s::unreachable_sentinel_t> open(7);
    r::iota_view<int, s::unreachable_sentinel_t> remaining(open.begin() + 2, open.end());
    if (remaining.begin() == remaining.end() || *remaining.begin() != 9)
        return 7;
    r::iota_view<int, long> different(2, 5L);
    r::iota_view<int, long> tail(different.begin() + 1, different.end());
    return tail.size() == 2 && *tail.begin() == 3 ? 0 : 8;
}
