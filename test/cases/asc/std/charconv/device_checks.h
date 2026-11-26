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

#ifndef ASC_STL_TEST_CHARCONV_DEVICE_CHECKS_H
#define ASC_STL_TEST_CHARCONV_DEVICE_CHECKS_H

#include <asc/std/charconv>

namespace asc_stl_test_charconv {

template <class T>
CANN_ASC_STL_API bool matches(T input, int base, const char* expected, int length)
{
    char buffer[70];
    for (char& ch : buffer)
        ch = '!';
    auto end = asc::std::to_chars(buffer + 1, buffer + 1 + length, input, base);
    if (end.ec != asc::std::errc{} || end.ptr != buffer + 1 + length || buffer[0] != '!' || *end.ptr != '!')
        return false;
    for (int i = 0; i < length; ++i)
        if (buffer[i + 1] != expected[i])
            return false;
    T value{};
    auto parsed = asc::std::from_chars(expected, expected + length, value, base);
    return parsed.ec == asc::std::errc{} && parsed.ptr == expected + length && value == input;
}

CANN_ASC_STL_API int check(int seed = 7)
{
    namespace s = asc::std;
    if (!matches(0, 2, "0", 1) || !matches(-seed, 2, "-111", 4) || !matches(seed + 28, 36, "z", 1) ||
        !matches(0xffU, 16, "ff", 2) || !matches(-2147483647 - 1, 10, "-2147483648", 11) ||
        !matches(18446744073709551615ULL, 10, "18446744073709551615", 20))
        return 1;
    char bounded[] = {'a', 'b', 'c', 'd'};
    const auto too_short = s::to_chars(bounded + 1, bounded + 2, -seed);
    if (too_short.ptr != bounded + 2 || too_short.ec != s::errc::value_too_large || bounded[0] != 'a' ||
        bounded[2] != 'c')
        return 2;
    int value = 123;
    const char invalid[] = "+7";
    const auto none = s::from_chars(invalid, invalid + 2, value);
    if (none.ptr != invalid || none.ec != s::errc::invalid_argument || value != 123)
        return 3;
    const char overflow[] = "-21474836490x";
    const auto large = s::from_chars(overflow, overflow + 13, value);
    if (large.ptr != overflow + 12 || large.ec != s::errc::result_out_of_range || value != 123)
        return 4;
    const char upper[] = "Ffz";
    const auto partial = s::from_chars(upper, upper + 3, value, 16);
    if (partial.ptr != upper + 2 || partial.ec != s::errc{} || value != 255)
        return 5;
    auto flags = s::chars_format::fixed;
    flags |= s::chars_format::scientific;
    if (flags != s::chars_format::general || (flags & s::chars_format::hex) != static_cast<s::chars_format>(0))
        return 6;
    flags ^= s::chars_format::scientific;
    flags &= ~s::chars_format::hex;
    return flags == s::chars_format::fixed ? 0 : 7;
}

}  // namespace asc_stl_test_charconv

#endif  // ASC_STL_TEST_CHARCONV_DEVICE_CHECKS_H
