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

int main()
{
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
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
#endif
    int sum = 0;
    if (!asc::add_overflow(2147483647, 1, sum) || sum != static_cast<int>(0x80000000U))
        return 4;
    if (asc::saturating_add(2147483647, 1) != 2147483647)
        return 5;
    if (asc::saturating_sub(-2147483647 - 1, 1) != -2147483647 - 1)
        return 6;
    if (asc::saturating_mul(100000, 100000) != 2147483647)
        return 7;
    if (asc::overflow_cast<unsigned char>(300).overflow == false)
        return 8;
    const auto unsigned_product = asc::mul_overflow(0x80000000U, 1U);
    if (unsigned_product.overflow || unsigned_product.value != 0x80000000U || !asc::mul_overflow(~0U, 2U).overflow ||
        asc::saturating_mul(~0U, 2U) != ~0U || asc::saturating_sub(0U, 1U) != 0U ||
        asc::div_overflow(0x80000000U, ~0U).overflow)
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
    if (asc::std::imaxabs(-9) != 9 || asc::std::imaxdiv(17, 5).rem != 2)
        return 11;
    return 0;
}
