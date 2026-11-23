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

#ifndef ASC_STL_TEST_FUNCTIONAL_OBJECTS_H
#define ASC_STL_TEST_FUNCTIONAL_OBJECTS_H

#include <asc/functional>
#include <asc/std/type_traits>
#include <asc/std/utility>

namespace asc_stl_functional_objects {
struct explicit_bool {
    bool value;
    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return value;
    }
};
struct box {
    int value;
    CANN_ASC_STL_API friend constexpr explicit_bool operator<(const box& left, const box& right) noexcept
    {
        return {left.value < right.value};
    }
    CANN_ASC_STL_API friend constexpr explicit_bool operator==(int left, const box& right) noexcept
    {
        return {left == right.value};
    }
};
struct move_only {
    int value;
    CANN_ASC_STL_API explicit constexpr move_only(int input) noexcept : value(input)
    {}
    move_only(const move_only&) = delete;
    move_only& operator=(const move_only&) = delete;
    CANN_ASC_STL_API constexpr move_only(move_only&& other) noexcept : value(other.value)
    {
        other.value = -1;
    }
    CANN_ASC_STL_API friend constexpr bool operator<(const move_only& left, const move_only& right) noexcept
    {
        return left.value < right.value;
    }
    CANN_ASC_STL_API friend constexpr bool operator==(int left, const move_only& right) noexcept
    {
        return left == right.value;
    }
};
struct no_comparison {};
struct right_only_comparison {
    CANN_ASC_STL_API friend bool operator<(right_only_comparison&&, right_only_comparison&&) noexcept;
};
struct incomplete;
struct maybe_throwing_bool {
    CANN_ASC_STL_API explicit operator bool() const noexcept(false);
};
struct maybe_throwing_comparison {
    CANN_ASC_STL_API friend maybe_throwing_bool operator<(
        const maybe_throwing_comparison&, const maybe_throwing_comparison&) noexcept;
    CANN_ASC_STL_API friend maybe_throwing_bool operator==(int, const maybe_throwing_comparison&) noexcept;
};
struct maybe_throwing_copy {
    CANN_ASC_STL_API maybe_throwing_copy() noexcept = default;
    CANN_ASC_STL_API maybe_throwing_copy(const maybe_throwing_copy&) noexcept(false);
    CANN_ASC_STL_API maybe_throwing_copy(maybe_throwing_copy&&) noexcept;
    CANN_ASC_STL_API friend bool operator<(const maybe_throwing_copy&, const maybe_throwing_copy&) noexcept;
};
struct maybe_throwing_destructor {
    CANN_ASC_STL_API ~maybe_throwing_destructor() noexcept(false);
    CANN_ASC_STL_API explicit operator bool() const noexcept;
};
struct destructor_comparison {
    CANN_ASC_STL_API friend maybe_throwing_destructor operator<(
        const destructor_comparison&, const destructor_comparison&) noexcept;
};

CANN_ASC_STL_API constexpr bool constraints()
{
    using asc::std::is_invocable_v;
    static_assert(!is_invocable_v<asc::maximum<>, no_comparison, no_comparison>);
    static_assert(!is_invocable_v<asc::minimum<no_comparison>, no_comparison, no_comparison>);
    static_assert(!is_invocable_v<asc::maximum<>, right_only_comparison, right_only_comparison>);
    static_assert(!is_invocable_v<asc::maximum<>, incomplete&, incomplete&>);
    static_assert(!is_invocable_v<asc::maximum<>, int(&)[2], int(&)[2]>);
    static_assert(!is_invocable_v<asc::maximum<>, volatile int&, int&>);
    static_assert(!is_invocable_v<asc::maximum<>, move_only&, move_only&>);
    static_assert(!is_invocable_v<asc::maximum<>, const move_only&, move_only&&>);
    static_assert(!is_invocable_v<asc::maximum<move_only>, move_only, move_only>);
    static_assert(is_invocable_v<asc::maximum<>, move_only, move_only>);
    static_assert(!asc::std::is_default_constructible_v<asc::equal_to_value<int>>);
    static_assert(!asc::std::is_copy_constructible_v<asc::equal_to_value<move_only>>);
    static_assert(asc::std::is_move_constructible_v<asc::equal_to_value<move_only>>);
    static_assert(is_invocable_v<const asc::equal_to_value<box>&, int>);
    static_assert(!is_invocable_v<const asc::equal_to_value<box>&, no_comparison>);
    return true;
}

CANN_ASC_STL_API constexpr bool exception_specifications()
{
    using asc::std::declval;
    static_assert(noexcept(asc::maximum<int>{}(1, 2)));
    static_assert(noexcept(asc::minimum<>{}(1, 2L)));
    static_assert(
        !noexcept(asc::maximum<>{}(declval<maybe_throwing_comparison>(), declval<maybe_throwing_comparison>())));
    static_assert(!noexcept(asc::minimum<maybe_throwing_copy>{}(
        declval<const maybe_throwing_copy&>(), declval<const maybe_throwing_copy&>())));
    static_assert(noexcept(asc::maximum<>{}(declval<maybe_throwing_copy>(), declval<maybe_throwing_copy>())));
    static_assert(!noexcept(asc::maximum<>{}(declval<destructor_comparison>(), declval<destructor_comparison>())));
    static_assert(!noexcept(declval<const asc::equal_to_value<maybe_throwing_comparison>&>()(1)));
    static_assert(!noexcept(asc::equal_to_value<maybe_throwing_copy>(declval<const maybe_throwing_copy&>())));
    static_assert(noexcept(asc::equal_to_value<maybe_throwing_copy>(declval<maybe_throwing_copy>())));
    static_assert(noexcept(asc::always_true{}()) && noexcept(asc::always_false{}(1, 2)));
    return true;
}

CANN_ASC_STL_API constexpr bool values()
{
    static_assert(asc::std::is_same_v<decltype(asc::maximum<>{}(1, 2L)), long>);
    static_assert(
        asc::std::is_same_v<decltype(asc::minimum<>{}(asc::std::declval<int&>(), asc::std::declval<int&>())), int>);
    static_assert(asc::std::is_same_v<typename asc::maximum<>::is_transparent, void>);
    static_assert(asc::std::is_same_v<typename asc::minimum<>::is_transparent, void>);
    static_assert(asc::std::is_same_v<decltype(asc::maximum<>{}(box{1}, box{2})), box>);
    static_assert(asc::maximum<>{}(box{1}, box{2}).value == 2);
    static_assert(asc::minimum<>{}(box{1}, box{2}).value == 1);
    constexpr auto equal = asc::equal_to_value{7};
    constexpr auto copied = asc::equal_to_value{equal};
    static_assert(asc::std::is_same_v<asc::std::remove_cv_t<decltype(copied)>, asc::equal_to_value<int>>);
    static_assert(copied(7L) && !copied(8L));
    static_assert(asc::equal_to_value<box>{box{7}}(7));
    static_assert(asc::always_true{}() && asc::always_true{}(1, box{2}));
    static_assert(!asc::always_false{}() && !asc::always_false{}(box{2}, 3));
    return true;
}

struct counted {
    int key;
    int identity;
    int* events;
    CANN_ASC_STL_API constexpr counted(int value, int id, int* state) noexcept : key(value), identity(id), events(state)
    {}
    CANN_ASC_STL_API constexpr counted(const counted& other) noexcept
        : key(other.key), identity(other.identity), events(other.events)
    {
        ++events[0];
    }
    CANN_ASC_STL_API constexpr counted(counted&& other) noexcept
        : key(other.key), identity(other.identity), events(other.events)
    {
        ++events[1];
        other.key = -1;
    }
    CANN_ASC_STL_API friend constexpr bool operator<(const counted& left, const counted& right) noexcept
    {
        ++left.events[2];
        return left.key < right.key;
    }
};

CANN_ASC_STL_API constexpr bool selection(unsigned input)
{
    int events[3] = {};
    counted left(static_cast<int>(input % 100), 1, events);
    counted right(left.key, 2, events);
    const auto tied = asc::maximum<>{}(left, right);
    if (tied.identity != 1 || &tied == &left || events[0] != 1 || events[1] != 0 || events[2] != 1)
        return false;
    right.key = left.key + 1;
    // NOLINTNEXTLINE(build/include_what_you_use)
    const auto moved = asc::maximum<>{}(asc::std::move(left), asc::std::move(right));
    if (moved.identity != 2 || right.key != -1 || left.key < 0 || events[1] != 1 || events[2] != 2)
        return false;
    const auto minimum = asc::minimum<counted>{}(left, moved);
    if (minimum.identity != 1 || events[0] != 2 || events[2] != 3)
        return false;
    const auto owned = asc::maximum<>{}(move_only{3}, move_only{9});
    const auto predicate = asc::equal_to_value{move_only{9}};
    int evaluated = 0;
    const bool ignored = asc::always_true{}(++evaluated);
    const bool ignored_false = asc::always_false{}(++evaluated, input);
    return owned.value == 9 && predicate(9) && !predicate(3) && ignored && !ignored_false && evaluated == 2;
}

CANN_ASC_STL_API constexpr bool matches_float_bits(float value, unsigned expected) noexcept
{
    const unsigned actual = __builtin_bit_cast(unsigned, value);
    if ((expected & 0x7fffffffU) > 0x7f800000U) {
        return (actual & 0x7fffffffU) > 0x7f800000U;
    }
    return actual == expected;
}

CANN_ASC_STL_API constexpr bool floating_selection(unsigned input)
{
    static_assert(sizeof(float) == sizeof(unsigned));
    // Left, right, expected maximum, expected minimum. NaNs are compared by class, not payload.
    const unsigned cases[6][4] = {{0x80000000U, 0U, 0x80000000U, 0x80000000U}, {0U, 0x80000000U, 0U, 0U},
        {0x7fc00001U, 0x40400000U, 0x7fc00001U, 0x7fc00001U}, {0x40400000U, 0x7fc00001U, 0x40400000U, 0x40400000U},
        {0x40400000U, 0x40e00000U, 0x40e00000U, 0x40400000U}, {0x40e00000U, 0x40400000U, 0x40e00000U, 0x40400000U}};
    for (unsigned offset = 0; offset < 6; ++offset) {
        const unsigned index = (input % 6U + offset) % 6U;
        const float left = __builtin_bit_cast(float, cases[index][0]);
        const float right = __builtin_bit_cast(float, cases[index][1]);
        if (!matches_float_bits(asc::maximum<>{}(left, right), cases[index][2]) ||
            !matches_float_bits(asc::maximum<float>{}(left, right), cases[index][2]) ||
            !matches_float_bits(asc::minimum<>{}(left, right), cases[index][3]) ||
            !matches_float_bits(asc::minimum<float>{}(left, right), cases[index][3])) {
            return false;
        }
    }
    return true;
}

CANN_ASC_STL_API constexpr bool evaluate(unsigned input)
{
    return constraints() && exception_specifications() && values() && selection(input) && floating_selection(input);
}
}  // namespace asc_stl_functional_objects

#endif  // ASC_STL_TEST_FUNCTIONAL_OBJECTS_H
