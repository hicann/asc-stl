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

#ifndef ASC_STL_TEST_NUMERIC_REFERENCE_H
#define ASC_STL_TEST_NUMERIC_REFERENCE_H

#include <cstdint>
#include <limits>
#include <random>
#include <type_traits>
#include <vector>

namespace numeric_reference {

// Host-only oracle: exact arithmetic in a larger integer domain, independent
// of the delivered division-bound checks. Unsigned 64-bit products fit u128.
using wide = __int128_t;
using unsigned_wide = __uint128_t;

template <class T>
struct result {
    T value;
    bool failed;
};

template <class T>
result<T> arithmetic(T left, T right, unsigned operation)
{
    if (operation == 2 && !std::is_signed_v<T>) {
        const auto exact = static_cast<unsigned_wide>(left) * static_cast<unsigned_wide>(right);
        const bool failed = exact > static_cast<unsigned_wide>(std::numeric_limits<T>::max());
        return {failed ? T{0} : static_cast<T>(exact), failed};
    }
    const wide a = left, b = right;
    if (operation == 3 && b == 0)
        return {T{0}, true};
    wide exact{};
    switch (operation) {
        case 0:
            exact = a + b;
            break;
        case 1:
            exact = a - b;
            break;
        case 2:
            exact = a * b;
            break;
        default:
            exact = a / b;
            break;
    }
    const bool failed = exact < static_cast<wide>(std::numeric_limits<T>::min()) ||
        exact > static_cast<wide>(std::numeric_limits<T>::max());
    return {failed ? T{0} : static_cast<T>(exact), failed};
}

template <class To, class From>
result<To> cast(From value)
{
    const wide exact = value;
    const bool failed = exact < static_cast<wide>(std::numeric_limits<To>::min()) ||
        exact > static_cast<wide>(std::numeric_limits<To>::max());
    return {failed ? To{0} : static_cast<To>(value), failed};
}

template <class T>
std::vector<T> boundaries()
{
    const T low = std::numeric_limits<T>::min(), high = std::numeric_limits<T>::max();
    std::vector<T> values{low, static_cast<T>(low + 1), T{0}, T{1}, T{2}, T{3}, T{7}, static_cast<T>(high / 2),
        static_cast<T>(high / 2 + 1), static_cast<T>(high - 1), high};
    if constexpr (std::is_signed_v<T>) {
        values.push_back(T{-1});
        values.push_back(T{-2});
        values.push_back(static_cast<T>(low / 2));
    }
    return values;
}

template <class T>
T random_value(std::mt19937_64& engine)
{
    const auto raw = engine();
    if constexpr (std::is_signed_v<T>) {
        const T magnitude = static_cast<T>(raw & static_cast<std::uint64_t>(std::numeric_limits<T>::max()));
        return (raw >> 63) != 0 ? static_cast<T>(-magnitude) : magnitude;
    }
    return static_cast<T>(raw);
}

}  // namespace numeric_reference

#endif  // ASC_STL_TEST_NUMERIC_REFERENCE_H
