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
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>
#include <list>

namespace r = asc::std::ranges;
namespace s = asc::std;

namespace cpo_test {

extern int unknown_bound[];

using unbounded_array = int[];

bool check_unknown_bound(unbounded_array& input)
{
    int* first = r::begin(input);
    return first == unknown_bound && first[0] == 7 && first[2] == -6;
}

bool check_extern_array()
{
    return check_unknown_bound(unknown_bound);
}

int unknown_bound[] = {7, 2, -6};

struct borrowed {
    int* first;
    int* last;

    const int* begin() const
    {
        return first;
    }
    const int* end() const
    {
        return last;
    }
    const int* data() const
    {
        return first;
    }
    auto rbegin() const
    {
        return s::make_reverse_iterator(last);
    }
    auto rend() const
    {
        return s::make_reverse_iterator(first);
    }
};

struct adl_reverse {
    int* first;
    int* last;
    int calls = 0;

    friend auto rbegin(adl_reverse& range)
    {
        ++range.calls;
        return s::make_reverse_iterator(range.last);
    }
    friend auto rend(adl_reverse& range)
    {
        ++range.calls;
        return s::make_reverse_iterator(range.first);
    }
};

template <class I>
struct endpoints {
    I first;
    I last;
    I begin() const
    {
        return first;
    }
    I end() const
    {
        return last;
    }
};

}  // namespace cpo_test

namespace asc::std::ranges {
template <>
inline constexpr bool enable_borrowed_range<cpo_test::borrowed> = true;
}  // namespace asc::std::ranges

namespace cpo_test {

int access_overloads()
{
    int values[] = {11, -5, 23, 8};
    int* first = values + 1;
    int* last = values + 3;
    const auto begin = r::cbegin(borrowed{first, last});
    const auto end = r::cend(borrowed{first, last});
    const auto data = r::cdata(borrowed{first, last});
    static_assert(s::is_same_v<decltype(begin), const int* const>);
    if (begin != first || end != last || data != first || *begin != -5 || end[-1] != 23)
        return 1;
    const auto reversed_first = r::crbegin(borrowed{first, last});
    const auto reversed_last = r::crend(borrowed{first, last});
    if (reversed_first.base() != last || reversed_last.base() != first || *reversed_first != 23 ||
        r::rend(borrowed{first, first}).base() != first)
        return 2;
    adl_reverse adl{first, last};
    auto it = r::rbegin(adl);
    const auto sentinel = r::rend(adl);
    if (adl.calls != 2 || it == sentinel || *it++ != 23 || *it++ != -5 || it != sentinel)
        return 3;
    endpoints<int*> sized{first, last};
    static_assert(s::is_unsigned_v<decltype(r::size(sized))>);
    if (r::size(s::move(values)) != 4 || r::size(sized) != 2)
        return 4;
    sized.last = first;
    if (r::size(sized) != 0)
        return 5;
    return 0;
}

int view_overloads()
{
    volatile int start = -2;
    const auto whole = r::views::iota(static_cast<int>(start));
    auto i = whole.begin();
    for (int expected = -2; expected != 3; ++expected, ++i)
        if (i == whole.end() || *i != expected)
            return 6;
    std::list<int> list{11, -5, 23};
    using iterator = decltype(list.begin());
    endpoints<iterator> non_sized{list.begin(), list.end()};
    if (r::empty(non_sized))
        return 7;
    non_sized.first = list.end();
    if (!r::empty(non_sized))
        return 8;
    using reverse = s::reverse_iterator<iterator>;
    using sized = r::subrange<reverse, reverse, r::subrange_kind::sized>;
    using unsized = r::subrange<reverse, reverse, r::subrange_kind::unsized>;
    const reverse begin(list.end());
    const reverse end(list.begin());
    const auto with_size = r::views::reverse(sized(begin, end, 3));
    const auto without_size = r::views::reverse(unsized(begin, end));
    static_assert(s::is_same_v<decltype(with_size), const r::subrange<iterator, iterator, r::subrange_kind::sized>>);
    static_assert(
        s::is_same_v<decltype(without_size), const r::subrange<iterator, iterator, r::subrange_kind::unsized>>);
    if (with_size.size() != 3 || with_size.begin() != list.begin() || with_size.end() != list.end() ||
        without_size.begin() != list.begin() || without_size.end() != list.end())
        return 9;
    *without_size.begin() = -17;
    return *with_size.begin() == -17 && list.front() == -17 ? 0 : 10;
}

}  // namespace cpo_test

int main()
{
    if (!cpo_test::check_extern_array())
        return 11;
    if (int result = cpo_test::access_overloads())
        return result;
    return cpo_test::view_overloads();
}
