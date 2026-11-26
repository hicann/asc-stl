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

#ifndef ASC_STL_TEST_RANGES_VIEWS_H
#define ASC_STL_TEST_RANGES_VIEWS_H

#include <asc/std/ranges>
#include <asc/std/array>

namespace asc_stl_test_ranges {
struct before {
    int limit = 1;
    CANN_ASC_STL_API bool operator()(int x) const
    {
        return x < limit;
    }
};
struct twice {
    CANN_ASC_STL_API int operator()(int x) const
    {
        return x * 2;
    }
};

template <class V>
CANN_ASC_STL_API bool same_base(V& v, int* p)
{
    auto cloned = v;
    return v.base().begin() == p && static_cast<V&&>(cloned).base().begin() == p;
}

template <class V>
CANN_ASC_STL_API bool own_access(V& v)
{
    return v.size() == 3 && !v.empty() && static_cast<bool>(v) && v.data() == v.begin() && v.end() == v.data() + 3 &&
        &v.front() == v.data() && v.back() == 5 && v[1] == 0 && v.base().data() == v.data();
}

CANN_ASC_STL_API int check_views(int seed)
{
    namespace s = asc::std;
    namespace r = asc::std::ranges;
    using arr = s::array<int, 3>;
    r::owning_view<arr> own(arr{{seed, 0, 5}});
    const auto& co = own;
    if (!own_access(own) || !own_access(co))
        return 1;
    static_assert(s::is_same_v<decltype(static_cast<decltype(own)&&>(own).base()), arr&&>);
    static_assert(s::is_same_v<decltype(static_cast<const decltype(own)&&>(own).base()), const arr&&>);
    if (static_cast<const decltype(own)&&>(own).base().front() != 7 ||
        static_cast<decltype(own)&&>(own).base().back() != 5)
        return 2;
    arr values{{0, seed, 2}};
    r::ref_view<arr> ref(values);
    if (ref.data() != values.data() || ref.begin() != ref.data() || ref.empty() || ref.end() != ref.begin() + 3 ||
        &ref.base() != &values || ref.size() != 3)
        return 3;
    const auto empty = r::empty_view<int>{};
    if (empty.begin() != empty.end() || empty.data() != nullptr || !empty.empty() || empty.size())
        return 4;
    const int five = 5;
    r::single_view<int> from_lvalue(five), from_rvalue(7), in_place(s::in_place, -3);
    const auto& c1 = in_place;
    if (from_rvalue.empty() || from_lvalue.front() != 5 || c1.data() != c1.begin() || *c1.begin() != -3 ||
        c1.end() - c1.begin() != 1 || in_place.data() != in_place.begin() || in_place.end() - in_place.begin() != 1)
        return 5;
    r::take_view<decltype(ref)> take(ref, 2);
    r::drop_view<decltype(ref)> drop(ref, 1);
    r::reverse_view<decltype(ref)> reverse(ref);
    r::drop_while_view<decltype(ref), before> drop_while(ref, before{1});
    r::take_while_view<decltype(ref), before> take_while(ref, before{1});
    r::filter_view<decltype(ref), before> filter(ref, before{3});
    r::transform_view<decltype(ref), twice> doubled(ref, twice{});
    if (!same_base(take, values.data()) || !same_base(drop, values.data()) || !same_base(reverse, values.data()) ||
        !same_base(drop_while, values.data()) || !same_base(take_while, values.data()) ||
        !same_base(filter, values.data()) || !same_base(doubled, values.data()))
        return 6;
    const auto& rev = reverse;
    const auto& mapped = doubled;
    if (rev.size() != 3 || rev.begin().base() != values.end() || rev.end().base() != values.begin() ||
        reverse.size() != 3 || doubled.size() != 3 || mapped.size() != 3 || *mapped.begin() != 0 ||
        *(mapped.end() - 2) != 14 || *(drop_while.begin()) != 7 || *filter.begin() != 0 || !take_while.pred()(0) ||
        !drop_while.pred()(0) || filter.pred()(4))
        return 7;
    auto composed = r::views::drop(1) | r::views::take(1);
    auto one = ref | composed;
    if (one.size() != 1 || one.front() != 7)
        return 8;
    r::iota_view<int, int> seq(2, seed);
    auto it = seq.begin();
    if (*it++ != 2 || *(++it) != 4 || *it-- != 4 || *(--it) != 2 || it[2] != 4)
        return 9;
    it += 4;
    it -= 1;
    auto finish = seq.end();
    if (*it != 5 || finish - it != 2 || !(it < finish && it <= finish && finish >= it && finish > it))
        return 10;
    auto sub = r::subrange(values);
    const auto& cs = sub;
    if (r::get<0>(cs) != values.begin() || r::get<1>(static_cast<decltype(sub)&&>(sub)) != values.end() ||
        cs.next(2).front() != 2 || cs.next(2).prev().front() != 7)
        return 11;
    return 0;
}
}  // namespace asc_stl_test_ranges

#endif  // ASC_STL_TEST_RANGES_VIEWS_H
