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

#ifndef ASC_STL_TEST_B024_SEMANTICS_H
#define ASC_STL_TEST_B024_SEMANTICS_H

#include <asc/pipeline>
#include <asc/std/__algorithm/for_each_n.h>
#include <asc/std/__algorithm/generate_n.h>
#include <asc/std/__algorithm/is_permutation.h>
#include <asc/std/__algorithm/partition_point.h>
#include <asc/std/__algorithm/ranges_for_each.h>
#include <asc/std/__chrono/year_month_weekday.h>
#include <asc/std/__cinttypes/integer_intmax.h>
#include <asc/std/__expected/expected.h>
#include <asc/std/__inplace_vector/inplace_vector.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/allocate_at_least.h>
#include <asc/std/__numeric/iota.h>
#include <asc/std/__numeric/transform_exclusive_scan.h>
#include <asc/std/__optional/optional.h>
#include <asc/std/__random/linear_congruential_engine.h>
#include <asc/std/__type_traits/is_non_narrowing_convertible.h>
#include <asc/std/__variant/comparison.h>
#include <asc/std/iterator>
#include <asc/std/ranges>
#include <asc/__cmath/operations.h>
#include <asc/__iterator/adaptors.h>
#include <asc/__memory/buffers.h>
#include <asc/__random/pcg64.h>
#include <asc/__work_queue/cursor.h>

namespace asc_stl_b024_test {

CANN_ASC_STL_API int* values_data();

// AICore rejects static data members inside device functions, so the live
// count is caller-owned storage referenced by each instance.
struct b024_counter {
    int value;
    int* alive;
    CANN_ASC_STL_API b024_counter(int v, int* counter) : value(v), alive(counter)
    {
        ++*alive;
    }
    CANN_ASC_STL_API b024_counter(const b024_counter& other) : value(other.value), alive(other.alive)
    {
        ++*alive;
    }
    CANN_ASC_STL_API b024_counter(b024_counter&& other) noexcept : value(other.value), alive(other.alive)
    {
        ++*alive;
    }
    CANN_ASC_STL_API b024_counter& operator=(const b024_counter&) = default;
    CANN_ASC_STL_API b024_counter& operator=(b024_counter&&) = default;
    CANN_ASC_STL_API ~b024_counter()
    {
        --*alive;
    }
};

struct b024_lifetime_counter {
    int* destructions;
    CANN_ASC_STL_API explicit b024_lifetime_counter(int* counter) : destructions(counter)
    {}
    CANN_ASC_STL_API b024_lifetime_counter(const b024_lifetime_counter& other) : destructions(other.destructions)
    {}
    CANN_ASC_STL_API ~b024_lifetime_counter()
    {
        ++*destructions;
    }
};

struct b024_self_move_counter {
    int value;
    int* self_moves;
    CANN_ASC_STL_API b024_self_move_counter(int v, int* counter) : value(v), self_moves(counter)
    {}
    CANN_ASC_STL_API b024_self_move_counter(const b024_self_move_counter&) = default;
    CANN_ASC_STL_API b024_self_move_counter(b024_self_move_counter&&) = default;
    CANN_ASC_STL_API b024_self_move_counter& operator=(b024_self_move_counter&& other) noexcept
    {
        if (this == &other) {
            ++*self_moves;
            value = -1;
        } else {
            value = other.value;
            self_moves = other.self_moves;
        }
        return *this;
    }
};

struct b024_seed_sequence {
    using result_type = unsigned int;
    CANN_ASC_STL_API result_type operator()()
    {
        return 123456789u;
    }
};

CANN_ASC_STL_API int evaluate_algorithms()
{
    int values[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int sum = 0;
    auto consumer = [&sum](int value) { sum += value; };
    const auto returned = asc::std::for_each_n(values, 4, consumer);
    if (returned != values + 4) {
        return 1;
    }
    if (sum != 0) {
        return 2;
    }
    int generated[5] = {0, 0, 0, 0, 0};
    int next = 1;
    const auto generator = [&next]() {
        const int current = next;
        next *= 2;
        return current;
    };
    if (asc::std::generate_n(generated, 5, generator) != generated + 5) {
        return 3;
    }
    for (int index = 0; index < 5; ++index) {
        if (generated[index] != (1 << index)) {
            return 4;
        }
    }
    const int left[4] = {1, 2, 3, 4};
    const int right_a[4] = {4, 3, 2, 1};
    const int right_b[4] = {1, 2, 3, 5};
    if (!asc::std::is_permutation(left, left + 4, right_a)) {
        return 5;
    }
    if (asc::std::is_permutation(left, left + 4, right_b)) {
        return 6;
    }
    if (!asc::std::is_permutation(left, left + 4, right_a, right_a + 4)) {
        return 7;
    }
    if (asc::std::is_permutation(left, left + 4, right_b, right_b + 4)) {
        return 8;
    }
    const bool predicated = asc::std::is_permutation(left, left + 4, right_a, [](int a, int b) { return a == b; });
    if (!predicated) {
        return 9;
    }
    const int partitioned[6] = {1, 3, 5, 2, 4, 6};
    const auto* split_point = asc::std::partition_point(partitioned, partitioned + 6, [](int v) { return v % 2 == 1; });
    if (split_point != partitioned + 3) {
        return 10;
    }
    const auto* empty_point = asc::std::partition_point(partitioned, partitioned, [](int) { return true; });
    if (empty_point != partitioned) {
        return 11;
    }
    // ranges::iota_view: bounded form exposes values/size/random-access category;
    // the single-argument form defaults to an unbounded range.
    {
        auto bounded = asc::std::ranges::views::iota(0, 5);
        int probed[5]{};
        int index = 0;
        for (auto value : bounded) {
            probed[index++] = value;
        }
        int mismatched = (index != 5);
        for (int i = 0; i < 5; ++i) {
            mismatched += probed[i] != i;
        }
        if (mismatched != 0 || bounded.size() != 5) {
            return 13;
        }
        auto unbounded = asc::std::ranges::iota_view<int>{};
        auto cursor = unbounded.begin();
        if (*cursor != 0) {
            return 14;
        }
        ++cursor;
        if (*cursor != 1) {
            return 14;
        }
    }
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    static_assert(asc::std::ranges::random_access_range<asc::std::ranges::iota_view<int, int>>);
    static_assert(asc::std::ranges::sized_range<asc::std::ranges::iota_view<int, int>>);
#endif
    // counted_iterator sentinel subtraction direction: iterator minus sentinel is -count.
    {
        int storage[4]{};
        asc::std::counted_iterator<int*> counter(storage, 3);
        const auto difference = asc::std::default_sentinel - counter;
        if (difference != 3 || (counter - asc::std::default_sentinel) != -3) {
            return 15;
        }
    }
    asc::std::iota(values, values + 8, 3);
    for (int index = 0; index < 8; ++index) {
        if (values[index] != 3 + index) {
            return 12;
        }
    }
    int scanned[5] = {0, 0, 0, 0, 0};
    const auto doubled = [](int v) { return v * 2; };
    const auto plus = [](int a, int b) { return a + b; };
    if (asc::std::transform_exclusive_scan(values, values + 5, scanned, 10, plus, doubled) != scanned + 5) {
        return 13;
    }
    if (scanned[0] != 10 || scanned[1] != 16 || scanned[2] != 24 || scanned[3] != 34 || scanned[4] != 46) {
        return 14;
    }
    if (asc::std::transform_exclusive_scan(values, values, scanned, 7, plus, doubled) != scanned) {
        return 15;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_ranges_for_each()
{
    int values[5] = {1, 2, 3, 4, 5};
    int visits = 0;
    int projected_sum = 0;
    const auto result = asc::std::ranges::for_each(values, values + 5, [&](int v) {
        ++visits;
        projected_sum += v;
    });
    if (visits != 5 || projected_sum != 15 || result.in != values + 5) {
        return 1;
    }
    visits = 0;
    int doubled_visits = 0;
    asc::std::ranges::for_each(values, values + 5, [&](int v) {
        ++visits;
        doubled_visits += v * 2;
    });
    if (visits != 5 || doubled_visits != 30) {
        return 2;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_chrono()
{
    namespace chrono = asc::std::chrono;
    const chrono::sys_days first_monday_2026(chrono::year(2026) / chrono::January / chrono::day(5u));
    const chrono::year_month_weekday round(first_monday_2026);
    if (round.year() != chrono::year(2026) || round.month() != chrono::January) {
        return 1;
    }
    if (round.weekday() != chrono::Monday || round.index() != 1u || round.weekday_indexed() != chrono::Monday[1]) {
        return 2;
    }
    if (!round.ok()) {
        return 3;
    }
    const chrono::local_days local(first_monday_2026.time_since_epoch());
    const chrono::year_month_weekday from_local(local);
    if (from_local.index() != 1u || from_local.weekday() != chrono::Monday) {
        return 4;
    }
    auto shifted = round;
    shifted += chrono::months(13);
    if (shifted.year() != chrono::year(2027) || shifted.month() != chrono::February) {
        return 5;
    }
    shifted -= chrono::years(1);
    if (shifted.year() != chrono::year(2026) || shifted.month() != chrono::February) {
        return 6;
    }
    const chrono::year_month_weekday_last last_sunday(
        chrono::year(2026), chrono::December, chrono::Sunday[chrono::last]);
    if (!last_sunday.ok() || last_sunday.weekday() != chrono::Sunday ||
        last_sunday.weekday_last().weekday() != chrono::Sunday) {
        return 7;
    }
    auto last_shifted = last_sunday;
    last_shifted += chrono::months(1);
    if (last_shifted.year() != chrono::year(2027) || last_shifted.month() != chrono::January) {
        return 8;
    }
    last_shifted -= chrono::years(2);
    if (last_shifted.year() != chrono::year(2025)) {
        return 9;
    }
    const chrono::year_month_weekday fifth_monday(chrono::year(2026), chrono::February, chrono::Monday[5]);
    if (fifth_monday.ok()) {
        return 10;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_expected()
{
    const asc::std::expected<int, int> ok(42);
    const asc::std::expected<int, int> bad(asc::std::unexpect, 7);
    if (!static_cast<bool>(ok) || static_cast<bool>(bad) || !ok.has_value() || bad.has_value()) {
        return 1;
    }
    if (*ok != 42 || ok.value_or(5) != 42 || bad.value_or(5) != 5) {
        return 2;
    }
    if (bad.error() != 7 || ok.error_or(-1) != -1 || bad.error_or(-1) != 7) {
        return 3;
    }
    if (ok.operator->() == nullptr || *ok.operator->() != 42) {
        return 4;
    }
    const auto doubled = ok.transform([](int v) { return v * 2; });
    if (!doubled.has_value() || *doubled != 84) {
        return 5;
    }
    const auto failed_transform = bad.transform([](int v) { return v * 2; });
    if (failed_transform.has_value() || failed_transform.error() != 7) {
        return 6;
    }
    const auto chained = ok.and_then([](int v) { return asc::std::expected<int, int>(v + 1); });
    if (!chained.has_value() || *chained != 43) {
        return 7;
    }
    const auto recovered = bad.or_else([](int) { return asc::std::expected<int, int>(99); });
    if (!recovered.has_value() || *recovered != 99) {
        return 8;
    }
    const auto tagged = bad.transform_error([](int e) { return e * 10; });
    if (tagged.has_value() || tagged.error() != 70) {
        return 9;
    }
    const asc::std::expected<int, int> copied(ok);
    if (!copied.has_value() || *copied != 42) {
        return 10;
    }
    const asc::std::expected<int, int> second_bad(asc::std::unexpect, 3);
    if (second_bad.has_value() || second_bad.error() != 3) {
        return 11;
    }
    const auto error_mapped = second_bad.transform([](int value) { return value + 1; });
    if (error_mapped.has_value() || error_mapped.error() != 3) {
        return 12;
    }
    const auto error_preserved =
        second_bad.or_else([](int e) { return asc::std::expected<int, int>(asc::std::unexpect, e); });
    if (error_preserved.has_value() || error_preserved.error() != 3) {
        return 13;
    }
    int value_destructions = 0;
    b024_lifetime_counter value_source(&value_destructions);
    {
        const asc::std::expected<b024_lifetime_counter, int> tracked(value_source);
        if (!tracked.has_value()) {
            return 14;
        }
    }
    if (value_destructions != 1) {
        return 15;
    }
    int error_destructions = 0;
    b024_lifetime_counter error_source(&error_destructions);
    {
        const asc::std::expected<int, b024_lifetime_counter> tracked(asc::std::unexpect, error_source);
        if (tracked.has_value()) {
            return 16;
        }
    }
    if (error_destructions != 1) {
        return 17;
    }
    int copied_error_destructions = 0;
    b024_lifetime_counter copied_error_source(&copied_error_destructions);
    {
        const asc::std::expected<long, b024_lifetime_counter> tracked(asc::std::unexpect, copied_error_source);
        const asc::std::expected<long, b024_lifetime_counter> copied_error(tracked);
        if (tracked.has_value() || copied_error.has_value()) {
            return 18;
        }
    }
    if (copied_error_destructions != 2) {
        return 19;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_inplace_vector()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.empty() || values.capacity() != 4u || values.max_size() != 4u || values.size() != 0u) {
        return 1;
    }
    const auto first = values.try_push_back(1);
    if (!first.has_value() || *first != 1 || values.front() != 1 || values.back() != 1) {
        return 2;
    }
    values.unchecked_push_back(2);
    const auto moved = values.try_push_back(3);
    values.unchecked_emplace_back(4);
    if (!moved.has_value() || values.size() != 4u || values.data()[3] != 4) {
        return 3;
    }
    if (values.try_push_back(5).has_value() || values.try_emplace_back(6).has_value()) {
        return 4;
    }
    if (values.cbegin() != values.data() || values.cend() != values.data() + 4) {
        return 5;
    }
    values.erase(values.begin());
    if (values.size() != 3u || values[0] != 2) {
        return 6;
    }
    const auto removed = values.erase_if([](int v) { return v == 3; });
    if (removed != 1u || values.size() != 2u) {
        return 7;
    }
    asc::std::inplace_vector<int, 4> copy(values);  // NOLINT(build/include_what_you_use)
    if (copy.size() != 2u || copy.front() != 2 || copy.back() != 4) {
        return 8;
    }
    asc::std::inplace_vector<int, 4> grown;
    grown.try_push_back(7);
    grown.try_push_back(8);
    grown.try_push_back(9);
    grown.swap(copy);
    if (grown.size() != 2u || copy.size() != 3u || copy.back() != 9 || grown.front() != 2) {
        return 9;
    }
    copy.pop_back();
    copy.clear();
    if (!copy.empty() || copy.size() != 0u) {
        return 10;
    }
    asc::std::inplace_vector<int, 0> zero;
    if (!zero.empty() || zero.try_push_back(1).has_value() || zero.data() != nullptr) {
        return 11;
    }
    bool called = false;
    const auto zero_removed = zero.erase_if([&called](int) {
        called = true;
        return true;
    });
    if (zero_removed != 0 || called) {
        return 18;
    }
    {
        int alive = 0;
        asc::std::inplace_vector<b024_counter, 2> objects;
        objects.try_emplace_back(1, &alive);
        objects.try_emplace_back(2, &alive);
        if (alive != 2) {
            return 12;
        }
        if (objects.try_emplace_back(3, &alive).has_value()) {
            return 13;
        }
        objects.erase(objects.begin());
        if (alive != 1 || objects.front().value != 2) {
            return 14;
        }
        const auto move_assigned = objects.try_push_back(b024_counter(5, &alive));
        if (!move_assigned.has_value() || alive != 2) {
            return 15;
        }
    }
    {
        int self_moves = 0;
        asc::std::inplace_vector<b024_self_move_counter, 3> objects;
        objects.try_emplace_back(1, &self_moves);
        objects.try_emplace_back(2, &self_moves);
        objects.try_emplace_back(3, &self_moves);
        const auto returned = objects.erase(objects.begin() + 1, objects.begin() + 1);
        if (returned != objects.begin() + 1 || objects.size() != 3u || self_moves != 0) {
            return 16;
        }
        if (objects[0].value != 1 || objects[1].value != 2 || objects[2].value != 3) {
            return 17;
        }
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_random_and_traits()
{
    asc::std::minstd_rand0 engine;
    if (engine() != 16807u || engine() != 282475249u) {
        return 1;
    }
    asc::std::minstd_rand0 reset;
    reset.discard(2);
    if (!(reset == engine) || reset == asc::std::minstd_rand0{}) {
        return 2;
    }
    reset.seed(1);
    if (!(reset == asc::std::minstd_rand0(1)) || reset() != 16807u) {
        return 3;
    }
    if (asc::std::minstd_rand0::min() != 1u || asc::std::minstd_rand0::max() != 2147483646u) {
        return 4;
    }
    if (asc::std::minstd_rand0::multiplier != 16807u || asc::std::minstd_rand0::increment != 0u ||
        asc::std::minstd_rand0::modulus != 2147483647u || asc::std::minstd_rand0::default_seed != 1u) {
        return 5;
    }
    b024_seed_sequence sequence;
    asc::std::linear_congruential_engine<unsigned, 48271u, 0u, 2147483647u> seeded(sequence);
    if (seeded() != (48271ull * 123456789ull) % 2147483647ull) {
        return 6;
    }
    asc::detail::pcg64_engine pcg_a;
    asc::detail::pcg64_engine pcg_b;
    const auto pcg_first = pcg_a();
    pcg_b.discard(1);
    const auto pcg_second = pcg_a();
    if (pcg_second != pcg_b() || pcg_first == pcg_second || !pcg_a.equal(pcg_b)) {
        return 7;
    }
    if (!asc::std::__asc_internal::__is_non_narrowing_convertible<long, int>::value) {
        return 8;
    }
    if (asc::std::__asc_internal::__is_non_narrowing_convertible<int, long>::value) {
        return 9;
    }
    if (!asc::std::__asc_internal::__is_non_narrowing_convertible<double, float>::value) {
        return 10;
    }
    if (asc::std::__asc_internal::__is_non_narrowing_convertible<float, double>::value) {
        return 11;
    }
    if (!asc::std::__asc_internal::__is_non_narrowing_convertible<int, int>::value) {
        return 12;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_memory_and_support()
{
    long storage[4] = {0, 0, 0, 0};
    const asc::std::allocation_result<long*, asc::std::size_t> result{storage, 4u};
    if (result.ptr != storage || result.count != 4u) {
        return 1;
    }
    int value = 8;
    const asc::std::optional<int&> borrowed(value);
    const asc::std::optional<int&> empty_optional;
    if (!borrowed.has_value() || empty_optional.has_value() || *borrowed != 8 || borrowed.operator->() != &value) {
        return 2;
    }
    *borrowed = 12;
    if (value != 12) {
        return 3;
    }
    const asc::std::optional<int&> rebinding(value);
    asc::std::optional<int&> assigned(asc::std::nullopt);
    assigned = rebinding;
    if (!assigned.has_value() || *assigned != 12) {
        return 4;
    }
    assigned = asc::std::nullopt;
    if (assigned.has_value()) {
        return 5;
    }
    if (!asc::detail::buffer_alignment_valid(32u) || asc::detail::buffer_alignment_valid(48u)) {
        return 6;
    }
    if (asc::detail::buffer_element_bytes(4u, 10u) != 40u) {
        return 7;
    }
    asc::detail::buffer_state buffer_state(storage, sizeof(storage), alignof(long));
    if (!buffer_state.owns || buffer_state.release() != storage || buffer_state.owns) {
        return 8;
    }
    if (asc::std::detail::intmax_abs(-5) != 5 || asc::std::detail::intmax_abs(5) != 5) {
        return 9;
    }
    if (!asc::std::detail::intmax_abs_representable(0) ||
        asc::std::detail::intmax_abs_representable(asc::std::detail::intmax_min())) {
        return 10;
    }
    if (asc::std::detail::intmax_max() != __INT64_MAX__) {
        return 11;
    }
    if (!asc::detail::math_is_nan(asc::detail::math_quiet_nan()) || asc::detail::math_is_nan(0.0f)) {
        return 12;
    }
    if (!asc::detail::math_is_inf(asc::detail::math_infinity()) || asc::detail::math_is_inf(1.0f)) {
        return 13;
    }
    if (!asc::detail::math_sign_bit(-0.0f) || !asc::detail::math_sign_bit(-1.0f) || asc::detail::math_sign_bit(1.0f)) {
        return 14;
    }
    if (asc::detail::math_round_preserve_zero(-0.0f) != 0.0f ||
        !asc::detail::math_sign_bit(asc::detail::math_round_preserve_zero(-0.0f))) {
        return 15;
    }
    if (asc::detail::math_round_preserve_zero(2.7f) != 2.0f || asc::detail::math_round_preserve_zero(-2.7f) != -2.0f) {
        return 16;
    }
    asc::detail::iterator_adaptor_state<int*> adaptor(values_data());
    if (adaptor.advanced(2) != values_data() + 2 || adaptor.offset != 0) {
        return 17;
    }
    if (asc::detail::adaptor_remaining(2, 7) != 5 || asc::detail::adaptor_remaining(9, 7) != 0) {
        return 18;
    }
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // Host: the serialized claim tiles the range exactly.  Device claim
    // coverage runs from the runtime payload with GM-backed cursor storage.
    asc::detail::work_cursor cursor(0, 10, 4);
    __UINT64_TYPE__ claimed_begin = 0;
    __UINT64_TYPE__ claimed_end = 0;
    if (!cursor.try_claim(claimed_begin, claimed_end) || claimed_begin != 0 || claimed_end != 4) {
        return 19;
    }
    if (!cursor.try_claim(claimed_begin, claimed_end) || claimed_begin != 4 || claimed_end != 8) {
        return 20;
    }
    if (!cursor.try_claim(claimed_begin, claimed_end) || claimed_begin != 8 || claimed_end != 10) {
        return 21;
    }
    if (cursor.try_claim(claimed_begin, claimed_end)) {
        return 22;
    }
#endif
    return 0;
}

CANN_ASC_STL_API int evaluate_iterator_facade()
{
    int values[4] = {4, 1, 3, 2};
    if (asc::std::size(values) != 4u || asc::std::empty(values) || asc::std::data(values) != values) {
        return 1;
    }
    if (asc::std::begin(values) != values || asc::std::end(values) != values + 4 ||
        asc::std::cbegin(values) != values) {
        return 2;
    }
    if (asc::std::ssize(values) != 4) {
        return 3;
    }
    auto reversed = asc::std::rbegin(values);
    if (*reversed != 2) {
        return 4;
    }
    ++reversed;
    if (*reversed != 3) {
        return 5;
    }
    const int const_values[4] = {4, 1, 3, 2};
    if (asc::std::crbegin(const_values) != asc::std::rbegin(const_values) ||
        asc::std::crend(const_values) != asc::std::rend(const_values)) {
        return 6;
    }
    const asc::std::move_iterator<int*> moved(asc::std::begin(values));
    if (*moved != 4 || moved.base() != asc::std::begin(values)) {
        return 7;
    }
    asc::std::move_sentinel<int*> sentinel(asc::std::end(values));
    if (sentinel.base() != asc::std::end(values)) {
        return 8;
    }
    asc::std::counted_iterator<int*> counted(asc::std::begin(values), 4);
    if (counted.count() != 4 || *counted != 4) {
        return 9;
    }
    ++counted;
    if (counted.count() != 3 || *counted != 1) {
        return 10;
    }
    if (asc::std::distance(asc::std::begin(values), asc::std::end(values)) != 4) {
        return 11;
    }
    auto advanced = asc::std::begin(values);
    asc::std::advance(advanced, 2);
    if (advanced != values + 2 || *asc::std::next(advanced) != 2 || *asc::std::prev(advanced) != 1) {
        return 12;
    }
    const asc::std::common_iterator<int*, const int*> common(asc::std::begin(values));
    if (*common != 4) {
        return 13;
    }
    asc::std::iterator_traits<int*>::difference_type difference = 2;
    if (difference != 2) {
        return 14;
    }
    int swapped_a = 1;
    int swapped_b = 2;
    asc::std::iter_swap(&swapped_a, &swapped_b);
    if (swapped_a != 2 || swapped_b != 1) {
        return 15;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate_variant_comparison()
{
    const asc::std::variant<int, long> left(7);
    const asc::std::variant<int, long> right(7);
    const asc::std::variant<int, long> other(9L);
    if (!(left == right) || left == other || left != right) {
        return 1;
    }
    if (left < right || other < left || !(left < other)) {
        return 2;
    }
    if (left > other || !(other > left) || !(left <= right) || !(left >= right)) {
        return 3;
    }
    return 0;
}

CANN_ASC_STL_API int evaluate()
{
    const int results[8] = {
        evaluate_algorithms(),
        evaluate_ranges_for_each(),
        evaluate_chrono(),
        evaluate_expected(),
        evaluate_inplace_vector(),
        evaluate_random_and_traits(),
        evaluate_memory_and_support(),
        evaluate_iterator_facade(),
    };
    for (int index = 0; index < 8; ++index) {
        if (results[index] != 0) {
            return 100 + index * 100 + results[index];
        }
    }
    if (evaluate_variant_comparison() != 0) {
        return 1000 + evaluate_variant_comparison();
    }
    return 0;
}

}  // namespace asc_stl_b024_test

CANN_ASC_STL_API int* asc_stl_b024_test::values_data()
{
    static int shared_values[6] = {0, 1, 2, 3, 4, 5};
    return shared_values;
}

#endif  // ASC_STL_TEST_B024_SEMANTICS_H
