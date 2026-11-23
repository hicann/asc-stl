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

#ifndef CANN_ASC_STL_ASC___BIT_OPERATIONS_H
#define CANN_ASC_STL_ASC___BIT_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/climits>

// Portable unsigned arithmetic shared by Host, constant evaluation, SIMD
// scalar code and SIMT. Public operations use the 32/64-bit unsigned types.
namespace asc::detail {

// A high-rank unsigned working type avoids signed integer promotion even for
// the narrow types used by private helper tests.
template <class T>
CANN_ASC_STL_API constexpr T bit_reverse_impl(T value) noexcept
{
    unsigned long long input = value;
    unsigned long long result = 0;
    for (int index = 0; index < static_cast<int>(sizeof(T)) * CHAR_BIT; ++index) {
        result = (result << 1) | (input & 1ULL);
        input >>= 1;
    }
    return static_cast<T>(result);
}

template <class T>
CANN_ASC_STL_API constexpr T bitmask_low_impl(int bits) noexcept
{
    const int digits = static_cast<int>(sizeof(T)) * CHAR_BIT;
    return bits <= 0 ? T{0} : bits >= digits ? static_cast<T>(~T{0}) : static_cast<T>((1ULL << bits) - 1ULL);
}

template <class T>
CANN_ASC_STL_API constexpr bool bit_window_is_valid(int start, int width) noexcept
{
    const int digits = static_cast<int>(sizeof(T)) * CHAR_BIT;
    // Check the start before subtracting; start + width could overflow int.
    return start >= 0 && start <= digits && width >= 0 && width <= digits - start;
}

template <class T>
CANN_ASC_STL_API constexpr T bitmask_impl(int start, int width) noexcept
{
    if (!bit_window_is_valid<T>(start, width) || width == 0) {
        return T{0};
    }
    const auto low = static_cast<unsigned long long>(bitmask_low_impl<T>(width));
    return static_cast<T>(low << start);
}

template <class T>
CANN_ASC_STL_API constexpr T bitfield_extract_impl(T value, int start, int width) noexcept
{
    if (!bit_window_is_valid<T>(start, width) || width == 0) {
        return T{0};
    }
    const auto input = static_cast<unsigned long long>(value);
    return static_cast<T>((input >> start) & bitmask_low_impl<T>(width));
}

template <class T>
CANN_ASC_STL_API constexpr T bitfield_insert_impl(T destination, T source, int start, int width) noexcept
{
    if (!bit_window_is_valid<T>(start, width) || width == 0) {
        return destination;
    }
    const auto low = static_cast<unsigned long long>(bitmask_low_impl<T>(width));
    const auto mask = low << start;
    return static_cast<T>((static_cast<unsigned long long>(destination) & ~mask) |
        ((static_cast<unsigned long long>(source) & low) << start));
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___BIT_OPERATIONS_H
