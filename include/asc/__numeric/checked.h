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

#ifndef CANN_ASC_STL_ASC___NUMERIC_CHECKED_H
#define CANN_ASC_STL_ASC___NUMERIC_CHECKED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Checked and saturating arithmetic backend for the later public <asc/numeric>
// facade. Following the confirmed design, the implementation relies on no
// single compiler builtin: signed arithmetic goes through the portable
// unsigned decomposition (two's-complement wrap is well defined for unsigned
// types), range comparison, and division-based magnitude verification, all of
// which are valid in Host, ordinary AICore and pure SIMT and stay free of
// signed-overflow undefined behavior at every optimization level. The
// non-saturating forms return the wrapped bit pattern together with the
// overflow flag; the saturating forms clamp to the target bounds in the
// direction determined by the operation. __int128 is not part of the
// supported matrix.
namespace asc::detail {

template <class T>
struct overflow_result {
    T value{};
    bool overflow{};
};

template <bool Condition, class TrueType, class FalseType>
struct checked_conditional {
    using type = FalseType;
};

template <class TrueType, class FalseType>
struct checked_conditional<true, TrueType, FalseType> {
    using type = TrueType;
};

// Same-width unsigned counterpart for the supported standard integer widths.
template <class T>
struct checked_unsigned {
    using type = typename checked_conditional<sizeof(T) == 1, unsigned char,
        typename checked_conditional<sizeof(T) == 2, unsigned short,
            typename checked_conditional<sizeof(T) == 4, unsigned int,
                typename checked_conditional<sizeof(T) == 8, unsigned long long, void>::type>::type>::type>::type;
};

template <class T>
using checked_unsigned_t = typename checked_unsigned<T>::type;

template <class T>
CANN_ASC_STL_API constexpr T checked_minimum() noexcept
{
    if constexpr (static_cast<T>(-1) < T{0}) {
        return static_cast<T>(1ULL << (sizeof(T) * 8 - 1));
    }
    return T{0};
}

template <class T>
CANN_ASC_STL_API constexpr T checked_maximum() noexcept
{
    if constexpr (static_cast<T>(-1) < T{0}) {
        return static_cast<T>((1ULL << (sizeof(T) * 8 - 1)) - 1ULL);
    }
    return static_cast<T>(~T{0});
}

// The division-based magnitude verification never evaluates INT_MIN / -1,
// which traps on every supported toolchain before it can report overflow.
template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> add_overflow_impl(T left, T right) noexcept
{
    using Unsigned = checked_unsigned_t<T>;
    const Unsigned sum = static_cast<Unsigned>(left) + static_cast<Unsigned>(right);
    const T value = static_cast<T>(sum);
    if constexpr (static_cast<T>(-1) < T{0}) {
        const bool overflow = (left < 0) == (right < 0) && (value < 0) != (left < 0);
        return overflow_result<T>{value, overflow};
    } else {
        return overflow_result<T>{value, sum < static_cast<Unsigned>(left)};
    }
}

template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> sub_overflow_impl(T left, T right) noexcept
{
    using Unsigned = checked_unsigned_t<T>;
    const Unsigned difference = static_cast<Unsigned>(left) - static_cast<Unsigned>(right);
    const T value = static_cast<T>(difference);
    if constexpr (static_cast<T>(-1) < T{0}) {
        const bool overflow = (left < 0) != (right < 0) && (value < 0) != (left < 0);
        return overflow_result<T>{value, overflow};
    } else {
        return overflow_result<T>{value, static_cast<Unsigned>(left) < static_cast<Unsigned>(right)};
    }
}

template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> mul_overflow_impl(T left, T right) noexcept
{
    if (left == 0 || right == 0) {
        return overflow_result<T>{T{0}, false};
    }
    using Unsigned = checked_unsigned_t<T>;
    if constexpr (!(static_cast<T>(-1) < T{0})) {
        const Unsigned product = static_cast<Unsigned>(left) * static_cast<Unsigned>(right);
        return overflow_result<T>{static_cast<T>(product), product / static_cast<Unsigned>(right) != left};
    }
    const bool negative = (left < 0) != (right < 0);
    // Negating through the +1 step avoids the UB of -INT_MIN while producing
    // the exact magnitude in the unsigned domain.
    const Unsigned left_magnitude = left < 0 ? static_cast<Unsigned>(-(left + 1)) + 1U : static_cast<Unsigned>(left);
    const Unsigned right_magnitude =
        right < 0 ? static_cast<Unsigned>(-(right + 1)) + 1U : static_cast<Unsigned>(right);
    const Unsigned product_magnitude = static_cast<Unsigned>(left_magnitude * right_magnitude);
    bool overflow = product_magnitude / right_magnitude != left_magnitude;
    if (!overflow) {
        const Unsigned sign_bit = static_cast<Unsigned>(1) << (sizeof(T) * 8 - 1);
        const Unsigned negative_limit = negative ? sign_bit : sign_bit - 1U;
        overflow = product_magnitude > negative_limit;
    }
    const T value =
        negative ? static_cast<T>(static_cast<Unsigned>(0) - product_magnitude) : static_cast<T>(product_magnitude);
    return overflow_result<T>{value, overflow};
}

template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> div_overflow_impl(T left, T right) noexcept
{
    if (right == 0) {
        return overflow_result<T>{T{0}, true};
    }
    if constexpr (static_cast<T>(-1) < T{0}) {
        if (left == checked_minimum<T>() && right == T{-1}) {
            return overflow_result<T>{checked_minimum<T>(), true};
        }
    }
    return overflow_result<T>{static_cast<T>(left / right), false};
}

// The saturation direction comes from the operation, never from the sign of
// the wrapped result: a positive overflow of a signed type can wrap to a
// negative bit pattern and vice versa.
template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> saturating_add_impl(T left, T right) noexcept
{
    overflow_result<T> result = add_overflow_impl(left, right);
    // Only same-sign additions can overflow: both positive saturates high,
    // both negative saturates low.
    result.value = result.overflow ? (left < 0 ? checked_minimum<T>() : checked_maximum<T>()) : result.value;
    return result;
}

template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> saturating_sub_impl(T left, T right) noexcept
{
    overflow_result<T> result = sub_overflow_impl(left, right);
    if constexpr (static_cast<T>(-1) < T{0}) {
        result.value =
            result.overflow ? ((left < 0 && right >= 0) ? checked_minimum<T>() : checked_maximum<T>()) : result.value;
    } else {
        result.value = result.overflow ? checked_minimum<T>() : result.value;
    }
    return result;
}

template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> saturating_mul_impl(T left, T right) noexcept
{
    overflow_result<T> result = mul_overflow_impl(left, right);
    const bool clamp_low = (left < 0) != (right < 0);
    result.value = result.overflow ? (clamp_low ? checked_minimum<T>() : checked_maximum<T>()) : result.value;
    return result;
}

template <class T>
CANN_ASC_STL_API constexpr overflow_result<T> saturating_div_impl(T left, T right) noexcept
{
    overflow_result<T> result = div_overflow_impl(left, right);
    // The only division overflow carries a positive mathematical result.
    result.value = result.overflow ? checked_maximum<T>() : result.value;
    return result;
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___NUMERIC_CHECKED_H
