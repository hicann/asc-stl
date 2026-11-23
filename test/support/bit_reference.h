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

#ifndef ASC_STL_TEST_BIT_REFERENCE_H
#define ASC_STL_TEST_BIT_REFERENCE_H

#include <asc/std/climits>
#include <asc/std/cstdint>

namespace bit_test {

using u32 = asc::std::uint32_t;
using u64 = asc::std::uint64_t;

template <class T>
inline constexpr int digits = static_cast<int>(sizeof(T)) * CHAR_BIT;

template <class T>
CANN_ASC_STL_API constexpr bool reference_window(int start, int width)
{
    if (start < 0 || width < 0) {
        return false;
    }
    // A wider sum supplies an independent check without overflowing int.
    return static_cast<unsigned long long>(start) + static_cast<unsigned long long>(width) <= digits<T>;
}

template <class T>
CANN_ASC_STL_API constexpr T reference_reverse(T value)
{
    unsigned long long result = 0;
    for (int bit = 0; bit < digits<T>; ++bit) {
        if ((static_cast<unsigned long long>(value) & (1ULL << bit)) != 0) {
            result |= 1ULL << (digits<T> - 1 - bit);
        }
    }
    return static_cast<T>(result);
}

template <class T>
CANN_ASC_STL_API constexpr T reference_extract(T value, int start, int width)
{
    if (!reference_window<T>(start, width)) {
        return T{0};
    }
    unsigned long long result = 0;
    for (int bit = 0; bit < width; ++bit) {
        if ((static_cast<unsigned long long>(value) & (1ULL << (start + bit))) != 0) {
            result |= 1ULL << bit;
        }
    }
    return static_cast<T>(result);
}

template <class T>
CANN_ASC_STL_API constexpr T reference_insert(T destination, T source, int start, int width)
{
    if (!reference_window<T>(start, width)) {
        return destination;
    }
    unsigned long long result = 0;
    for (int bit = 0; bit < digits<T>; ++bit) {
        const bool inside = bit >= start && bit - start < width;
        const auto input = static_cast<unsigned long long>(inside ? source : destination);
        const int input_bit = inside ? bit - start : bit;
        if ((input & (1ULL << input_bit)) != 0) {
            result |= 1ULL << bit;
        }
    }
    return static_cast<T>(result);
}

template <class T>
CANN_ASC_STL_API constexpr T reference_mask(int start, int width)
{
    if (!reference_window<T>(start, width)) {
        return T{0};
    }
    unsigned long long result = 0;
    for (int bit = 0; bit < digits<T>; ++bit) {
        if (bit >= start && bit - start < width) {
            result |= 1ULL << bit;
        }
    }
    return static_cast<T>(result);
}

}  // namespace bit_test

#endif  // ASC_STL_TEST_BIT_REFERENCE_H
