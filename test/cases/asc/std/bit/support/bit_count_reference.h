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

#ifndef ASC_STL_TEST_BIT_COUNT_REFERENCE_H
#define ASC_STL_TEST_BIT_COUNT_REFERENCE_H

#include <cstdint>
#include <limits>

#include "bit_count_semantics.h"

namespace asc_stl_bit_count_test {

// Independent bit-by-bit goldens: no ASC-STL bit count or compiler clz/ctz builtin.
constexpr unsigned int reference_run(std::uint64_t value, unsigned int width, bool high, unsigned int bit)
{
    unsigned int count = 0;
    while (count < width) {
        const unsigned int position = high ? width - 1 - count : count;
        if (((value >> position) & 1U) != bit) {
            break;
        }
        ++count;
    }
    return count;
}

constexpr unsigned int reference(std::uint64_t value, unsigned int width)
{
    return reference_run(value, width, true, 0) | (reference_run(value, width, true, 1) << 7) |
        (reference_run(value, width, false, 0) << 14) | (reference_run(value, width, false, 1) << 21);
}

constexpr std::uint64_t runtime_input(unsigned int width, unsigned int index)
{
    const std::uint64_t maximum = width == 64 ? ~std::uint64_t{0} : (std::uint64_t{1} << width) - 1;
    const std::uint64_t high = std::uint64_t{1} << (width - 1);
    switch (index) {
        case 0:
            return 0;
        case 1:
            return maximum;
        case 2:
            return 1;
        case 3:
            return high;
        case 4:
            return high - 1;
        case 5:
            return high + 1;
        case 6:
            return 0xAAAAAAAAAAAAAAAAULL & maximum;
        case 7:
            return 0x5555555555555555ULL & maximum;
        default:
            return std::uint64_t{1} << (width / 2);
    }
}

inline void initialize_runtime(unsigned int* words)
{
    const unsigned int widths[4] = {8, 16, 32, 64};
    for (unsigned int group = 0; group < 4; ++group) {
        for (unsigned int index = 0; index < cases_per_width; ++index) {
            const auto value = runtime_input(widths[group], index);
            const auto position = input_start + 2 * (group * cases_per_width + index);
            words[position] = static_cast<unsigned int>(value);
            words[position + 1] = static_cast<unsigned int>(value >> 32);
        }
    }
}

inline unsigned int runtime_failures(const unsigned int* words)
{
    const unsigned int widths[4] = {8, 16, 32, 64};
    unsigned int failures = words[13] != runtime_checks;
    for (unsigned int group = 0; group < 4; ++group) {
        for (unsigned int index = 0; index < cases_per_width; ++index) {
            const auto value = runtime_input(widths[group], index);
            const auto expected = reference(value, widths[group]);
            const auto position = input_start + 2 * (group * cases_per_width + index);
            failures += words[position] != static_cast<unsigned int>(value);
            failures += words[position + 1] != static_cast<unsigned int>(value >> 32);
            failures += words[output_start + group * cases_per_width + index] != expected;
        }
    }
    return failures;
}

}  // namespace asc_stl_bit_count_test

#endif  // ASC_STL_TEST_BIT_COUNT_REFERENCE_H
