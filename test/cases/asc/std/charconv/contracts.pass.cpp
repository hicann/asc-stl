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

#include <asc/std/charconv>
#include <charconv>
#include <limits>

template <class T>
bool integers()
{
    const T samples[] = {std::numeric_limits<T>::min(), T{0}, T{1}, T{9}, std::numeric_limits<T>::max()};
    for (T value : samples) {
        for (int base = 2; base <= 36; ++base) {
            char reference[70]{};
            const auto ref = std::to_chars(reference, reference + sizeof(reference), value, base);
            const auto length = ref.ptr - reference;
            char actual[72]{};
            actual[length + 1] = '!';
            auto good = asc::std::to_chars(actual + 1, actual + 1 + length, value, base);
            if (!good || good != asc::std::to_chars_result{actual + 1 + length, {}} || actual[length + 1] != '!')
                return false;
            for (int j = 0; j < length; ++j) {
                if (actual[j + 1] != reference[j])
                    return false;
            }
            T parsed = T{3};
            const auto read = asc::std::from_chars(reference, ref.ptr, parsed, base);
            if (!read || read != asc::std::from_chars_result{ref.ptr, {}} || parsed != value)
                return false;
            const auto short_write = asc::std::to_chars(actual, actual + length - 1, value, base);
            if (short_write || short_write.ptr != actual + length - 1 ||
                short_write.ec != asc::std::errc::value_too_large)
                return false;
        }
    }
    char overflow[] = "99999999999999999999999999x";
    T preserved = T{7};
    auto large = asc::std::from_chars(overflow, overflow + sizeof(overflow) - 1, preserved);
    auto invalid = asc::std::from_chars(overflow, overflow, preserved);
    return preserved == T{7} && large.ec == asc::std::errc::result_out_of_range &&
        large.ptr == overflow + sizeof(overflow) - 2 && invalid.ec == asc::std::errc::invalid_argument &&
        invalid.ptr == overflow;
}

int main()
{
    using format = asc::std::chars_format;
    format f = format::fixed;
    f |= format::scientific;
    f ^= format::fixed;
    f &= ~format::hex;
    if (f != format::scientific || (format::general & format::fixed) != format::fixed ||
        (format::fixed | format::scientific) != format::general || (format::general ^ format::fixed) != f)
        return 1;
    return !(integers<char>() && integers<signed char>() && integers<unsigned char>() && integers<short>() &&
        integers<unsigned short>() && integers<int>() && integers<unsigned int>() && integers<long>() &&
        integers<unsigned long>() && integers<long long>() && integers<unsigned long long>());
}
