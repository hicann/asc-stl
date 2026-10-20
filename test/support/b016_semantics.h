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

#ifndef ASC_STL_TEST_B016_SEMANTICS_H
#define ASC_STL_TEST_B016_SEMANTICS_H
#include <asc/hierarchy>
#include <asc/std/__algorithm/search.h>
#include <asc/std/__charconv/to_chars.h>
#include <asc/std/__chrono/duration.h>
#include <asc/std/__chrono/year.h>
#include <asc/std/__functional/perfect_forward.h>
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__iterator/common_iterator.h>
#include <asc/std/__iterator/counted_iterator.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/reverse_access.h>
#include <asc/std/__optional/nullopt.h>
#include <asc/std/__random/uniform_int_distribution.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/limits>
#include <asc/std/tuple>
namespace asc_stl_b016_test {
struct sentinel {
    int* end;
};
CANN_ASC_STL_API bool operator==(int* value, sentinel other)
{
    return value == other.end;
}
CANN_ASC_STL_API bool operator==(sentinel other, int* value)
{
    return value == other.end;
}
CANN_ASC_STL_API bool operator!=(int* value, sentinel other)
{
    return value != other.end;
}
CANN_ASC_STL_API bool operator!=(sentinel other, int* value)
{
    return value != other.end;
}
static_assert(asc::std::sentinel_for<sentinel, int*>, "B016 sentinel must model both equality directions in C++17");
struct generator {
    using result_type = unsigned int;
    unsigned int state = 7;
    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return 15;
    }
    CANN_ASC_STL_API result_type operator()() noexcept
    {
        const result_type result = state;
        state = (state + 1) & 15U;
        return result;
    }
};
struct narrow_generator {
    using result_type = unsigned int;
    unsigned int state = 0;
    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return 3;
    }
    CANN_ASC_STL_API result_type operator()() noexcept
    {
        const result_type result = state;
        state = (state + 1) & 3U;
        return result;
    }
};
struct add {
    CANN_ASC_STL_API int operator()(int left, int right) const noexcept
    {
        return left + right;
    }
};
struct wrapped_iterator {
    int* current;
    CANN_ASC_STL_API constexpr int* operator->() const noexcept
    {
        return current;
    }
};
struct wrapped_range {
    int* values;
    CANN_ASC_STL_API constexpr wrapped_iterator begin() const noexcept
    {
        return {values};
    }
};
struct nonpointer_data_range {
    int* values;
    CANN_ASC_STL_API constexpr int data() const noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API constexpr int* begin() const noexcept
    {
        return values;
    }
};
CANN_ASC_STL_API constexpr int evaluate_hierarchy() noexcept
{
    constexpr auto hierarchy = asc::make_hierarchy(asc::grid_dims<3, 2>(), asc::block_dims<32, 2>());
    static_assert(hierarchy.count(asc::grid) == 6, "grid count");
    static_assert(hierarchy.count(asc::block) == 64, "block count");
    constexpr auto launch = asc::get_launch_dimensions(hierarchy);
    static_assert(launch.grid == asc::extent3d{3, 2, 1}, "grid extents");
    return 0;
}

CANN_ASC_STL_API int evaluate_iterators_and_charconv() noexcept
{
    int failures = 0;
    int values[] = {1, 2, 3, 4};
    int pattern[] = {2, 3};
    failures += asc::std::search(values, values + 4, pattern, pattern + 2) != values + 1;
    failures += asc::std::distance(values, values + 4) != 4;
    failures += *asc::std::rbegin(values) != 4;
    asc::std::counted_iterator<int*> counted(values, 2);
    ++counted;
    failures += *counted != 2 || counted.count() != 1;
    asc::std::common_iterator<int*, sentinel> common(values);
    ++common;
    failures += *common != 2;
    char buffer[16]{};
    const auto converted = asc::std::to_chars(buffer, buffer + 16, -42);
    failures += converted.ptr != buffer + 3 || buffer[0] != '-' || buffer[1] != '4' || buffer[2] != '2';
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_chrono() noexcept
{
    constexpr asc::std::chrono::seconds two_seconds(2);
    constexpr asc::std::chrono::milliseconds half_second(500);
    static_assert(
        asc::std::chrono::duration_cast<asc::std::chrono::milliseconds>(two_seconds).count() == 2000, "duration cast");
    static_assert(two_seconds + half_second == asc::std::chrono::milliseconds(2500), "cross-period arithmetic");
    static_assert(
        asc::std::chrono::floor<asc::std::chrono::seconds>(asc::std::chrono::milliseconds(-1500)).count() == -2,
        "duration floor");
    static_assert(asc::std::chrono::ceil<asc::std::chrono::seconds>(asc::std::chrono::milliseconds(1500)).count() == 2,
        "duration ceil");
    static_assert(asc::std::chrono::round<asc::std::chrono::seconds>(asc::std::chrono::milliseconds(2500)).count() == 2,
        "duration ties to even");
    constexpr auto extreme_offset = [] {
        asc::std::chrono::year value(0);
        value -= asc::std::chrono::years(asc::std::numeric_limits<int>::min());
        return value;
    }();
    constexpr auto extreme_sum = [] {
        asc::std::chrono::year value(32767);
        value += asc::std::chrono::years(asc::std::numeric_limits<int>::max());
        return value;
    }();
    (void)extreme_offset;
    (void)extreme_sum;
    asc::std::chrono::year value(2024);
    value -= asc::std::chrono::years(1);
    return value != asc::std::chrono::year(2023);
}

CANN_ASC_STL_API int evaluate_random_and_tuple() noexcept
{
    int failures = 0;
    generator random{};
    const int sampled = asc::std::uniform_int_distribution<int>(1, 6)(random);
    failures += sampled < 1 || sampled > 6;
    narrow_generator narrow_random{};
    const int expanded_sample = asc::std::uniform_int_distribution<int>(0, 9)(narrow_random);
    failures += expanded_sample < 0 || expanded_sample > 9;
    asc::std::__perfect_forward<add, int> bound_add(2);
    failures += bound_add(3) != 5;
    const auto tuple = asc::std::make_tuple(4, 5);
    failures += asc::std::get<0>(tuple) != 4 || asc::std::get<1>(tuple) != 5;
    return failures;
}

CANN_ASC_STL_API int evaluate_range_data() noexcept
{
    int values[] = {1, 2, 3, 4};
    wrapped_range range{values};
    int* range_data = asc::std::ranges::data(range);
    nonpointer_data_range fallback{values};
    int* fallback_data = asc::std::ranges::data(fallback);
    return (range_data != values) + (fallback_data != values) + (asc::std::ranges::data(values) != values);
}

CANN_ASC_STL_API int evaluate_device_hierarchy() noexcept
{
    int failures = 0;
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    failures += asc::block_count() == 0;
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    failures += asc::thread_count() == 0 || asc::warp_count() == 0;
    failures += asc::thread_extents_3d().count() != asc::thread_count();
    failures += asc::block_extents_3d().count() != asc::block_count();
    failures += asc::lane_id() >= asc::warp_size;
#else
    failures += asc::sub_block_count() == 0;
    failures += asc::sub_block_index() >= asc::sub_block_count();
#endif
#endif
    return failures;
}

CANN_ASC_STL_API int evaluate_common() noexcept
{
    return evaluate_hierarchy() + evaluate_iterators_and_charconv() + evaluate_chrono() + evaluate_random_and_tuple() +
        evaluate_range_data() + evaluate_device_hierarchy();
}
}  // namespace asc_stl_b016_test
#endif  // ASC_STL_TEST_B016_SEMANTICS_H
