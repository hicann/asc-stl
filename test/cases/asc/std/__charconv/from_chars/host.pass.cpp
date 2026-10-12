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

#include <asc/std/__charconv/from_chars.h>

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    // Successful parses consume the longest digit pattern of the base.
    std::int32_t value = 0;
    auto result = asc::std::from_chars("42", "42" + 2, value);
    assert(result.ec == asc::std::errc{} && result.ptr == "42" + 2 && value == 42);

    const char leading_space[] = " 42";
    result = asc::std::from_chars(leading_space, leading_space + 3, value);
    assert(result.ec == asc::std::errc::invalid_argument && result.ptr == leading_space && value == 42);

    const char leading_plus[] = "+42";
    result = asc::std::from_chars(leading_plus, leading_plus + 3, value);
    assert(result.ec == asc::std::errc::invalid_argument);

    const char non_digit[] = "xyz";
    result = asc::std::from_chars(non_digit, non_digit + 3, value);
    assert(result.ec == asc::std::errc::invalid_argument && result.ptr == non_digit);

    const char mixed[] = "12ab";
    result = asc::std::from_chars(mixed, mixed + 4, value);
    assert(result.ec == asc::std::errc{} && result.ptr == mixed + 2 && value == 12);

    // Negative values parse for signed types only.
    const char negative[] = "-7";
    result = asc::std::from_chars(negative, negative + 2, value);
    assert(result.ec == asc::std::errc{} && result.ptr == negative + 2 && value == -7);
    std::uint32_t unsigned_value = 0;
    result = asc::std::from_chars(negative, negative + 2, unsigned_value);
    assert(result.ec == asc::std::errc::invalid_argument);

    // Bases 2..36 round-trip; other bases are rejected.
    std::int64_t parsed = 0;
    result = asc::std::from_chars("ff", "ff" + 2, parsed, 16);
    assert(result.ec == asc::std::errc{} && parsed == 255);
    result = asc::std::from_chars("777", "777" + 3, parsed, 8);
    assert(result.ec == asc::std::errc{} && parsed == 511);
    result = asc::std::from_chars("z", "z" + 1, parsed, 36);
    assert(result.ec == asc::std::errc{} && parsed == 35);
    result = asc::std::from_chars("2", "2" + 1, parsed, 2);
    assert(result.ec == asc::std::errc::invalid_argument);
    result = asc::std::from_chars("1", "1" + 1, parsed, 1);
    assert(result.ec == asc::std::errc::invalid_argument);
    result = asc::std::from_chars("1", "1" + 1, parsed, 37);
    assert(result.ec == asc::std::errc::invalid_argument);

    // Overflow leaves the value untouched and reports result_out_of_range.
    std::int8_t small = 0;
    result = asc::std::from_chars("200", "200" + 3, small);
    assert(result.ec == asc::std::errc::result_out_of_range && small == 0 && result.ptr == "200" + 3);
    small = 7;
    result = asc::std::from_chars("128", "128" + 3, small);
    assert(result.ec == asc::std::errc::result_out_of_range && small == 7);
    result = asc::std::from_chars("-129", "-129" + 4, small);
    assert(result.ec == asc::std::errc::result_out_of_range && small == 7);
    result = asc::std::from_chars("-128", "-128" + 4, small);
    assert(result.ec == asc::std::errc{} && small == -128);

    std::uint64_t wide = 0;
    const char max_digits[] = "18446744073709551615";
    result = asc::std::from_chars(max_digits, max_digits + 20, wide);
    assert(result.ec == asc::std::errc{} && wide == std::numeric_limits<std::uint64_t>::max());
    const char overflow_digits[] = "18446744073709551616";
    result = asc::std::from_chars(overflow_digits, overflow_digits + 20, wide);
    assert(result.ec == asc::std::errc::result_out_of_range);

    // The three character types parse through their dedicated overloads.
    char character = 0;
    result = asc::std::from_chars("9", "9" + 1, character);
    assert(result.ec == asc::std::errc{} && character == 9);
    signed char signed_character = 0;
    result = asc::std::from_chars("9", "9" + 1, signed_character);
    assert(result.ec == asc::std::errc{} && signed_character == 9);
    unsigned char unsigned_character = 0;
    result = asc::std::from_chars("9", "9" + 1, unsigned_character);
    assert(result.ec == asc::std::errc{} && unsigned_character == 9);
    return 0;
}
