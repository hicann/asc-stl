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

#ifndef ASC_STL_TEST_SUPPORT_B021_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_B021_SEMANTICS_H

#include <asc/memory_resource>
#include <asc/std/ctime>
#include <asc/std/__algorithm/binary_search.h>
#include <asc/std/__algorithm/copy_backward.h>
#include <asc/std/__algorithm/equal_range.h>
#include <asc/std/__algorithm/make_heap.h>
#include <asc/std/__algorithm/merge.h>
#include <asc/std/__algorithm/move_backward.h>
#include <asc/std/__algorithm/next_permutation.h>
#include <asc/std/__algorithm/pop_heap.h>
#include <asc/std/__algorithm/prev_permutation.h>
#include <asc/std/__algorithm/rotate_copy.h>
#include <asc/std/__algorithm/set_difference.h>
#include <asc/std/__algorithm/set_symmetric_difference.h>
#include <asc/std/__algorithm/set_union.h>
#include <asc/std/__chrono/hh_mm_ss.h>
#include <asc/std/__chrono/literals.h>
#include <asc/std/__chrono/month_weekday.h>
#include <asc/std/__chrono/year_month_day.h>

namespace asc_stl_b021_test {

struct descending {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left > right;
    }
};

struct stable_value {
    int key;
    int source;
};

struct stable_less {
    CANN_ASC_STL_API constexpr bool operator()(const stable_value& left, const stable_value& right) const noexcept
    {
        return left.key < right.key;
    }
};

CANN_ASC_STL_API constexpr int evaluate_algorithms()
{
    int failures = 0;
    int sorted[] = {1, 2, 2, 4};
    failures += !asc::std::binary_search(sorted, sorted + 4, 2);
    failures += asc::std::binary_search(sorted, sorted + 4, 3);
    failures += asc::std::binary_search(sorted, sorted, 1);
    int reverse_sorted[] = {4, 3, 2, 1};
    failures += !asc::std::binary_search(reverse_sorted, reverse_sorted + 4, 3, descending{});
    const auto equal = asc::std::equal_range(sorted, sorted + 4, 2);
    failures += equal.first != sorted + 1 || equal.second != sorted + 3;

    int backward[] = {1, 2, 3, 0, 0};
    failures += asc::std::copy_backward(backward, backward + 3, backward + 5) != backward + 2;
    failures += backward[2] != 1 || backward[3] != 2 || backward[4] != 3;
    failures += asc::std::copy_backward(backward, backward, backward + 2) != backward + 2;
    int moved[] = {4, 5, 6, 0, 0};
    failures += asc::std::move_backward(moved, moved + 3, moved + 5) != moved + 2;
    failures += moved[2] != 4 || moved[3] != 5 || moved[4] != 6;

    int heap[] = {1, 5, 2, 4, 3};
    asc::std::make_heap(heap, heap + 5);
    failures += heap[0] != 5;
    asc::std::pop_heap(heap, heap + 5);
    failures += heap[4] != 5;
    asc::std::make_heap(heap, heap);

    int permutation[] = {1, 2, 3};
    failures += !asc::std::next_permutation(permutation, permutation + 3);
    failures += permutation[0] != 1 || permutation[1] != 3 || permutation[2] != 2;
    failures += !asc::std::prev_permutation(permutation, permutation + 3);
    failures += permutation[0] != 1 || permutation[1] != 2 || permutation[2] != 3;

    int rotated[4] = {};
    asc::std::rotate_copy(sorted, sorted + 2, sorted + 4, rotated);
    failures += rotated[0] != 2 || rotated[1] != 4 || rotated[2] != 1 || rotated[3] != 2;

    const int left[] = {1, 2, 4};
    const int right[] = {2, 3, 4};
    int output[6] = {};
    auto end = asc::std::merge(left, left + 3, right, right + 3, output);
    failures += end != output + 6 || output[0] != 1 || output[1] != 2 || output[2] != 2 || output[3] != 3 ||
        output[4] != 4 || output[5] != 4;
    const stable_value stable_left[] = {{1, 1}, {2, 1}};
    const stable_value stable_right[] = {{1, 2}, {3, 2}};
    stable_value stable_output[4] = {};
    asc::std::merge(stable_left, stable_left + 2, stable_right, stable_right + 2, stable_output, stable_less{});
    failures += stable_output[0].source != 1 || stable_output[1].source != 2;
    end = asc::std::set_difference(left, left + 3, right, right + 3, output);
    failures += end != output + 1 || output[0] != 1;
    end = asc::std::set_symmetric_difference(left, left + 3, right, right + 3, output);
    failures += end != output + 2 || output[0] != 1 || output[1] != 3;
    end = asc::std::set_union(left, left + 3, right, right + 3, output);
    failures += end != output + 4 || output[0] != 1 || output[1] != 2 || output[2] != 3 || output[3] != 4;
    failures += asc::std::set_union(left, left, right, right, output) != output;
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_chrono()
{
    using asc::std::chrono::day;
    using asc::std::chrono::February;
    using asc::std::chrono::hh_mm_ss;
    using asc::std::chrono::hours;
    using asc::std::chrono::is_am;
    using asc::std::chrono::is_pm;
    using asc::std::chrono::last;
    using asc::std::chrono::make12;
    using asc::std::chrono::make24;
    using asc::std::chrono::March;
    using asc::std::chrono::milliseconds;
    using asc::std::chrono::minutes;
    using asc::std::chrono::Monday;
    using asc::std::chrono::October;
    using asc::std::chrono::seconds;
    using asc::std::chrono::Sunday;
    using asc::std::chrono::sys_days;
    using asc::std::chrono::Thursday;
    using asc::std::chrono::weekday;
    using asc::std::chrono::year;
    using asc::std::chrono::year_month_day;
    using asc::std::chrono::year_month_day_last;
#if !defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
    using asc::std::literals::chrono_literals::operator"" d;
    using asc::std::literals::chrono_literals::operator"" y;
#endif
    int failures = 0;
    constexpr auto leap = year{2024} / February / day{29};
    constexpr auto ordinary = year{2023} / February / day{29};
    failures += !leap.ok() || ordinary.ok();
    constexpr sys_days leap_days{leap};
    constexpr year_month_day round_trip{leap_days};
    failures += round_trip != leap;
    failures += weekday{leap_days} != Thursday;
    failures += !(March / Monday[2]).ok() || !(October / Sunday[last]).ok();
    failures += year_month_day_last{year{2024}, February / last}.day() != day{29};
#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
    failures += asc::std::literals::chrono_literals::operator"" y(12) != year{12} ||
        asc::std::literals::chrono_literals::operator"" d(7) != day{7};
#else
    failures += 12y != year{12} || 7d != day{7};
#endif
    failures += !is_am(hours{11}) || is_am(hours{12}) || !is_pm(hours{12});
    failures += make12(hours{0}) != hours{12} || make24(hours{3}, true) != hours{15};
    constexpr hh_mm_ss<milliseconds> split{milliseconds{3723004}};
    failures += split.hours() != hours{1} || split.minutes() != minutes{2} || split.seconds() != seconds{3} ||
        split.subseconds() != milliseconds{4};
#if !defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
    failures += asc::std::difftime(9, 4) != 5.0;
#endif
    failures += CLOCKS_PER_SEC <= 0;
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_common()
{
    return evaluate_algorithms() + evaluate_chrono();
}

inline int evaluate_memory_resource()
{
    int failures = 0;
    constexpr auto device_properties = asc::device_memory_resource::properties();
    constexpr auto pinned_properties = asc::pinned_memory_resource::properties();
    static_assert(!device_properties.host_accessible() && device_properties.device_accessible());
    static_assert(device_properties.maximum_alignment() == 32);
    static_assert(pinned_properties.host_accessible() && !pinned_properties.device_accessible());

    asc::device_memory_resource device_resource{3};
    asc::device_memory_resource_ref device_ref{device_resource};
    asc::device_memory_resource_ref empty_device_ref;
    failures += !device_ref.valid() || device_ref.device_ordinal() != 3 || empty_device_ref.valid();
    failures += device_ref == empty_device_ref || !(device_ref == asc::device_memory_resource_ref{device_resource});

    asc::pinned_memory_resource pinned_resource;
    asc::pinned_memory_resource_ref pinned_ref{pinned_resource};
    asc::pinned_memory_resource_ref empty_pinned_ref;
    failures += !pinned_ref.valid() || empty_pinned_ref.valid() || pinned_ref == empty_pinned_ref;
    return failures;
}

}  // namespace asc_stl_b021_test

#endif  // ASC_STL_TEST_SUPPORT_B021_SEMANTICS_H
