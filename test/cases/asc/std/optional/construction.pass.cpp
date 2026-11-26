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

#include <asc/std/optional>
#include <initializer_list>
#include <type_traits>
#include <utility>

struct box {
    int n;
    explicit box(int value) noexcept : n(value)
    {}
    box(std::initializer_list<int> items, int offset) noexcept : n(offset)
    {
        for (int i : items)
            n += i;
    }
};

template <class O>
bool observer(O&& value)
{
    using ref = std::conditional_t<std::is_const_v<std::remove_reference_t<O>>, const int, int>;
    using expected = std::conditional_t<std::is_lvalue_reference_v<O>, ref&, ref&&>;
    static_assert(std::is_same_v<decltype(*std::forward<O>(value)), expected>);
    return *std::forward<O>(value) == 8 && std::forward<O>(value).value_or(0) == 8;
}

int main()
{
    using asc::std::optional;
    const optional<short> empty, source(short{5});
    optional<box> implicit_value(9), copied(source), moved(optional<short>{short{6}}), absent(empty),
        absent_move(optional<short>{}), listed(asc::std::in_place, {1, 2, 3}, 10);
    if (implicit_value->n != 9 || copied->n != 5 || moved->n != 6 || absent || absent_move || listed->n != 16)
        return 1;
    if (listed.emplace({3, 4}, -1).n != 6 || !listed)
        return 2;
    auto constructed = asc::std::make_optional<box>(13);
    const auto constructed_list = asc::std::make_optional<box>({2, 4}, -3);
    optional<box> empty_box(asc::std::nullopt);
    optional<box> transfer(std::move(constructed));
    empty_box = std::move(transfer);
    if (!empty_box || empty_box->n != 13 || constructed_list->n != 3)
        return 5;
    int x = 1;
    optional<int&> borrowed, xref(x);
    if (borrowed.has_value())
        return 11;
    optional<int&> alias(xref);
    borrowed = alias;
    if (&*borrowed != &x || &*alias != &x)
        return 6;
    *alias = 4;
    borrowed = asc::std::nullopt;
    if (borrowed || !xref || *xref != 4)
        return 7;
    static_assert(!std::is_default_constructible_v<asc::std::nullopt_t>);
    const asc::std::nullopt_t sentinel = asc::std::nullopt;
    optional<int> assign(sentinel);
    assign = 5;
    if (!assign || *assign != 5)
        return 8;
    assign = 7;
    if (!assign || *assign != 7)
        return 9;
    optional<int> engaged(8);
    const optional<int> constant(8);
    if (!observer(engaged) || !observer(constant) || !observer(std::move(engaged)) || !observer(std::move(constant)))
        return 3;
    optional<int> converted = optional<short>(short{9});
    converted = optional<short>{};
    if (converted)
        return 4;
    converted = optional<short>(short{11});
    return !converted || *converted != 11;
}
