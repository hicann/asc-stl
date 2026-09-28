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
#include <asc/__numeric/checked.h>

#include <cassert>
#include <limits>

int main()
{
    constexpr int int_max = std::numeric_limits<int>::max();
    constexpr int int_min = std::numeric_limits<int>::min();

    auto wrapped = asc::detail::add_overflow_impl(int_max, 1);
    assert(wrapped.overflow && wrapped.value == int_min);
    wrapped = asc::detail::add_overflow_impl(int_min, -1);
    assert(wrapped.overflow && wrapped.value == int_max);
    auto plain = asc::detail::add_overflow_impl(40, 2);
    assert(!plain.overflow && plain.value == 42);

    auto subtracted = asc::detail::sub_overflow_impl(int_min, 1);
    assert(subtracted.overflow && subtracted.value == int_max);
    subtracted = asc::detail::sub_overflow_impl(int_max, -1);
    assert(subtracted.overflow);

    auto multiplied = asc::detail::mul_overflow_impl(30000, 40000);
    assert(!multiplied.overflow && multiplied.value == 1200000000);
    multiplied = asc::detail::mul_overflow_impl(100000, 100000);
    assert(multiplied.overflow);
    multiplied = asc::detail::mul_overflow_impl(int_min, -1);
    assert(multiplied.overflow);

    auto divided = asc::detail::div_overflow_impl(5, 0);
    assert(divided.overflow);
    divided = asc::detail::div_overflow_impl(int_min, -1);
    assert(divided.overflow);
    divided = asc::detail::div_overflow_impl(-42, 7);
    assert(!divided.overflow && divided.value == -6);

    auto saturated_high = asc::detail::saturating_add_impl(int_max, 1);
    assert(saturated_high.overflow && saturated_high.value == int_max);
    auto saturated_low = asc::detail::saturating_add_impl(int_min, -1);
    assert(saturated_low.overflow && saturated_low.value == int_min);
    auto saturating_mul_high = asc::detail::saturating_mul_impl(0x10000, 0x10000);
    assert(saturating_mul_high.overflow && saturating_mul_high.value == int_max);
    auto saturating_mul_low = asc::detail::saturating_mul_impl(-0x10000, 0x10000);
    assert(saturating_mul_low.overflow && saturating_mul_low.value == int_min);
    auto saturating_div = asc::detail::saturating_div_impl(int_min, -1);
    assert(saturating_div.overflow && saturating_div.value == int_max);
    auto saturating_sub = asc::detail::saturating_sub_impl(int_min, 1);
    assert(saturating_sub.overflow && saturating_sub.value == int_min);

    auto unsigned_checked = asc::detail::add_overflow_impl(0xFFFFFFFFu, 1u);
    assert(unsigned_checked.overflow && unsigned_checked.value == 0u);

    constexpr auto constant_evaluated = asc::detail::add_overflow_impl(40, 2);
    static_assert(!constant_evaluated.overflow && constant_evaluated.value == 42);
    return 0;
}
