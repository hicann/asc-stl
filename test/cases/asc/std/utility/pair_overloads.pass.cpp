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

#include <asc/std/utility>
#include <asc/std/tuple>
#include <asc/std/variant>
#include <type_traits>
#include <utility>

struct explicit_int {
    int value;
    explicit explicit_int(int v = 3) : value(v)
    {}
};

template <class P>
bool elements(P&& value)
{
    using Storage = std::remove_reference_t<P>;
    using F = std::conditional_t<std::is_const_v<Storage>, const int, int>;
    using S = std::conditional_t<std::is_const_v<Storage>, const short, short>;
    using Fr = std::conditional_t<std::is_lvalue_reference_v<P>, F&, F&&>;
    using Sr = std::conditional_t<std::is_lvalue_reference_v<P>, S&, S&&>;
    static_assert(std::is_same_v<decltype(asc::std::get<0>(std::forward<P>(value))), Fr>);
    static_assert(std::is_same_v<decltype(asc::std::get<short>(std::forward<P>(value))), Sr>);
    return asc::std::get<int>(std::forward<P>(value)) == 8 && asc::std::get<short>(std::forward<P>(value)) == -2 &&
        asc::std::get<0>(std::forward<P>(value)) == 8 && asc::std::get<1>(std::forward<P>(value)) == -2;
}

struct movable {
    int value;
    explicit movable(int n = 0) : value(n)
    {}
    movable(const movable& rhs) : value(rhs.value)
    {}
    movable(movable&& rhs) noexcept : value(std::exchange(rhs.value, -1))
    {}
    movable& operator=(const movable& rhs)
    {
        value = rhs.value;
        return *this;
    }
    movable& operator=(movable&& rhs) noexcept
    {
        value = std::exchange(rhs.value, -1);
        return *this;
    }
};

bool sequence_and_value_categories()
{
    using seq = asc::std::integer_sequence<int, -2, 0, 7>;
    using asc::std::monostate;
    using pair_type = asc::std::pair<long, short>;
    static_assert(asc::std::tuple_size<seq>::value == 3 && asc::std::tuple_size<pair_type>::value == 2);
    static_assert(std::is_same_v<asc::std::tuple_element_t<0, seq>, int>);
    static_assert(std::is_same_v<asc::std::tuple_element_t<2, const seq>, int>);
    static_assert(std::is_same_v<asc::std::tuple_element_t<0, pair_type>, long> &&
        std::is_same_v<asc::std::tuple_element_t<1, pair_type>, short>);
    static_assert(std::is_same_v<decltype(asc::std::declval<const int&>()), const int&>);
    static_assert(std::is_same_v<decltype(asc::std::forward<int>(42)), int&&>);
    static_assert(std::is_empty_v<asc::std::in_place_t> && std::is_empty_v<asc::std::in_place_type_t<int>> &&
        std::is_empty_v<asc::std::in_place_index_t<0>> && std::is_empty_v<asc::std::piecewise_construct_t>);
    constexpr asc::std::in_place_t tag{};
    constexpr asc::std::in_place_type_t<int> type_tag{};
    constexpr asc::std::in_place_index_t<0> index_tag{};
    static_assert(std::is_same_v<decltype(tag), decltype(asc::std::in_place)>);
    static_assert(std::is_same_v<decltype(type_tag), decltype(asc::std::in_place_type<int>)>);
    static_assert(std::is_same_v<decltype(index_tag), decltype(asc::std::in_place_index<0>)>);
    const monostate a{}, b{};
    const seq values{};
    return seq::size() == 3 && asc::std::index_sequence<>::size() == 0 && asc::std::get<0>(values) == -2 &&
        asc::std::get<1>(values) == 0 && asc::std::get<2>(values) == 7 && a == b && !(a != b) && !(a < b) && !(a > b) &&
        a <= b && a >= b && asc::std::forward<int>(42) == 42;
}

bool pair_special_members()
{
    using pair = asc::std::pair<movable, movable>;
    pair source(movable{3}, movable{7});
    const pair& readonly = source;
    pair copied(readonly);
    pair moved(std::move(source));
    pair assigned, transferred;
    assigned = copied;
    transferred = std::move(copied);
    return source.first.value == -1 && copied.second.value == -1 && moved.first.value == 3 &&
        assigned.first.value == 3 && transferred.second.value == 7;
}

int main()
{
    if (!sequence_and_value_categories() || !pair_special_members())
        return 6;
    using asc::std::pair;
    const pair<int, short> zero = {};
    if (zero.first != 0 || zero.second != 0)
        return 7;
    pair<int, short> a(8, short{-2});
    const auto ca = a;
    if (!asc::std::rel_ops::operator!=(a, zero) || asc::std::rel_ops::operator!=(a, ca))
        return 8;
    if (!elements(a) || !elements(ca) || !elements(std::move(a)) || !elements(std::move(ca)))
        return 1;
    pair<long, int> b(a), c(ca), d(std::move(a)), e(std::move(ca));
    if (b.first != 8 || c.second != -2 || d.second != -2 || e.first != 8)
        return 2;
    pair<explicit_int, explicit_int> explicit_values(4, 7), defaults;
    if (explicit_values.second.value != 7 || defaults.first.value != 3)
        return 3;
    int first = 0, second = 0;
    const pair<int&, int&> refs(first, second);
    refs = b;
    if (first != 8 || second != -2)
        return 4;
    refs = pair<short, short>(short{-9}, short{6});
    if (first != -9 || second != 6)
        return 5;
    auto t = asc::std::make_tuple(7, 8);
    pair<int, int> from_tuple(t);
    from_tuple = asc::std::make_tuple(1, 2);
    b = ca;
    b = pair<int, short>(0, short{3});
    return from_tuple.first != 1 || from_tuple.second != 2 || b.first != 0 || b.second != 3;
}
