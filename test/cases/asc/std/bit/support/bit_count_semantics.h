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

#ifndef ASC_STL_TEST_BIT_COUNT_SEMANTICS_H
#define ASC_STL_TEST_BIT_COUNT_SEMANTICS_H

#include <asc/std/bit>

namespace asc_stl_bit_count_test {

inline constexpr unsigned int cases_per_width = 9;
inline constexpr unsigned int runtime_cases = 4 * cases_per_width;
inline constexpr unsigned int input_start = 64;
inline constexpr unsigned int output_start = 160;
inline constexpr unsigned int runtime_checks = 4 * runtime_cases;

template <class T>
CANN_ASC_STL_API constexpr unsigned int observe(T value) noexcept
{
    return static_cast<unsigned int>(asc::std::countl_zero(value)) |
        (static_cast<unsigned int>(asc::std::countl_one(value)) << 7) |
        (static_cast<unsigned int>(asc::std::countr_zero(value)) << 14) |
        (static_cast<unsigned int>(asc::std::countr_one(value)) << 21);
}

template <class T, class Pointer>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE void evaluate_width(Pointer words, unsigned int first) noexcept
{
    for (unsigned int index = 0; index < cases_per_width; ++index) {
        const unsigned int position = first + index;
        const auto low = static_cast<__UINT64_TYPE__>(words[input_start + 2 * position]);
        const auto high = static_cast<__UINT64_TYPE__>(words[input_start + 2 * position + 1]);
        const T value = static_cast<T>((high << 32) | low);
        words[output_start + position] = observe(value);
    }
}

template <class Pointer>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned int evaluate_runtime(Pointer words) noexcept
{
    // Only a few scalar locals live on Device; all varying inputs come from GM.
    evaluate_width<__UINT8_TYPE__>(words, 0);
    evaluate_width<__UINT16_TYPE__>(words, cases_per_width);
    evaluate_width<__UINT32_TYPE__>(words, 2 * cases_per_width);
    evaluate_width<__UINT64_TYPE__>(words, 3 * cases_per_width);
    return runtime_checks;
}

}  // namespace asc_stl_bit_count_test

#endif  // ASC_STL_TEST_BIT_COUNT_SEMANTICS_H
