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

#ifndef CANN_ASC_STL_TEST_SUPPORT_B010_SEMANTICS_H
#define CANN_ASC_STL_TEST_SUPPORT_B010_SEMANTICS_H

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__cmath/sincos.h>
#include <asc/std/__cmath/uabs.h>
#include <asc/std/__fwd/common_iterator.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/bounded_iter.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__iterator/unreachable_sentinel.h>
#include <asc/std/__iterator/wrap_iter.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__tuple/tuple_constraints.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/vector_types.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/functional>

namespace asc_stl_b010_test {

struct identity {
    CANN_ASC_STL_API constexpr int& operator()(int& value) const noexcept
    {
        return value;
    }
};

struct member_range {
    int values[4] = {3, 5, 7, 9};
    CANN_ASC_STL_API constexpr int* begin() noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr const int* begin() const noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr int* end() noexcept
    {
        return values + 4;
    }
    CANN_ASC_STL_API constexpr const int* end() const noexcept
    {
        return values + 4;
    }
    CANN_ASC_STL_API constexpr unsigned size() const noexcept
    {
        return 4;
    }
};

namespace adl_range {
struct range {
    int values[3] = {2, 4, 6};
};
CANN_ASC_STL_API constexpr int* begin(range& value) noexcept
{
    return value.values;
}
CANN_ASC_STL_API constexpr int* end(range& value) noexcept
{
    return value.values + 3;
}
CANN_ASC_STL_API constexpr unsigned size(range&) noexcept
{
    return 3;
}
}  // namespace adl_range

struct lifetime_probe {
    int value;
    CANN_ASC_STL_API explicit constexpr lifetime_probe(int input) noexcept : value(input)
    {}
    CANN_ASC_STL_API ~lifetime_probe() noexcept
    {
        value = -1;
    }
};

static_assert(asc::std::__equal_to{}(4, 4));
static_assert(asc::std::__less{}(3, 4));
static_assert(asc::std::__uabs(-17) == 17U);
static_assert(asc::std::__uabs(static_cast<unsigned short>(9)) == 9U);
static_assert(asc::std::is_same_v<decltype(asc::std::__uabs(-1LL)), unsigned long long>);
static_assert(asc::std::tuple_size<asc::std::pair<int, long>>::value == 2);
static_assert(asc::std::is_same_v<asc::std::tuple_element_t<1, asc::std::pair<int, long>>, long>);
static_assert(asc::std::is_same_v<asc::std::unwrap_reference_t<asc::std::reference_wrapper<int>>, int&>);
static_assert(asc::std::is_same_v<asc::std::unwrap_ref_decay_t<asc::std::reference_wrapper<int>>, int&>);
static_assert(asc::std::is_same_v<asc::std::unwrap_ref_decay_t<const int&>, int>);
static_assert(asc::std::pair<int, int>{1, 2} != asc::std::pair<int, int>{1, 3});
static_assert(asc::std::pair<int, int>{1, 2} < asc::std::pair<int, int>{1, 3});
static_assert(asc::std::pair<int, int>{1, 3} > asc::std::pair<int, int>{1, 2});
static_assert(asc::std::pair<int, int>{1, 2} <= asc::std::pair<int, int>{1, 3});
static_assert(asc::std::pair<int, int>{1, 3} >= asc::std::pair<int, int>{1, 2});
static_assert(asc::std::is_same_v<typename asc::std::projected<int*, identity>::value_type, int>);
static_assert(asc::std::is_same_v<asc::std::ranges::iterator_t<member_range>, int*>);
static_assert(CANN_ASC_STL_DETAIL_AUTO_CAST(7) == 7);
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
static_assert(asc::std::input_or_output_iterator<int*>);
static_assert(asc::std::random_access_iterator<int*>);
static_assert(asc::std::contiguous_iterator<int*>);
static_assert(asc::std::indirectly_swappable<int*>);
#endif

CANN_ASC_STL_API constexpr int evaluate_constexpr() noexcept
{
    int values[4] = {8, 3, 5, 1};
    auto bounded = asc::std::__make_bounded_iter(values, values, values + 4);
    int* wrapped = values;
    asc::std::advance(wrapped, 2);
    asc::std::iter_swap(values, values + 3);
    asc::std::pair<int, long> pair(values[0], values[2]);
    member_range member{};
    adl_range::range adl{};
    return *bounded == 1 && *wrapped == 5 && asc::std::iter_move(values + 1) == 3 && asc::std::get<0>(pair) == 1 &&
            asc::std::get<int>(pair) == 1 && asc::std::ranges::end(member) - asc::std::ranges::begin(member) == 4 &&
            asc::std::ranges::size(member) == 4 && asc::std::ranges::ssize(member) == 4 &&
            asc::std::ranges::end(adl) - asc::std::ranges::begin(adl) == 3 && asc::std::ranges::size(adl) == 3 &&
            values != asc::std::unreachable_sentinel ?
        0 :
        1;
}

static_assert(evaluate_constexpr() == 0);

CANN_ASC_STL_API int evaluate_runtime() noexcept
{
    alignas(lifetime_probe) unsigned char storage[sizeof(lifetime_probe)] = {};
    auto* value = asc::std::construct_at(reinterpret_cast<lifetime_probe*>(storage), 23);
    const bool constructed = value->value == 23;
    asc::std::destroy_at(value);
#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    const auto trig = asc::std::__sincos(0.0F);
    const bool trigonometry = trig.sin == 0.0F && trig.cos == 1.0F;
#else
    const bool trigonometry = true;
#endif
    return constructed && trigonometry && evaluate_constexpr() == 0 ? 0 : 1;
}

}  // namespace asc_stl_b010_test

#endif  // CANN_ASC_STL_TEST_SUPPORT_B010_SEMANTICS_H
