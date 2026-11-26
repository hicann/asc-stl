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

#include <asc/std/compare>
#include <type_traits>

#include "../../compare/support/comparison_helpers_semantics.h"

namespace {

using partial = asc::std::partial_ordering;
using weak = asc::std::weak_ordering;
using strong = asc::std::strong_ordering;
using predicate = bool (*)(partial) noexcept;

static_assert(std::is_same_v<decltype(&asc::std::is_eq), predicate>);
static_assert(std::is_same_v<decltype(&asc::std::is_neq), predicate>);
static_assert(std::is_same_v<decltype(&asc::std::is_lt), predicate>);
static_assert(std::is_same_v<decltype(&asc::std::is_lteq), predicate>);
static_assert(std::is_same_v<decltype(&asc::std::is_gt), predicate>);
static_assert(std::is_same_v<decltype(&asc::std::is_gteq), predicate>);

static_assert(std::is_convertible_v<weak, partial>);
static_assert(std::is_convertible_v<strong, weak>);
static_assert(std::is_convertible_v<strong, partial>);
static_assert(!std::is_convertible_v<partial, weak>);
static_assert(!std::is_convertible_v<partial, strong>);
static_assert(!std::is_convertible_v<weak, strong>);
static_assert(static_cast<partial>(weak::less) == partial::less);
static_assert(static_cast<partial>(weak::equivalent) == partial::equivalent);
static_assert(static_cast<partial>(weak::greater) == partial::greater);
static_assert(static_cast<weak>(strong::less) == weak::less);
static_assert(static_cast<weak>(strong::equal) == weak::equivalent);
static_assert(static_cast<weak>(strong::equivalent) == weak::equivalent);
static_assert(static_cast<weak>(strong::greater) == weak::greater);
static_assert(static_cast<partial>(strong::less) == partial::less);
static_assert(static_cast<partial>(strong::equal) == partial::equivalent);
static_assert(static_cast<partial>(strong::equivalent) == partial::equivalent);
static_assert(static_cast<partial>(strong::greater) == partial::greater);

template <class Ordering>
constexpr bool contract(Ordering value)
{
    return std::is_same_v<decltype(asc::std::is_eq(value)), bool> && noexcept(asc::std::is_eq(value)) &&
        std::is_same_v<decltype(asc::std::is_neq(value)), bool> && noexcept(asc::std::is_neq(value)) &&
        std::is_same_v<decltype(asc::std::is_lt(value)), bool> && noexcept(asc::std::is_lt(value)) &&
        std::is_same_v<decltype(asc::std::is_lteq(value)), bool> && noexcept(asc::std::is_lteq(value)) &&
        std::is_same_v<decltype(asc::std::is_gt(value)), bool> && noexcept(asc::std::is_gt(value)) &&
        std::is_same_v<decltype(asc::std::is_gteq(value)), bool> && noexcept(asc::std::is_gteq(value));
}

static_assert(contract(partial::unordered));
static_assert(contract(weak::less));
static_assert(contract(strong::equal));

template <class Ordering>
constexpr unsigned int zero_mask(Ordering value)
{
    return (value == 0 ? 1U : 0U) | (value != 0 ? 2U : 0U) | (value < 0 ? 4U : 0U) | (value <= 0 ? 8U : 0U) |
        (value > 0 ? 16U : 0U) | (value >= 0 ? 32U : 0U);
}

template <class Ordering>
constexpr unsigned int reverse_zero_mask(Ordering value)
{
    return (0 == value ? 1U : 0U) | (0 != value ? 2U : 0U) | (0 > value ? 4U : 0U) | (0 >= value ? 8U : 0U) |
        (0 < value ? 16U : 0U) | (0 <= value ? 32U : 0U);
}

template <class Ordering>
constexpr bool canonical(Ordering value, unsigned int expected)
{
    return asc_stl_comparison_helpers_test::predicate_mask(value) == expected && zero_mask(value) == expected &&
        reverse_zero_mask(value) == expected;
}

// Eleven independently specified rows, six helper outcomes in each mask.
static_assert(canonical(partial::less, 14));
static_assert(canonical(partial::equivalent, 41));
static_assert(canonical(partial::greater, 50));
static_assert(canonical(partial::unordered, 2));
static_assert(canonical(weak::less, 14));
static_assert(canonical(weak::equivalent, 41));
static_assert(canonical(weak::greater, 50));
static_assert(canonical(strong::less, 14));
static_assert(canonical(strong::equal, 41));
static_assert(canonical(strong::equivalent, 41));
static_assert(canonical(strong::greater, 50));

}  // namespace

int main()
{
    volatile unsigned int input[11] = {0, 1, 2, 3, 0, 1, 2, 0, 1, 1, 2};
    const auto correct = asc_stl_comparison_helpers_test::evaluate(input);
    if (correct.failures != 0 || correct.signature != 358 || correct.checks != 66) {
        return 1;
    }
    // A valid but incorrect category value must fail its independent golden.
    input[0] = 2;
    const auto mismatched = asc_stl_comparison_helpers_test::evaluate(input);
    if (mismatched.failures != 1 || mismatched.signature != 394 || mismatched.checks != 66) {
        return 2;
    }
    input[0] = 0;
    input[4] = 3;
    const auto invalid = asc_stl_comparison_helpers_test::evaluate(input);
    return invalid.failures == 1 && invalid.signature == 344 && invalid.checks == 60 ? 0 : 3;
}
