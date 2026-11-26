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

#include <asc/std/algorithm>
#include <asc/std/expected>
#include <asc/std/optional>
#include <asc/std/tuple>
#include <asc/std/utility>

#include <type_traits>
#include <utility>

namespace {

namespace ast = asc::std;

struct value {
    int left;
    int right;
    constexpr value(int a, int b) : left(a), right(b)
    {}
};
struct throwing_move {
    throwing_move() = default;
    throwing_move(const throwing_move&) = default;
    throwing_move(throwing_move&&) noexcept(false);
};
struct move_only {
    move_only() = default;
    move_only(const move_only&) = delete;
    move_only(move_only&&) noexcept(false);
};

static_assert(std::is_same_v<decltype(ast::move_if_noexcept(std::declval<throwing_move&>())), const throwing_move&>);
static_assert(std::is_same_v<decltype(ast::move_if_noexcept(std::declval<move_only&>())), move_only&&>);
static_assert(std::is_same_v<decltype(ast::move_if_noexcept(std::declval<int&>())), int&&>);
static_assert(std::is_trivially_destructible_v<ast::piecewise_construct_t>);
static_assert(std::is_same_v<decltype(ast::in_place_type<long>), const ast::in_place_type_t<long>>);
static_assert(std::is_same_v<decltype(ast::in_place_index<1>), const ast::in_place_index_t<1>>);
static_assert(std::is_constructible_v<ast::optional<int>, ast::in_place_t, int>);
static_assert(std::is_same_v<ast::optional<int>::value_type, int>);
static_assert(std::is_same_v<ast::expected<long, int>::value_type, long>);
static_assert(std::is_same_v<ast::expected<long, int>::error_type, int>);
static_assert(std::is_trivially_destructible_v<ast::unexpect_t>);

bool check_construction_tags()
{
    const ast::in_place_t in_place{};
    const ast::in_place_type_t<int> by_type{};
    const ast::in_place_index_t<0> by_index{};
    const ast::unexpect_t unexpect{};
    const ast::nullopt_t none = ast::nullopt;
    const ast::piecewise_construct_t piecewise{};
    const ast::optional<int> empty(none);
    const ast::optional<int> some(in_place, 29);
    const ast::expected<long, int> expected(ast::in_place, 41);
    const ast::expected<long, int> error(unexpect, 7);
    const ast::pair<value, value> combined(piecewise, ast::tuple<int, int>(3, 4), ast::tuple<int, int>(5, 6));
    static_assert(std::is_same_v<decltype(by_type), const ast::in_place_type_t<int>>);
    static_assert(std::is_same_v<decltype(by_index), const ast::in_place_index_t<0>>);
    int word = 19;
    const ast::optional<int&> borrowed(word);
    const ast::optional<int&> no_reference;
    return !empty && some && *some == 29 && expected && *expected == 41 && !error && error.error() == 7 &&
        combined.first.left == 3 && combined.first.right == 4 && combined.second.left == 5 &&
        combined.second.right == 6 && borrowed && !no_reference && &*borrowed == &word;
}

bool check_pairs()
{
    auto x = ast::make_pair(1, 5L);
    auto y = ast::make_pair(2, 3L);
    static_assert(std::is_same_v<decltype(x)::first_type, int>);
    static_assert(std::is_same_v<decltype(x)::second_type, long>);
    if (!(x < y) || x == y) {
        return false;
    }
    y.swap(x);
    if (x.first != 2 || x.second != 3 || y.first != 1 || y.second != 5) {
        return false;
    }
    x = y;
    return x == y && !(x < y);
}

bool check_tuples()
{
    using pair = ast::tuple<int, long>;
    static_assert(std::is_same_v<ast::tuple_element<1, pair>::type, long>);
    pair first(2, 8L);
    pair second(2, 10L);
    if (!(first != second && first < second && first <= second && second > first && second >= first) ||
        first == second || second < first) {
        return false;
    }
    first.swap(second);
    if (ast::get<1>(first) != 10 || ast::get<1>(second) != 8) {
        return false;
    }
    second = first;
    if (!(first == second && first <= second && first >= second) || first != second) {
        return false;
    }
    const auto empty = ast::tuple_cat();
    static_assert(ast::tuple_size<decltype(empty)>::value == 0);
    const auto combined = ast::tuple_cat(empty, second, ast::tuple<char>('z'), ast::tuple<>());
    static_assert(ast::tuple_size<decltype(combined)>::value == 3);
    return ast::get<0>(combined) == 2 && ast::get<1>(combined) == 10 && ast::get<2>(combined) == 'z';
}

struct sum {
    int value = 0;
    void operator()(int x)
    {
        value += x;
    }
};
static_assert(std::is_same_v<ast::ranges::for_each_result<int*, sum>, ast::ranges::in_fun_result<int*, sum>>);
static_assert(std::is_same_v<ast::ranges::for_each_n_result<int*, sum>, ast::ranges::in_fun_result<int*, sum>>);

bool check_result_positions()
{
    int input[] = {2, -3, 11};
    for (int count = 0; count <= 3; ++count) {
        const auto first = ast::ranges::for_each(input, input + count, sum{});
        const auto second = ast::ranges::for_each_n(input, count, sum{});
        int expected = 0;
        for (int i = 0; i < count; ++i) {
            expected += input[i];
        }
        if (first.in != input + count || second.in != input + count || first.fun.value != expected ||
            second.fun.value != expected) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main()
{
    return check_construction_tags() && check_pairs() && check_tuples() && check_result_positions() ? 0 : 1;
}
