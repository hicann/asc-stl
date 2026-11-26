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

#include <asc/std/array>
#include <asc/std/ranges>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace {

namespace ast = asc::std;
namespace rg = ast::ranges;
namespace views = rg::views;
using array = ast::array<int, 5>;
using reference_view = rg::ref_view<array>;

static_assert(rg::range<array> && rg::input_range<array> && rg::output_range<array, int>);
static_assert(!rg::output_range<const array, int> && !rg::range<int>);
static_assert(rg::forward_range<array> && rg::bidirectional_range<array> && rg::contiguous_range<array>);
static_assert(rg::common_range<array> && rg::sized_range<array>);
static_assert(rg::view<reference_view> && !rg::view<array>);
static_assert(rg::borrowed_range<reference_view> && !rg::borrowed_range<array> && rg::borrowed_range<array&>);
static_assert(rg::enable_borrowed_range<reference_view> && !rg::enable_borrowed_range<array>);
static_assert(!rg::disable_sized_range<array>);
static_assert(std::is_same_v<rg::borrowed_iterator_t<array>, rg::dangling>);
static_assert(std::is_same_v<rg::borrowed_iterator_t<array&>, int*>);
static_assert(std::is_constructible_v<rg::dangling, int*> && std::is_default_constructible_v<rg::dangling>);
static_assert(std::is_same_v<rg::range_common_reference_t<array>, int&>);
static_assert(std::is_same_v<rg::range_difference_t<array>, std::ptrdiff_t>);
static_assert(std::is_same_v<rg::range_reference_t<const array>, const int&>);
static_assert(std::is_same_v<rg::range_rvalue_reference_t<array>, int&&>);
static_assert(std::is_same_v<rg::range_size_t<array>, ast::size_t>);
static_assert(std::is_same_v<rg::range_value_t<const array>, int>);
static_assert(std::is_same_v<rg::sentinel_t<const array>, const int*>);
static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::from_range)>, ast::from_range_t>);
static_assert(std::is_enum_v<rg::subrange_kind>);

struct end_sentinel {
    int* last;
    friend constexpr bool operator==(int* cursor, end_sentinel end) noexcept
    {
        return cursor == end.last;
    }
    friend constexpr bool operator==(end_sentinel end, int* cursor) noexcept
    {
        return cursor == end;
    }
    friend constexpr bool operator!=(int* cursor, end_sentinel end) noexcept
    {
        return !(cursor == end);
    }
    friend constexpr bool operator!=(end_sentinel end, int* cursor) noexcept
    {
        return !(end == cursor);
    }
};

struct span_view : rg::view_interface<span_view> {
    int* first = nullptr;
    int* last = nullptr;
    constexpr span_view() = default;
    constexpr span_view(int* begin, int* end) : first(begin), last(end)
    {}
    constexpr int* begin() const noexcept
    {
        return first;
    }
    constexpr int* end() const noexcept
    {
        return last;
    }
};

struct non_common_view : rg::view_interface<non_common_view> {
    int* first = nullptr;
    int* last = nullptr;
    constexpr non_common_view() = default;
    constexpr non_common_view(int* begin, int* end) : first(begin), last(end)
    {}
    constexpr int* begin() const noexcept
    {
        return first;
    }
    constexpr end_sentinel end() const noexcept
    {
        return {last};
    }
    constexpr std::size_t size() const noexcept
    {
        return static_cast<std::size_t>(last - first);
    }
};
static_assert(rg::sized_range<non_common_view> && !rg::common_range<non_common_view>);
static_assert(!rg::contiguous_range<rg::reverse_view<span_view>>);

struct below {
    int upper;
    constexpr bool operator()(int value) const noexcept
    {
        return value < upper;
    }
};
struct twice {
    constexpr int operator()(int value) const noexcept
    {
        return value * 2;
    }
};
struct odd {
    constexpr bool operator()(int value) const noexcept
    {
        return value % 2 != 0;
    }
};
struct first_two : rg::range_adaptor_closure<first_two> {
    template <class R>
    auto operator()(R&& value) const
    {
        return views::take(std::forward<R>(value), 2);
    }
};

bool check_access_and_lifetimes()
{
    array source{{1, 2, 3, 4, 5}};
    const array& constant = source;
    if (rg::cbegin(source) != constant.begin() || rg::cend(source) != constant.end() ||
        rg::cdata(source) != constant.data() || *rg::crbegin(source) != 5 ||
        rg::crend(source) - rg::crbegin(source) != 5) {
        return false;
    }
    reference_view reference(source);
    if (&reference.base() != &source || reference.begin() != source.begin() || reference.end() != source.end() ||
        reference.empty() || reference.size() != 5 || reference.data() != source.data()) {
        return false;
    }
    reference.data()[1] = 9;
    if (source[1] != 9) {
        return false;
    }
    rg::owning_view<array> owner(array{{7, 8, 9, 10, 11}});
    if (owner.empty() || owner.size() != 5 || owner.data() != owner.base().data() || *owner.begin() != 7 ||
        owner.end() - owner.begin() != 5) {
        return false;
    }
    owner = rg::owning_view<array>(array{{0, -1, -2, -3, -4}});
    if (*owner.begin() != 0 || owner.base()[4] != -4 || source[1] != 9) {
        return false;
    }
    const rg::empty_view<int> empty{};
    const rg::single_view<int> single{19};
    return empty.empty() && empty.data() == nullptr && views::empty<int>.empty() && single.size() == 1 &&
        single.data() == single.begin() && single.end() - single.begin() == 1 && *single.begin() == 19;
}

bool check_common_and_interface()
{
    int data[] = {5, 7, 9};
    const non_common_view source(data, data + 3);
    rg::common_view<non_common_view> common(source);
    if (!rg::common_range<decltype(common)> || common.base().begin() != data || common.size() != 3) {
        return false;
    }
    auto it = common.begin();
    if (*it++ != 5 || *it++ != 7 || *it++ != 9 || it != common.end()) {
        return false;
    }
    const auto interval = rg::subrange<int*, int*, rg::subrange_kind::sized>(data, data + 3);
    if (interval.end() != data + 3) {
        return false;
    }
    const span_view populated(data, data + 3);
    const span_view empty(data, data);
    return !populated.empty() && populated.data() == data && populated.size() == 3 && populated.front() == 5 &&
        populated.back() == 9 && populated[1] == 7 && empty.empty() && empty.size() == 0;
}

bool check_slices()
{
    array input{{1, 2, 3, 4, 5}};
    reference_view reference(input);
    const int counts[] = {0, 1, 4, 5, 8};
    for (int count : counts) {
        const int limited = count < 5 ? count : 5;
        rg::take_view<reference_view> prefix(reference, count);
        rg::drop_view<reference_view> suffix(reference, count);
        if (prefix.size() != static_cast<unsigned>(limited) || suffix.size() != static_cast<unsigned>(5 - limited) ||
            prefix.base().data() != input.data() || suffix.base().data() != input.data() ||
            prefix.begin() != input.begin() || prefix.end() != input.begin() + limited ||
            suffix.begin() != input.begin() + limited || suffix.end() != input.end()) {
            return false;
        }
    }
    rg::reverse_view<reference_view> reversed(reference);
    if (reversed.size() != 5 || reversed.base().begin() != input.begin() || *reversed.begin() != 5 ||
        reversed.end() - reversed.begin() != 5 || reversed.begin()[4] != 1) {
        return false;
    }
    auto pipeline = reference | views::reverse | first_two{};
    auto item = pipeline.begin();
    return *item++ == 5 && *item++ == 4 && item == pipeline.end();
}

bool check_predicates()
{
    array input{{1, 2, 3, 4, 5}};
    reference_view reference(input);
    for (int limit = 0; limit <= 6; ++limit) {
        const int expected = limit < 1 ? 0 : limit - 1;
        rg::take_while_view<reference_view, below> take(reference, below{limit});
        rg::drop_while_view<reference_view, below> drop(reference, below{limit});
        if (take.base().begin() != input.begin() || drop.base().begin() != input.begin() ||
            take.pred().upper != limit || drop.pred().upper != limit || drop.begin() != input.begin() + expected ||
            drop.end() != input.end()) {
            return false;
        }
        int count = 0;
        for (int item : take) {
            if (item != ++count) {
                return false;
            }
        }
        if (count != expected) {
            return false;
        }
    }

    rg::filter_view<reference_view, odd> selected(reference, odd{});
    if (!selected.pred()(3) || selected.pred()(2) || selected.base().data() != input.data()) {
        return false;
    }
    auto i = selected.begin();
    if (*i != 1 || *++i != 3 || *++i != 5 || ++i != selected.end()) {
        return false;
    }
    rg::transform_view<reference_view, twice> mapped(reference, twice{});
    if (mapped.base().begin() != input.begin() || mapped.size() != 5 || mapped.end() - mapped.begin() != 5 ||
        mapped.begin()[4] != 10) {
        return false;
    }
    input[0] = -3;
    return *mapped.begin() == -6;
}

}  // namespace

int main()
{
    if (!check_access_and_lifetimes()) {
        return 1;
    }
    if (!check_common_and_interface()) {
        return 2;
    }
    if (!check_slices()) {
        return 3;
    }
    return check_predicates() ? 0 : 4;
}
