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

#ifndef ASC_STL_TEST_B020_SEMANTICS_H
#define ASC_STL_TEST_B020_SEMANTICS_H

#include <asc/std/__algorithm/count_if.h>
#include <asc/std/__algorithm/includes.h>
#include <asc/std/__algorithm/is_heap_until.h>
#include <asc/std/__algorithm/is_sorted_until.h>
#include <asc/std/__algorithm/lower_bound.h>
#include <asc/std/__algorithm/minmax_element.h>
#include <asc/std/__algorithm/mismatch.h>
#include <asc/std/__algorithm/partition.h>
#include <asc/std/__algorithm/partition_copy.h>
#include <asc/std/__algorithm/push_heap.h>
#include <asc/std/__algorithm/reverse.h>
#include <asc/std/__algorithm/sample.h>
#include <asc/std/__algorithm/search_n.h>
#include <asc/std/__algorithm/set_intersection.h>
#include <asc/std/__algorithm/shuffle.h>
#include <asc/std/__algorithm/sift_down.h>
#include <asc/std/__algorithm/unique.h>
#include <asc/std/__algorithm/unique_copy.h>
#include <asc/std/__algorithm/upper_bound.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__functional/compose.h>
#include <asc/std/optional>
#include <asc/std/utility>

#include "vocabulary_copy_test.h"

namespace asc_stl_b020_test {

struct less_int {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};

struct equal_int {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left == right;
    }
};

struct even_int {
    CANN_ASC_STL_API constexpr bool operator()(int value) const noexcept
    {
        return value % 2 == 0;
    }
};

struct add_three {
    CANN_ASC_STL_API constexpr int operator()(int a, int b, int c) const noexcept
    {
        return a + b + c;
    }
};

struct times_two {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return value * 2;
    }
};

struct plus_one {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return value + 1;
    }
};

struct deterministic_urbg {
    using result_type = unsigned int;
    unsigned int state = 7;

    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return 0xffffffffU;
    }
    CANN_ASC_STL_API result_type operator()() noexcept
    {
        state = state * 1664525U + 1013904223U;
        return state;
    }
};

CANN_ASC_STL_API constexpr int evaluate_query_algorithms() noexcept
{
    int values[] = {1, 2, 2, 3, 5, 8};
    int subset[] = {2, 5};
    int heap[] = {9, 7, 8, 1, 6};
    int unsorted[] = {1, 2, 4, 3, 5};
    int failures = asc::std::count_if(values, values + 6, even_int{}) != 3;
    failures += !asc::std::includes(values, values + 6, subset, subset + 2, less_int{});
    failures += asc::std::is_heap_until(heap, heap + 5, less_int{}) != heap + 5;
    failures += asc::std::is_sorted_until(unsorted, unsorted + 5, less_int{}) != unsorted + 3;
    failures += asc::std::search_n(values, values + 6, 2, 2, equal_int{}) != values + 1;
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_selection_algorithms() noexcept
{
    int values[] = {4, 1, 7, 1, 6};
    int other[] = {4, 1, 8, 1, 6};
    int evens[5] = {};
    int odds[5] = {};
    auto extrema = asc::std::minmax_element(values, values + 5, less_int{});
    auto unequal = asc::std::mismatch(values, values + 5, other, other + 5, equal_int{});
    auto partitioned = asc::std::partition_copy(values, values + 5, evens, odds, even_int{});
    int failures = extrema.first != values + 1 || extrema.second != values + 2;
    failures += unequal.first != values + 2 || unequal.second != other + 2;
    failures += partitioned.first != evens + 2 || partitioned.second != odds + 3;
    failures += evens[0] != 4 || evens[1] != 6 || odds[0] != 1 || odds[1] != 7 || odds[2] != 1;
    return failures;
}

CANN_ASC_STL_API int evaluate_mutating_algorithms() noexcept
{
    int sorted[] = {1, 2, 2, 4, 7};
    int failures = asc::std::lower_bound(sorted, sorted + 5, 2, less_int{}) != sorted + 1;
    failures += asc::std::upper_bound(sorted, sorted + 5, 2, less_int{}) != sorted + 3;

    int partitioned[] = {1, 2, 3, 4, 5, 6};
    int* middle = asc::std::partition(partitioned, partitioned + 6, even_int{});
    failures += middle != partitioned + 3;
    for (int* iterator = partitioned; iterator != middle; ++iterator) {
        failures += !even_int{}(*iterator);
    }
    for (int* iterator = middle; iterator != partitioned + 6; ++iterator) {
        failures += even_int{}(*iterator);
    }

    int heap[] = {9, 7, 8, 1, 10};
    asc::std::push_heap(heap, heap + 5, less_int{});
    failures += heap[0] != 10;

    int reversed[] = {1, 2, 3, 4};
    asc::std::reverse(reversed, reversed + 4);
    failures += reversed[0] != 4 || reversed[3] != 1;

    int intersection[4] = {};
    int left[] = {1, 2, 3, 5};
    int right[] = {2, 3, 4};
    int* intersection_end = asc::std::set_intersection(left, left + 4, right, right + 3, intersection, less_int{});
    failures += intersection_end != intersection + 2 || intersection[0] != 2 || intersection[1] != 3;

    int repeated[] = {1, 1, 2, 2, 3};
    int* unique_end = asc::std::unique(repeated, repeated + 5, equal_int{});
    failures += unique_end != repeated + 3 || repeated[0] != 1 || repeated[1] != 2 || repeated[2] != 3;
    int copied[5] = {};
    int source[] = {1, 1, 2, 3, 3};
    int* copied_end = asc::std::unique_copy(source, source + 5, copied, equal_int{});
    failures += copied_end != copied + 3 || copied[0] != 1 || copied[1] != 2 || copied[2] != 3;

    deterministic_urbg generator{};
    int sample_output[3] = {};
    failures += asc::std::sample(sorted, sorted + 5, sample_output, 3, generator) != sample_output + 3;
    int shuffled[] = {1, 2, 3, 4};
    asc::std::shuffle(shuffled, shuffled + 4, generator);
    failures += shuffled[0] + shuffled[1] + shuffled[2] + shuffled[3] != 10;

    int sifted[] = {1, 9, 8, 7, 6};
    asc::std::__sift_down<asc::std::__classic_algorithm_iterator_operations>(sifted, less_int{}, 5, sifted);
    failures += sifted[0] != 9;
    return failures;
}

CANN_ASC_STL_API constexpr int evaluate_functional() noexcept
{
    auto bound = asc::std::__bind_back(add_three{}, 3, 4);
    auto composed = asc::std::__compose(times_two{}, plus_one{});
    return (bound(2) != 9) + (composed(3) != 8);
}

static_assert(asc_stl_copy_test::check_traits<asc::std::optional>());
static_assert(asc::std::is_trivially_copyable_v<asc::std::optional<asc_stl_copy_test::move_only&>>);

CANN_ASC_STL_API int evaluate_optional_copy(int input)
{
    using asc_stl_copy_test::payload;
    using optional = asc::std::optional<payload>;
    asc_stl_copy_test::counts calls;
    int failures = 0;
    {
        const optional empty;
        const optional source(asc::std::in_place, calls, input);
        optional target(empty);
        optional copied(source);
        failures += target.has_value() || !copied || copied->value != input;
        target = source;
        copied = target;
        target = empty;
        target = empty;
        failures += target.has_value() || !copied || copied->value != input || calls.live != 2;
    }
    using move_optional = asc::std::optional<asc_stl_copy_test::move_only>;
    move_optional move_source(asc::std::in_place, input);
    move_optional moved(asc::std::move(move_source));
    move_optional assigned;
    assigned = asc::std::move(moved);  // NOLINT(build/include_what_you_use)
    failures += !assigned || assigned->value != input;
    asc_stl_copy_test::move_only object(input);
    asc::std::optional<asc_stl_copy_test::move_only&> binding(object);
    auto alias = binding;
    return failures + (&*alias != &object) + (calls.live != 0 || calls.copies != 2 || calls.assignments != 1);
}

CANN_ASC_STL_API int evaluate_optional() noexcept
{
    asc::std::optional<int> empty;
    asc::std::optional<int> value(4);
    int failures = evaluate_optional_copy(13) + empty.has_value();
    failures += !value || *value != 4 || value.value_or(9) != 4;
    failures += empty.value_or(9) != 9;
    failures += !(value > asc::std::nullopt) || !(asc::std::nullopt < value);
    value.emplace(7);
    failures += *value != 7;
    auto made = asc::std::make_optional<int>(11);
    value.swap(made);
    failures += *value != 11 || *made != 7;
    value.reset();
    failures += value.has_value();
    return failures;
}

}  // namespace asc_stl_b020_test

#endif  // ASC_STL_TEST_B020_SEMANTICS_H
