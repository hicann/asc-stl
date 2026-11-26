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

#include <array>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string_view>
#include <system_error>

namespace {

namespace asc_std = asc::std;

template <class T>
bool check_round_trip(T value, int base)
{
    std::array<char, 80> actual, reference;
    actual.fill('#');
    reference.fill('#');
    const auto expected = std::to_chars(reference.data(), reference.data() + reference.size(), value, base);
    const auto width = expected.ptr - reference.data();
    if (expected.ec != std::errc{} || width <= 0 || width >= static_cast<std::ptrdiff_t>(reference.size()))
        return false;

    const auto compiled = asc_std::to_chars(actual.data() + 1, actual.data() + 1 + width, value, base);
    if (compiled.ec != asc_std::errc{} || compiled.ptr != actual.data() + 1 + width ||
        std::string_view(actual.data() + 1, width) != std::string_view(reference.data(), width) ||
        actual.front() != '#' || actual[width + 1] != '#')
        return false;
    T decoded = T{9};
    const auto read = asc_std::from_chars(actual.data() + 1, compiled.ptr + 1, decoded, base);
    if (read.ec != asc_std::errc{} || read.ptr != compiled.ptr || decoded != value)
        return false;

    actual.fill('#');
    const auto insufficient = asc_std::to_chars(actual.data() + 1, actual.data() + width, value, base);
    return insufficient.ec == asc_std::errc::value_too_large && insufficient.ptr == actual.data() + width &&
        actual.front() == '#' && actual[width] == '#';
}

template <class T>
bool check_parsing(std::string_view input, int base)
{
    T actual = T{47};
    T expected = actual;
    const auto* last = input.data() + input.size();
    const auto reference = std::from_chars(input.data(), last, expected, base);
    const auto result = asc_std::from_chars(input.data(), last, actual, base);
    return result.ptr == reference.ptr && static_cast<int>(result.ec) == static_cast<int>(reference.ec) &&
        actual == expected;
}

template <class T>
bool check_radix(int base)
{
    using limits = std::numeric_limits<T>;
    const T values[] = {limits::min(), static_cast<T>(limits::min() + 1), T{0}, T{1}, static_cast<T>(base - 1),
        static_cast<T>(base), static_cast<T>(limits::max() - 1), limits::max()};
    for (T value : values) {
        if (!check_round_trip(value, base))
            return false;
    }
    const std::string_view patterns[] = {"", " ", "+1", "-1", "-", "--1", " 1", "1#", "00B?",
        "00000000000000000000000000000000000001", "0xFA",
        "111111111111111111111111111111111111111111111111111111111111111111111111111#",
        "-111111111111111111111111111111111111111111111111111111111111111111111111111#", "ZZz?"};
    for (auto input : patterns) {
        if (!check_parsing<T>(input, base))
            return false;
    }
    return true;
}

}  // namespace

int main()
{
    for (int base = 2; base <= 36; ++base) {
        if (!check_radix<char>(base) || !check_radix<signed char>(base) || !check_radix<unsigned char>(base) ||
            !check_radix<std::int16_t>(base) || !check_radix<std::uint16_t>(base) || !check_radix<std::int32_t>(base) ||
            !check_radix<std::uint32_t>(base) || !check_radix<std::int64_t>(base) ||
            !check_radix<std::uint64_t>(base)) {
            std::cerr << "Integer conversion mismatch at base " << base << '\n';
            return 1;
        }
    }
    return 0;
}
