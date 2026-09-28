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

#ifndef ASC_STL_TEST_B017_SEMANTICS_H
#define ASC_STL_TEST_B017_SEMANTICS_H
#include <asc/std/__algorithm/copy_n.h>
#include <asc/std/__algorithm/equal.h>
#include <asc/std/__algorithm/move.h>
#include <asc/std/__algorithm/ranges_find_if_not.h>
#include <asc/std/__algorithm/ranges_min.h>
#include <asc/std/__algorithm/ranges_min_element.h>
#include <asc/std/__algorithm/swap_ranges.h>
#include <asc/std/__optional/make_optional.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/atomic>
#include <asc/std/complex>
#include <asc/std/ctgmath>
#include <asc/warp>

namespace asc_stl_b017_test {
struct greater_than_two {
    CANN_ASC_STL_API constexpr bool operator()(int value) const noexcept
    {
        return value > 2;
    }
};

CANN_ASC_STL_API int evaluate_common() noexcept
{
    int failures = 0;
    int source[] = {1, 2, 3, 4};
    int copied[] = {0, 0, 0, 0};
    asc::std::copy_n(source, 4, copied);
    failures += !asc::std::equal(source, source + 4, copied);
    int moved[] = {0, 0, 0, 0};
    asc::std::move(copied, copied + 4, moved);  // NOLINT(build/include_what_you_use)
    failures += !asc::std::equal(source, source + 4, moved);
    int replacement[] = {5, 6, 7, 8};
    asc::std::swap_ranges(moved, moved + 4, replacement);
    failures += moved[0] != 5 || replacement[3] != 4;
    failures += asc::std::find_if_not(source, source + 4, greater_than_two{}) != source;

    asc::std::optional<int> value(3);
    failures += !value || *value != 3 || value.value_or(9) != 3;
    value.emplace(7);
    failures += value.has_value() == false || *value != 7;
    asc::std::optional<int> empty;
    failures += empty.value_or(11) != 11 || !(empty < value);
    empty = value;
    failures += empty != value;
    empty.reset();
    failures += static_cast<bool>(empty);
    const auto made = asc::std::make_optional(13);
    failures += !made || *made != 13;

    asc::std::complex<float> left(1.0F, 2.0F);
    asc::std::complex<float> right(3.0F, -1.0F);
    const auto sum = left + right;
    failures += sum.real() != 4.0F || sum.imag() != 1.0F;
    failures += asc::std::norm(left) != 5.0F;

    int array[] = {1};
    failures += asc::std::ranges::empty(array);
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    int atomic_value = 0;
    asc::std::atomic_ref<int> reference(atomic_value);
    failures += !reference.is_always_lock_free || !reference.is_lock_free();
    int expected = 0;
    failures += !reference.compare_exchange_weak(expected, 1, asc::std::memory_order_relaxed);
#endif
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    failures += asc::std::ranges::find_if_not(source, source + 4, greater_than_two{}) != source;
    failures += asc::std::ranges::min(4, 2) != 2;
    failures += asc::std::ranges::min_element(source, source + 4) != source;
#endif
    return failures;
}
}  // namespace asc_stl_b017_test
#endif  // ASC_STL_TEST_B017_SEMANTICS_H
