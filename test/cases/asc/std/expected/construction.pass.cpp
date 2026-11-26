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

#include <asc/std/expected>
#include <asc/std/utility>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <utility>

struct explicit_int {
    int n;
    explicit explicit_int(int value) noexcept : n(value)
    {}
};
struct listed {
    int n;
    listed(std::initializer_list<int> values, int extra) noexcept : n(extra)
    {
        for (int i : values)
            n += i;
    }
};

template <class E>
bool observers(E&& value, E&& failure)
{
    using ref = std::conditional_t<std::is_lvalue_reference_v<E>, int&, int&&>;
    using cref = std::conditional_t<std::is_lvalue_reference_v<E>, const int&, const int&&>;
    using expected_ref = std::conditional_t<std::is_const_v<std::remove_reference_t<E>>, cref, ref>;
    static_assert(std::is_same_v<decltype(*static_cast<E&&>(value)), expected_ref>);
    static_assert(std::is_same_v<decltype(static_cast<E&&>(failure).error()), expected_ref>);
    return *static_cast<E&&>(value) == 4 && static_cast<E&&>(failure).error() == -3 &&
        static_cast<E&&>(value).value_or(19) == 4 && static_cast<E&&>(failure).value_or(19) == 19;
}

int main()
{
    using asc::std::expected;
    using asc::std::in_place;
    using asc::std::unexpect;
    using asc::std::unexpected;
    const unexpected<short> comparison_error(short{-7});
    if (!(comparison_error == unexpected<long>(-7L)) || comparison_error == unexpected<long>(7L))
        return 10;
    const std::string message("first");
    const unexpected<std::string> u(message);
    unexpected<std::string> copy_u(u), moved_u(std::move(copy_u)), assigned_u(in_place, 3, 'x');
    if (assigned_u.error() != "xxx" || moved_u.error() != message)
        return 7;
    assigned_u = u;
    copy_u = std::move(assigned_u);
    static_assert(std::is_same_v<decltype(std::move(u).error()), const std::string&&>);
    if (copy_u.error() != message || std::move(u).error() != message)
        return 8;
    const int input = 4;
    const int error = -3;
    const unexpected<int> tag(error);
    expected<int, int> a(input), b(tag);
    const expected<int, int> ca(a), cb(unexpect, error);
    if (!observers(a, b) || !observers(ca, cb) || !observers(std::move(a), std::move(b)) ||
        !observers(std::move(ca), std::move(cb)))
        return 1;

    const expected<short, short> narrow(7), invalid(unexpect, -2);
    expected<int, int> implicit = narrow;
    expected<int, int> moved_implicit(expected<short, short>(short{12}));
    expected<int, int> moved_error(expected<short, short>(unexpect, short{-7}));
    const unexpected<short> small_error(short{-4});
    expected<int, int> implicit_tag(small_error);
    if (!moved_implicit || *moved_implicit != 12 || moved_error.error() != -7 || implicit_tag.error() != -4)
        return 9;
    expected<explicit_int, explicit_int> copy_ok(narrow), copy_fail(invalid);
    expected<explicit_int, explicit_int> moved_ok(expected<short, short>{8}),
        moved_fail(expected<short, short>{unexpect, -5});
    if (*implicit != 7 || !copy_ok || copy_ok->n != 7 || copy_fail.error().n != -2 || moved_ok->n != 8 ||
        moved_fail.error().n != -5)
        return 2;
    expected<explicit_int, int> from_integer(6);
    const unexpected<short> short_tag(short{-11});
    expected<int, explicit_int> converted_tag(short_tag), moved_tag(unexpected<short>(short{-6}));
    if (from_integer->n != 6 || converted_tag.error().n != -11 || moved_tag.error().n != -6)
        return 3;

    expected<listed, listed> list_ok(in_place, {1, 2, 3}, 4), list_fail(unexpect, {1, 3}, -10);
    if (list_ok->n != 10 || list_fail.error().n != -6 || list_fail.emplace({3, 4}, 8).n != 15 || !list_fail.has_value())
        return 4;
    unexpected<listed> utag(in_place, {4, 5}, 1);
    if (utag.error().n != 10 || std::move(utag).error().n != 10)
        return 5;
    expected<int, int> assigned(a);
    assigned = std::move(b);
    assigned = unexpected<short>(short{-8});
    if (assigned || assigned.error() != -8)
        return 6;
    assigned = expected<int, int>{9};
    return !assigned || *assigned != 9;
}
