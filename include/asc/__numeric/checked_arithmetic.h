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

#ifndef CANN_ASC_STL_ASC___NUMERIC_CHECKED_ARITHMETIC_H
#define CANN_ASC_STL_ASC___NUMERIC_CHECKED_ARITHMETIC_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/limits>

namespace asc {
namespace detail {

template <class T,
    bool = ::asc::std::disjunction_v<::asc::std::is_same<T, signed char>, ::asc::std::is_same<T, unsigned char>,
        ::asc::std::is_same<T, short>, ::asc::std::is_same<T, unsigned short>, ::asc::std::is_same<T, int>,
        ::asc::std::is_same<T, unsigned int>, ::asc::std::is_same<T, long>, ::asc::std::is_same<T, unsigned long>,
        ::asc::std::is_same<T, long long>, ::asc::std::is_same<T, unsigned long long>>>
struct numeric_integer : ::asc::std::false_type {};

template <class T>
struct numeric_integer<T, true>
    : ::asc::std::bool_constant<(
          ::asc::std::numeric_limits<T>::digits + ::asc::std::numeric_limits<T>::is_signed <= 64)> {};

}  // namespace detail

template <class T>
struct checked_result {
    static_assert(detail::numeric_integer<T>::value, "checked_result requires a standard integer of at most 64 bits");
    T value{};
    bool failed{};
};

namespace detail {

// Check before evaluating the arithmetic expression. Failure values are always
// zero, with no dependence on signed representation or out-of-range casts.
template <class T>
CANN_ASC_STL_API constexpr checked_result<T> numeric_add(T left, T right) noexcept
{
    constexpr T high = ::asc::std::numeric_limits<T>::max();
    if constexpr (::asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = ::asc::std::numeric_limits<T>::min();
        if ((right > T{0} && left > high - right) || (right < T{0} && left < low - right)) {
            return {T{0}, true};
        }
    } else if (left > high - right) {
        return {T{0}, true};
    }
    return {static_cast<T>(left + right), false};
}

template <class T>
CANN_ASC_STL_API constexpr checked_result<T> numeric_sub(T left, T right) noexcept
{
    if constexpr (::asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = ::asc::std::numeric_limits<T>::min();
        constexpr T high = ::asc::std::numeric_limits<T>::max();
        if ((right > T{0} && left < low + right) || (right < T{0} && left > high + right)) {
            return {T{0}, true};
        }
    } else if (left < right) {
        return {T{0}, true};
    }
    return {static_cast<T>(left - right), false};
}

using numeric_word = unsigned long long;

struct numeric_product {
    numeric_word value;
    bool failed;
};

// Partial products use at most 32-bit operands. This avoids a widened multiply
// and the unavailable __multi3 helper in some AICore compiler configurations.
CANN_ASC_STL_API constexpr numeric_product numeric_multiply_words(numeric_word left, numeric_word right) noexcept
{
    constexpr numeric_word mask = 0xffffffffULL;
    const numeric_word left_low = left & mask, right_low = right & mask;
    const numeric_word left_high = left >> 32, right_high = right >> 32;
    if (left_high != 0 && right_high != 0) {
        return {0, true};
    }
    const numeric_word low = left_low * right_low;
    const numeric_word cross_left = left_low * right_high;
    const numeric_word cross_right = left_high * right_low;
    if (cross_left > mask || cross_right > mask) {
        return {0, true};
    }
    const numeric_word cross = cross_left + cross_right;
    if (cross > mask) {
        return {0, true};
    }
    const numeric_word shifted = cross << 32;
    if (low > 0xffffffffffffffffULL - shifted) {
        return {0, true};
    }
    return {low + shifted, false};
}

template <class T>
CANN_ASC_STL_API constexpr numeric_word numeric_magnitude(T value) noexcept
{
    if constexpr (::asc::std::numeric_limits<T>::is_signed) {
        return value < T{0} ? numeric_word{0} - static_cast<numeric_word>(value) : static_cast<numeric_word>(value);
    }
    return static_cast<numeric_word>(value);
}

template <class T>
CANN_ASC_STL_API constexpr checked_result<T> numeric_mul(T left, T right) noexcept
{
    const auto product = ::asc::detail::numeric_multiply_words(
        ::asc::detail::numeric_magnitude(left), ::asc::detail::numeric_magnitude(right));
    constexpr T high = ::asc::std::numeric_limits<T>::max();
    if constexpr (::asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = ::asc::std::numeric_limits<T>::min();
        const bool negative = (left < T{0}) != (right < T{0});
        const numeric_word limit = negative ? ::asc::detail::numeric_magnitude(low) : static_cast<numeric_word>(high);
        if (product.failed || product.value > limit) {
            return {T{0}, true};
        }
        if (negative) {
            return {product.value == limit ? low : static_cast<T>(-static_cast<T>(product.value)), false};
        }
    } else if (product.failed || product.value > static_cast<numeric_word>(high)) {
        return {T{0}, true};
    }
    return {static_cast<T>(product.value), false};
}

template <class T>
CANN_ASC_STL_API constexpr checked_result<T> numeric_div(T left, T right) noexcept
{
    if (right == T{0}) {
        return {T{0}, true};
    }
    if constexpr (::asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = ::asc::std::numeric_limits<T>::min();
        constexpr T high = ::asc::std::numeric_limits<T>::max();
        if (low < -high && left == low && right == T{-1}) {
            return {T{0}, true};
        }
    }
    return {static_cast<T>(left / right), false};
}

template <class To, class From>
CANN_ASC_STL_API constexpr checked_result<To> numeric_cast(From value) noexcept
{
    if (!::asc::std::in_range<To>(value)) {
        return {To{0}, true};
    }
    return {static_cast<To>(value), false};
}

}  // namespace detail
}  // namespace asc

#endif  // CANN_ASC_STL_ASC___NUMERIC_CHECKED_ARITHMETIC_H
