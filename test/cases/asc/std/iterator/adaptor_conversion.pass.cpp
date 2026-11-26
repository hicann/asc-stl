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

#include <asc/std/iterator>
#include <array>
#include <list>
#include <type_traits>

namespace s = asc::std;

struct named_sequence {
    int elements[2];
    const int* begin() const
    {
        return elements;
    }
    const int* end() const
    {
        return elements + 2;
    }
};

int main()
{
    const named_sequence view{{1, 2}};
    if (asc::std::begin(view) != view.elements || asc::std::end(view) != view.elements + 2)
        return 9;
    int raw[] = {2, -2, 3};
    using count = s::counted_iterator<int*>;
    using read_count = s::counted_iterator<const int*>;
    using common = s::common_iterator<count, s::default_sentinel_t>;
    using read_common = s::common_iterator<read_count, s::default_sentinel_t>;
    count none{};
    if (none.count() != 0 || static_cast<count&&>(none).base() != nullptr ||
        s::move_sentinel<int*>{}.base() != nullptr || s::reverse_iterator<int*>{}.base() != nullptr ||
        !(s::move_iterator<int*>{} == s::move_iterator<const int*>{}))
        return 1;
    using unbounded = s::common_iterator<int*, s::unreachable_sentinel_t>;
    unbounded initial{};
    if (initial != unbounded{static_cast<int*>(nullptr)} || initial == unbounded{s::unreachable_sentinel})
        return 8;
    common iter{count(raw, 3)}, bound(s::default_sentinel);
    read_common at(iter), copy{};
    copy = bound;
    if (copy != bound || *at != 2)
        return 2;
    copy = iter;
    at = read_common(s::default_sentinel);
    if (at - copy != 3 || *copy++ != 2 || *copy != -2)
        return 3;
    at = copy;
    if (at != copy || *at != -2)
        return 4;
    std::list<int> values{1};
    const int two = 2, four = 4;
    auto front = s::front_inserter(values);
    *front++ = two;
    *++front = -1;
    auto insert = s::inserter(values, ++values.begin());
    static_assert(std::is_same_v<decltype(insert++), decltype(insert)&>);
    *insert++ = four;
    *++insert = 3;
    auto back = s::back_inserter(values);
    const auto& proxy = back;
    if (&*proxy != &back)
        return 5;
    *++back = 6;
    *back++ = two;
    const std::list<int> expected{-1, 4, 3, 2, 1, 6, 2};
    if (values != expected)
        return 6;
    std::array<int, 3> a{{4, 2, -3}};
    const auto& ca = a;
    return *s::rbegin(a) == -3 && s::rend(a) - s::rbegin(a) == 3 && *s::rbegin(ca) == -3 &&
            s::rend(ca) - s::rbegin(ca) == 3 && s::data(ca) == a.data() ?
        0 :
        7;
}
