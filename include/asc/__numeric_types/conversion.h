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

#ifndef CANN_ASC_STL_ASC___NUMERIC_TYPES_CONVERSION_H
#define CANN_ASC_STL_ASC___NUMERIC_TYPES_CONVERSION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__numeric_types/bits.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cfloat>

namespace asc {

enum class rounding_mode { nearest_even = 0, toward_zero = 1, toward_positive = 2, toward_negative = 3 };
enum class saturation_mode { none = 0, finite = 1 };

namespace detail {

// Keep the Host launch pass independent of Device-only standard helpers.
// These instantiations copy binary32 float and uint32_t representations.
template <class To, class From>
CANN_ASC_STL_DETAIL_NUMERIC_API To numeric_bit_copy(const From& value) noexcept
{
    static_assert(sizeof(To) == sizeof(From), "numeric representation widths must match");
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_bit_cast)
    return __builtin_bit_cast(To, value);
#else
    To result;
    auto* destination = reinterpret_cast<unsigned char*>(&result);
    const auto* source = reinterpret_cast<const unsigned char*>(&value);
    for (unsigned index = 0; index < sizeof(To); ++index)
        destination[index] = source[index];
    return result;
#endif
}

template <class T>
inline constexpr bool numeric_scalar_float_v = asc::std::is_same_v<T, float16> || asc::std::is_same_v<T, bfloat16> ||
    asc::std::is_same_v<T, float8_e4m3fn> || asc::std::is_same_v<T, float8_e5m2>;

// ASC also compiles a Host launch pass, where no NPU architecture is set.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(__NPU_ARCH__) || \
    (defined(__NPU_ARCH__) && __NPU_ARCH__ == 3510 && defined(__BISHENG_CCEC__) && __clang_major__ == 15)
inline constexpr bool numeric_execution_supported = true;
#else
inline constexpr bool numeric_execution_supported = false;
#endif

#if !defined(__FAST_MATH__) && FLT_RADIX == 2 && FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128 && FLT_MIN_EXP == -125
inline constexpr bool numeric_float_supported = sizeof(float) == 4 && numeric_execution_supported;
#else
inline constexpr bool numeric_float_supported = false;
#endif

template <class To, class From, rounding_mode R, saturation_mode S>
inline constexpr bool numeric_conversion_supported =
    (R == rounding_mode::nearest_even || R == rounding_mode::toward_zero || R == rounding_mode::toward_positive ||
        R == rounding_mode::toward_negative) &&
    (S == saturation_mode::none || S == saturation_mode::finite) &&
    ((numeric_float_supported &&
         ((asc::std::is_same_v<From, float> && numeric_scalar_float_v<To>) ||
             (numeric_scalar_float_v<From> && asc::std::is_same_v<To, float>))) ||
        (numeric_execution_supported &&
            ((asc::std::is_same_v<To, int4> && asc::std::is_same_v<From, asc::std::int32_t> &&
                 S == saturation_mode::finite) ||
                (asc::std::is_same_v<From, int4> && asc::std::is_same_v<To, asc::std::int32_t>))));

template <class T>
struct numeric_float_layout {
    static constexpr unsigned mantissa = asc::std::is_same_v<T, float16> ? 10 :
        asc::std::is_same_v<T, bfloat16>                                 ? 7 :
        asc::std::is_same_v<T, float8_e4m3fn>                            ? 3 :
                                                                           2;
    static constexpr unsigned exponent = asc::std::is_same_v<T, bfloat16> ? 8 :
        asc::std::is_same_v<T, float8_e4m3fn>                             ? 4 :
                                                                            5;
    static constexpr int bias = (1 << (exponent - 1)) - 1;
    static constexpr unsigned sign = 1U << (exponent + mantissa);
    static constexpr unsigned infinity = ((1U << exponent) - 1) << mantissa;
    static constexpr bool has_infinity = !asc::std::is_same_v<T, float8_e4m3fn>;
    static constexpr unsigned max_finite = has_infinity ? infinity - 1 : sign - 2;
    static constexpr unsigned nan = has_infinity ? infinity | (1U << (mantissa - 1)) : sign - 1;
};

// Rounding is entirely integer based, including shifts exceeding the source
// significand width. No target rounding register or denormal mode is consulted.
template <rounding_mode R>
CANN_ASC_STL_DETAIL_NUMERIC_API asc::std::uint32_t numeric_round(
    asc::std::uint32_t significand, unsigned shift, bool negative) noexcept
{
    const auto truncated = shift < 32 ? significand >> shift : 0U;
    const auto remainder = shift < 32 ? significand & ((1U << shift) - 1) : significand;
    bool increment = false;
    if constexpr (R == rounding_mode::nearest_even) {
        if (shift < 32) {
            const auto halfway = 1U << (shift - 1);
            increment = remainder > halfway || (remainder == halfway && (truncated & 1));
        }
    } else if constexpr (R == rounding_mode::toward_positive) {
        increment = !negative && remainder != 0;
    } else if constexpr (R == rounding_mode::toward_negative) {
        increment = negative && remainder != 0;
    }
    return truncated + static_cast<unsigned>(increment);
}

template <class T, rounding_mode R, saturation_mode S>
CANN_ASC_STL_DETAIL_NUMERIC_API unsigned numeric_overflow(bool negative) noexcept
{
    using L = numeric_float_layout<T>;
    const unsigned sign = negative ? L::sign : 0;
    if constexpr (S == saturation_mode::finite) {
        return sign | L::max_finite;
    } else if constexpr (!L::has_infinity) {
        return L::nan;
    } else {
        const bool to_infinity = R == rounding_mode::nearest_even ||
            (R == rounding_mode::toward_positive && !negative) || (R == rounding_mode::toward_negative && negative);
        return sign | (to_infinity ? L::infinity : L::max_finite);
    }
}

template <class T, rounding_mode R, saturation_mode S>
CANN_ASC_STL_DETAIL_NUMERIC_API unsigned numeric_encode(asc::std::uint32_t input) noexcept
{
    using L = numeric_float_layout<T>;
    const bool negative = (input >> 31) != 0;
    const unsigned sign = negative ? L::sign : 0;
    const unsigned exp = (input >> 23) & 255;
    const unsigned fraction = input & 0x7fffff;
    if (exp == 255) {
        if (fraction != 0) {
            return L::nan;
        }
        if constexpr (S == saturation_mode::finite || !L::has_infinity) {
            return numeric_overflow<T, R, S>(negative);
        } else {
            return sign | L::infinity;
        }
    }
    const int exponent = exp == 0 ? -126 : static_cast<int>(exp) - 127;
    const int minimum = 1 - L::bias;
    const unsigned significand = exp == 0 ? fraction : fraction | 0x800000;
    if (exponent > L::bias + (L::has_infinity ? 0 : 1)) {
        return numeric_overflow<T, R, S>(negative);
    }
    const unsigned shift = 23 - L::mantissa + (exponent < minimum ? minimum - exponent : 0);
    const unsigned rounded = numeric_round<R>(significand, shift, negative);
    const unsigned encoding = exponent < minimum ?
        rounded :
        (static_cast<unsigned>(exponent + L::bias) << L::mantissa) + rounded - (1U << L::mantissa);
    return encoding > L::max_finite ? numeric_overflow<T, R, S>(negative) : sign | encoding;
}

template <class T, saturation_mode S>
CANN_ASC_STL_DETAIL_NUMERIC_API asc::std::uint32_t numeric_decode(unsigned input) noexcept
{
    using L = numeric_float_layout<T>;
    const unsigned sign = (input & L::sign) != 0 ? 0x80000000U : 0;
    const unsigned magnitude = input & (L::sign - 1);
    if (magnitude > L::max_finite) {
        if (!L::has_infinity || magnitude != L::infinity) {
            return 0x7fc00000U;
        }
        return sign | (S == saturation_mode::finite ? 0x7f7fffffU : 0x7f800000U);
    }
    if (magnitude == 0) {
        return sign;
    }
    unsigned significand = magnitude & ((1U << L::mantissa) - 1);
    const unsigned exp = magnitude >> L::mantissa;
    int exponent = (exp == 0 ? 1 : static_cast<int>(exp)) - L::bias;
    if (exp != 0) {
        significand |= 1U << L::mantissa;
    } else {
        while (significand < (1U << L::mantissa)) {
            significand <<= 1;
            --exponent;
        }
    }
    significand <<= 23 - L::mantissa;
    // BF16 subnormals can also be binary32 subnormals.
    if (exponent < -126) {
        return sign | (significand >> (-126 - exponent));
    }
    return sign | (static_cast<unsigned>(exponent + 127) << 23) | (significand & 0x7fffff);
}

}  // namespace detail

template <class To, class From, rounding_mode R = rounding_mode::nearest_even,
    saturation_mode S = saturation_mode::none>
inline constexpr bool is_numeric_conversion_supported_v = detail::numeric_conversion_supported<To, From, R, S>;

template <class To, rounding_mode R = rounding_mode::nearest_even, saturation_mode S = saturation_mode::none,
    class From, asc::std::enable_if_t<is_numeric_conversion_supported_v<To, From, R, S>, int> = 0>
CANN_ASC_STL_DETAIL_NUMERIC_API To numeric_convert(From value) noexcept
{
    if constexpr (asc::std::is_same_v<From, float>) {
        using Storage = typename numeric_format_traits<To>::storage_type;
        return asc::from_bits<To>(static_cast<Storage>(
            detail::numeric_encode<To, R, S>(detail::numeric_bit_copy<asc::std::uint32_t>(value))));
    } else if constexpr (asc::std::is_same_v<To, float>) {
        return detail::numeric_bit_copy<float>(detail::numeric_decode<From, S>(asc::to_bits(value)));
    } else if constexpr (asc::std::is_same_v<To, int4>) {
        const auto clamped = value < -8 ? -8 : value > 7 ? 7 : value;
        return asc::from_bits<int4>(static_cast<asc::std::uint8_t>(static_cast<unsigned>(clamped) & 15));
    } else {
        const auto code = asc::to_bits(value);
        return static_cast<asc::std::int32_t>(code < 8 ? code : static_cast<int>(code) - 16);
    }
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___NUMERIC_TYPES_CONVERSION_H
