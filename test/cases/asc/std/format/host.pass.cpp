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

#include <asc/numeric>
#include <asc/std/charconv>
#include <asc/std/cinttypes>
#include <asc/std/cuchar>
#include <asc/std/format>
#include <asc/std/numeric>
#include <asc/std/version>

namespace {

int check_charconv_integer_limits()
{
    constexpr long long minimum = -9223372036854775807LL - 1;
    constexpr unsigned long long maximum = 18446744073709551615ULL;

    const char min_text[] = "-9223372036854775808";
    char min_output[sizeof(min_text)]{};
    min_output[sizeof(min_text) - 1] = '!';
    const auto min_conversion = asc::std::to_chars(min_output, min_output + sizeof(min_text) - 1, minimum);
    if (min_conversion.ec != asc::std::errc{} || min_conversion.ptr != min_output + sizeof(min_text) - 1 ||
        min_output[sizeof(min_text) - 1] != '!') {
        return 20;
    }
    for (unsigned int index = 0; index + 1 < sizeof(min_text); ++index) {
        if (min_output[index] != min_text[index]) {
            return 21;
        }
    }
    long long parsed_min = 0;
    const auto min_parse = asc::std::from_chars(min_text, min_text + sizeof(min_text) - 1, parsed_min);
    if (min_parse.ec != asc::std::errc{} || min_parse.ptr != min_text + sizeof(min_text) - 1 || parsed_min != minimum) {
        return 22;
    }

    const char below_min[] = "-9223372036854775809x";
    long long unchanged = 17;
    const auto out_of_range = asc::std::from_chars(below_min, below_min + sizeof(below_min) - 1, unchanged);
    if (out_of_range.ec != asc::std::errc::result_out_of_range ||
        out_of_range.ptr != below_min + sizeof(below_min) - 2 || unchanged != 17) {
        return 23;
    }

    const char base36[] = "3W5E11264SGSF?";
    unsigned long long parsed_max = 0;
    const auto max_parse = asc::std::from_chars(base36, base36 + sizeof(base36) - 1, parsed_max, 36);
    if (max_parse.ec != asc::std::errc{} || max_parse.ptr != base36 + sizeof(base36) - 2 || parsed_max != maximum) {
        return 24;
    }
    return 0;
}

}  // namespace

int main()
{
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    static_assert(CANN_ASC_STL_DETAIL_HAS_CONSTEVAL());
    static_assert(CANN_ASC_STL_HAS_FORMAT);
    char output[32] = {};
    auto result = asc::std::format_to_n(output, 8, "{} {:x} {}", -42, 255U, true);
    if (result.size != 11 || result.out != output + 8)
        return 1;
    const char expected[] = "-42 ff t";
    for (int index = 0; index < 8; ++index)
        if (output[index] != expected[index])
            return 2;
    if (asc::std::formatted_size("{{{}}}", 'x') != 3)
        return 3;
    char full[32] = {};
    auto* full_end = asc::std::format_to(full, "{} {} {} {:X} {:o} {:b}", 'Q', "ok", false, 42, 8U, 5);
    const char full_expected[] = "Q ok false 2A 10 101";
    if (full_end - full != static_cast<int>(sizeof(full_expected) - 1))
        return 12;
    for (unsigned int index = 0; index + 1 < sizeof(full_expected); ++index)
        if (full[index] != full_expected[index])
            return 13;
    char untouched[3] = {'x', 'y', 'z'};
    const auto negative = asc::std::format_to_n(untouched, -4, "{}", 1234);
    if (negative.out != untouched || negative.size != 4 || untouched[0] != 'x' || untouched[1] != 'y' ||
        untouched[2] != 'z')
        return 14;
    const auto zero = asc::std::format_to_n(untouched, 0, "{}", "text");
    if (zero.out != untouched || zero.size != 4 || untouched[0] != 'x')
        return 15;
#else
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CONSTEVAL());
    static_assert(!CANN_ASC_STL_HAS_FORMAT);
#endif
    int sum = 0;
    if (!asc::add_overflow(2147483647, 1, sum) || sum != 0)
        return 4;
    if (asc::std::saturating_add(2147483647, 1) != 2147483647)
        return 5;
    if (asc::std::saturating_sub(-2147483647 - 1, 1) != -2147483647 - 1)
        return 6;
    if (asc::std::saturating_mul(100000, 100000) != 2147483647)
        return 7;
    if (asc::overflow_cast<unsigned char>(300).failed == false)
        return 8;
    const auto unsigned_product = asc::mul_overflow(0x80000000U, 1U);
    if (unsigned_product.failed || unsigned_product.value != 0x80000000U || !asc::mul_overflow(~0U, 2U).failed ||
        asc::std::saturating_mul(~0U, 2U) != ~0U || asc::std::saturating_sub(0U, 1U) != 0U ||
        asc::div_overflow(0x80000000U, ~0U).failed)
        return 19;
    char digits[24] = {};
    const auto converted = asc::std::to_chars(digits, digits + 24, -255, 16);
    if (converted.ec != asc::std::errc{} || converted.ptr - digits != 3)
        return 9;
    int parsed = 0;
    const auto parsed_result = asc::std::from_chars(digits, converted.ptr, parsed, 16);
    if (parsed_result.ec != asc::std::errc{} || parsed != -255)
        return 10;
    char short_buffer[1] = {};
    const auto short_result = asc::std::to_chars(short_buffer, short_buffer + 1, 99);
    if (short_result.ptr != short_buffer + 1 || short_result.ec != asc::std::errc::value_too_large)
        return 16;
    int unchanged = 7;
    const char invalid[] = "+3";
    const auto invalid_result = asc::std::from_chars(invalid, invalid + 2, unchanged);
    if (invalid_result.ptr != invalid || invalid_result.ec != asc::std::errc::invalid_argument || unchanged != 7)
        return 17;
    const char overflow[] = "2147483648";
    const auto overflow_result = asc::std::from_chars(overflow, overflow + 10, unchanged);
    if (overflow_result.ptr != overflow + 10 || overflow_result.ec != asc::std::errc::result_out_of_range ||
        unchanged != 7)
        return 18;
    const int charconv_limits = check_charconv_integer_limits();
    if (charconv_limits != 0)
        return charconv_limits;
    if (asc::std::imaxabs(-9) != 9 || asc::std::imaxdiv(17, 5).rem != 2)
        return 11;
    return 0;
}
