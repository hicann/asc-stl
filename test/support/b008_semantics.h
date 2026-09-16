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
#ifndef CANN_ASC_STL_TEST_SUPPORT_B008_SEMANTICS_H
#define CANN_ASC_STL_TEST_SUPPORT_B008_SEMANTICS_H

#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__concepts/predicate.h>
#include <asc/std/__functional/unwrap_ref.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/is_comparable.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/limits>

namespace asc_stl_b008_test {
struct base {
    int value = 4;
    CANN_ASC_STL_API constexpr int add(int amount) const noexcept
    {
        return value + amount;
    }
};
struct derived : base {};
struct callable {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return value * 2;
    }
};
struct throwing_conversion {
    CANN_ASC_STL_API constexpr operator int() const noexcept(false)
    {
        return 1;
    }
};
struct conversion_callable {
    CANN_ASC_STL_API constexpr throwing_conversion operator()() const noexcept
    {
        return {};
    }
};
struct readable {
    using value_type = const int;
};
struct incrementable {
    using difference_type = long;
};
template <class = void>
struct delegate_base {
    CANN_ASC_STL_API constexpr delegate_base() noexcept = default;
    CANN_ASC_STL_API constexpr explicit delegate_base(int input) noexcept : value(input)
    {}
    int value = 0;
};
struct delegated : delegate_base<> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(delegated, delegate_base, void);
};
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
static_assert(asc::std::integral<int> && asc::std::signed_integral<int> && asc::std::unsigned_integral<unsigned>);
static_assert(asc::std::floating_point<float> && asc::std::derived_from<derived, base>);
static_assert(asc::std::convertible_to<int, long> && asc::std::destructible<int> && asc::std::copy_constructible<int>);
static_assert(asc::std::common_reference_with<int&, const int&>);
#endif
static_assert(asc::std::is_same_v<asc::std::common_reference_t<int&, const int&, volatile int&>, const volatile int&>);
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
static_assert(asc::std::invocable<callable, int> && asc::std::predicate<callable, int>);
#endif
static_assert(asc::std::is_same_v<asc::std::invoke_result_t<callable, int>, int>);
static_assert(!asc::std::is_invocable_v<int> && !asc::std::is_nothrow_invocable_v<int>);
static_assert(asc::std::is_invocable_r_v<int, conversion_callable> &&
    !asc::std::is_nothrow_invocable_r_v<int, conversion_callable>);
static_assert(asc::std::is_same_v<asc::std::__unwrap_ref_decay_t<const int&>, int>);
static_assert(asc::std::is_same_v<asc::std::incrementable_traits<int*>::difference_type, asc::std::ptrdiff_t>);
static_assert(asc::std::is_same_v<asc::std::incrementable_traits<incrementable>::difference_type, long>);
static_assert(asc::std::is_same_v<asc::std::indirectly_readable_traits<readable>::value_type, int>);
static_assert(
    asc::std::__is_cpp17_equality_comparable_v<int, int> && asc::std::__is_cpp17_less_than_comparable_v<int, int>);
static_assert(asc::std::is_swappable_v<int> && asc::std::numeric_limits<bool>::digits == 1);
static_assert(asc::std::numeric_limits<int>::min() < 0 && asc::std::numeric_limits<unsigned>::is_modulo);
static_assert(asc::std::numeric_limits<float>::digits == 24 && asc::std::numeric_limits<const double>::digits == 53);
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
static_assert(asc::std::numeric_limits<char8_t>::digits == 8);
#endif
CANN_ASC_STL_API constexpr int evaluate()
{
    base object{};
    int (base::*member)(int) const noexcept = &base::add;
    int invoked = asc::std::invoke(member, object, 3);
    int doubled = asc::std::invoke_r<int>(callable{}, 5);
    int left = 1;
    int right = 2;
    asc::std::swap(left, right);  // NOLINT(build/include_what_you_use)
    int old = asc::std::exchange(left, 7);
    delegated value(9);
    return invoked == 7 && doubled == 10 && left == 7 && right == 1 && old == 2 && value.value == 9 ? 0 : 1;
}
}  // namespace asc_stl_b008_test
#endif  // CANN_ASC_STL_TEST_SUPPORT_B008_SEMANTICS_H
