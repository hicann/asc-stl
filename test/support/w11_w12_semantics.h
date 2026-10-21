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

#ifndef ASC_STL_TEST_W11_W12_SEMANTICS_H
#define ASC_STL_TEST_W11_W12_SEMANTICS_H

#include <asc/__detail/attributes.h>
#include <asc/argument>
#include <asc/functional>
#include <asc/numeric>
#include <asc/random>
#include <asc/type_traits>
#include <asc/version>
#include <asc/std/algorithm>
#include <asc/std/charconv>
#include <asc/std/cinttypes>
#include <asc/std/cuchar>
#include <asc/std/cwctype>
#include <asc/std/expected>
#include <asc/std/format>
#include <asc/std/ranges>

#include "expected_monad_regression.h"

namespace asc_stl_w11_w12_test {

struct even {
    CANN_ASC_STL_API constexpr bool operator()(int value) const noexcept
    {
        return (value & 1) == 0;
    }
};
struct times_two {
    CANN_ASC_STL_API constexpr int operator()(int value) const noexcept
    {
        return value * 2;
    }
};

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_sort()
{
    int values[] = {5, 1, 4, 2, 3};
    asc::std::sort(values, values + 5);  // NOLINT(build/include_what_you_use)
    return values[0] != 1 || values[4] != 5;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_nth_and_stable()
{
    unsigned int failures = 0;
    int values[] = {5, 1, 4, 2, 3};
    asc::std::nth_element(values, values + 2, values + 5);
    failures += values[2] != 3 || values[0] > values[2] || values[1] > values[2] || values[3] < values[2] ||
        values[4] < values[2];
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    int stable[] = {3, 1, 2, 1};
    asc::std::stable_sort(stable, stable + 4);  // NOLINT(build/include_what_you_use)
    failures += stable[0] != 1 || stable[3] != 3;
#endif
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_foundation()
{
    unsigned int failures = 0;
    asc::pcg64 engine;  // NOLINT(build/include_what_you_use)
#if defined(ASC_STL_W08_HARDWARE)
    engine.discard(9999);
    const unsigned long long random_value = engine();
    failures += random_value != 11135645891219275043ULL;
#else
    const unsigned long long random_value = engine();
    failures += random_value != 14951315693135216709ULL;
#endif
    asc::std::expected<int, int> expected(7);
    failures += !expected || *expected != 7;
    failures += asc_stl_expected_monad_test::evaluate();
    failures += asc::saturating_add(2147483647, 1) != 2147483647;
    failures += !asc::add_overflow(2147483647, 1).overflow;
    failures += asc::saturating_sub(0U, 1U) != 0U || asc::saturating_mul(~0U, 2U) != ~0U;
    failures += asc::mul_overflow(0x80000000U, 1U).overflow || asc::div_overflow(0x80000000U, ~0U).overflow;
#if CANN_ASC_STL_DETAIL_HAS_CONSTEVAL()
    char text[16]{};
    auto* text_end = asc::std::format_to(text, "{:x}", 255);
    failures += text_end - text != 2 || text[0] != 'f' || text[1] != 'f';
#else
    char text[3]{};
    const auto rendered = asc::std::__format_detail::render_unchecked(text, 3, "{:x}", 4, 255);
    failures += rendered.total != 2 || text[0] != 'f' || text[1] != 'f';
#endif
    char digits[8]{};
    const auto to_result = asc::std::to_chars(digits, digits + 8, 31, 16);
    int parsed = 0;
    const auto from_result = asc::std::from_chars(digits, to_result.ptr, parsed, 16);
    failures += parsed != 31 || from_result.ptr != to_result.ptr;
    char too_small[1]{};
    const auto too_small_result = asc::std::to_chars(too_small, too_small + 1, 42);
    failures += too_small_result.ptr != too_small + 1 || too_small_result.ec != asc::std::errc::value_too_large;
    int unchanged = 19;
    const char plus[] = {'+', '1'};
    const auto invalid_result = asc::std::from_chars(plus, plus + 2, unchanged);
    failures += invalid_result.ptr != plus || invalid_result.ec != asc::std::errc::invalid_argument || unchanged != 19;
    const char overflow[] = {'2', '1', '4', '7', '4', '8', '3', '6', '4', '8'};
    const auto overflow_result = asc::std::from_chars(overflow, overflow + 10, unchanged);
    failures += overflow_result.ptr != overflow + 10 || overflow_result.ec != asc::std::errc::result_out_of_range ||
        unchanged != 19;
    asc::std::mbstate_t state{};
    char encoded[2] = {};
    char32_t decoded = U'!';
    failures += asc::std::c32rtomb(encoded, U'A', &state) != 1 || encoded[0] != 'A';
    failures += asc::std::mbrtoc32(&decoded, encoded, 1, &state) != 1 || decoded != U'A';
    failures += asc::std::mbrtoc32(nullptr, encoded, 0, &state) != static_cast<__SIZE_TYPE__>(-2);
    failures += asc::std::mbrtoc32(&decoded, nullptr, 0, &state) != 0 || decoded != U'\0';
    failures += asc::std::c16rtomb(nullptr, u'A', nullptr) != 1;
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    const char invalid[] = {static_cast<char>(0x80), '\0'};
    failures += asc::std::mbrtoc32(&decoded, invalid, 1, &state) != static_cast<__SIZE_TYPE__>(-1);
    failures += asc::std::c32rtomb(encoded, U'\u0080', &state) != static_cast<__SIZE_TYPE__>(-1);
#endif
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
    char8_t decoded8 = u8'!';
    failures += asc::std::c8rtomb(encoded, u8'A', &state) != 1 || encoded[0] != 'A';
    failures += asc::std::mbrtoc8(&decoded8, encoded, 1, &state) != 1 || decoded8 != u8'A';
#endif
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_ranges_and_vocabulary()
{
    unsigned int failures = 0;
    int values[] = {1, 2, 3, 4, 5};
    auto selected = values | asc::std::ranges::views::filter(even{});
    int sum = 0;
    for (int value : selected)
        sum += value;
    failures += sum != 6;
    auto transformed = values | asc::std::ranges::views::drop(1) | asc::std::ranges::views::take(2) |
        asc::std::ranges::views::transform(times_two{});
    failures += *transformed.begin() != 4;
    auto repeated = asc::std::ranges::views::repeat(9, 3);
    failures += repeated.size() != 3 || repeated.begin()[2] != 9;
    int second[] = {8, 7};
    auto zipped = asc::std::ranges::views::zip(values, second);
    failures += zipped.size() != 2;
    asc::args::immediate<int> immediate(4);
    failures += immediate.value() != 4 || asc::maximum<int>{}(2, 5) != 5;
    failures += !asc::is_bitwise_comparable_v<int> || CANN_ASC_STL_VERSION != 10000;
    failures += !asc::std::iswalpha(L'Q') || !asc::std::iswalnum(L'7') || !asc::std::iswblank(L' ') ||
        !asc::std::iswcntrl(L'\n') || !asc::std::iswdigit(L'4') || !asc::std::iswgraph(L'!') ||
        !asc::std::iswlower(L'a') || !asc::std::iswprint(L' ') || !asc::std::iswpunct(L'!') ||
        !asc::std::iswspace(L'\t') || !asc::std::iswupper(L'Z') || !asc::std::iswxdigit(L'F') ||
        asc::std::towlower(L'Q') != L'q' || asc::std::towupper(L'q') != L'Q';
    char alpha_name[] = {'a', 'l', 'p', 'h', 'a', '\0'};
    char lower_name[] = {'t', 'o', 'l', 'o', 'w', 'e', 'r', '\0'};
    const auto alpha_class = asc::std::wctype(alpha_name);
    const auto lower_transform = asc::std::wctrans(lower_name);
    failures += alpha_class == 0 || !asc::std::iswctype(L'K', alpha_class) || lower_transform == 0 ||
        asc::std::towctrans(L'K', lower_transform) != L'k';
    failures += asc::std::imaxabs(-7) != 7;
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_group(unsigned int group)
{
    if (group == 0) {
        return evaluate_sort();
    }
    if (group == 1) {
        return evaluate_nth_and_stable();
    }
    if (group == 2) {
        return evaluate_foundation();
    }
    return evaluate_ranges_and_vocabulary();
}

template <class ResultPointer>
CANN_ASC_STL_API unsigned int evaluate(ResultPointer result)
{
    unsigned int failures = 0;
    for (unsigned int group = 0; group < 4; ++group) {
        failures += evaluate_group(group);
    }
    result[61] = failures;
    return failures;
}

}  // namespace asc_stl_w11_w12_test

#endif  // ASC_STL_TEST_W11_W12_SEMANTICS_H
