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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_CAST_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_CAST_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>

// Floating-point format conversion via __fp_cast (a single constexpr template):
// - Between float/double/long double: static_cast (round to nearest even);
// - Same format (including __asc_fp wrappers vs CCE native scalars): storage
//   bits passed through unchanged;
// - half/bfloat16_t (CCE device built-in scalars): via static_cast;
// - fp8 (e4m3/e5m2/e8m0): software bit-level codec (__detail::__fp8_encode/
//   __fp8_decode), identical code on host and device, constexpr, bit-exact:
//   decoding is a pure bit expansion; encoding is RN-even (e4m3/e5m2 NOSAT
//   semantics: e4m3 overflow -> NaN, e5m2 overflow -> Inf; e8m0 encodes by
//   truncation).
//   double/long double sources are routed through float before encoding (fp8
//   significands are at most 4 bits, so double rounding is only a risk on
//   theoretical boundaries);
// - fp6/fp4: no scalar types exist (packed spellings only); instantiation
//   yields an explicit Unsupported static_assert.

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __detail {

// fp8 bit pattern -> float (exact bit expansion; constexpr, identical code on
// host and device).
// ebits/mbits are the fp8 format's field widths; fn_no_inf selects the e4m3
// no-Inf variant (exponent all ones with the largest mantissa -> NaN, otherwise
// the largest finite value on the 448 scale).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float __fp8_decode(
    unsigned char bits, int ebits, int mbits, bool fn_no_inf) noexcept
{
    const unsigned int sign = (static_cast<unsigned int>(bits) >> (ebits + mbits)) & 1u;
    const unsigned int expf = (static_cast<unsigned int>(bits) >> mbits) & ((1u << ebits) - 1u);
    const unsigned int mant = static_cast<unsigned int>(bits) & ((1u << mbits) - 1u);
    const int bias = (1 << (ebits - 1)) - 1;

    unsigned int out = sign << 31;
    if (expf == 0) {
        if (mant == 0) {
            return ::asc::std::bit_cast<float>(out);  // ±0
        }
        // Subnormal: value = m * 2^(1-bias-mbits). Normalize m up to its most
        // significant bit s, then assemble in 1.f form (float exponent =
        // -s-bias+127, mantissa aligned to 23 bits).
        int s = 0;
        unsigned int m = mant;
        while ((m & (1u << (mbits - 1))) == 0) {
            m <<= 1;
            ++s;  // each left shift lowers the MSB index by one
        }
        const int float_exponent = static_cast<int>(mbits) - 1 - s + 1 - bias - mbits + 127;
        if (float_exponent <= 0) {
            return ::asc::std::bit_cast<float>(out);  // deep underflow flushes to 0
        }
        const unsigned int float_mantissa = (m & ((1u << (mbits - 1)) - 1u)) << (23 - (mbits - 1));
        return ::asc::std::bit_cast<float>(out | (static_cast<unsigned int>(float_exponent) << 23) | float_mantissa);
    }
    if (expf == (1u << ebits) - 1u) {
        if (fn_no_inf) {
            // e4m3 variant: no Inf; the largest mantissa is NaN, all others are
            // the largest finite value
            if (mant == (1u << mbits) - 1u) {
                return ::asc::std::bit_cast<float>(out | 0x7fc00000u);  // NaN
            }
            // Largest finite binade of the e4m3 variant: the normal scale 2^8
            // with an all-ones E field
            const int float_exponent = (1 << ebits) - 1 - bias + 127;
            return ::asc::std::bit_cast<float>(
                out | (static_cast<unsigned int>(float_exponent) << 23) | (mant << (23 - mbits)));
        }
        if (mant == 0) {
            return ::asc::std::bit_cast<float>(out | 0x7f800000u);  // ±Inf
        }
        return ::asc::std::bit_cast<float>(out | 0x7fc00000u);  // NaN
    }
    const int float_exponent = static_cast<int>(expf) - bias + 127;
    return ::asc::std::bit_cast<float>(
        out | (static_cast<unsigned int>(float_exponent) << 23) | (mant << (23 - mbits)));
}

// float -> fp8 bit pattern (RN-even; NOSAT semantics). constexpr.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned char __fp8_encode(
    float value, int ebits, int mbits, bool fn_no_inf) noexcept
{
    const unsigned int float_bits = ::asc::std::bit_cast<unsigned int>(value);
    const unsigned int sign = (float_bits >> 31) & 1u;
    const unsigned int float_abs = float_bits & 0x7fffffffu;
    const int bias = (1 << (ebits - 1)) - 1;

    if (float_abs > 0x7f800000u) {
        // NaN: quieted (mantissa set to the smallest nonzero value)
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
    }
    if (float_abs == 0x7f800000u) {
        // Inf: the e4m3 variant has no Inf -> NaN; other formats keep Inf
        if (fn_no_inf) {
            return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
        }
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits));
    }
    if (float_abs == 0u) {
        return static_cast<unsigned char>(sign << (ebits + mbits));
    }

    const int float_exp = static_cast<int>((float_abs >> 23) & 0xffu);
    const unsigned int float_mant = float_abs & 0x7fffffu;
    int etarget = float_exp - 127 + bias;  // target exponent (before any mantissa carry)

    // Overflow ceiling: in the e4m3 variant E=15 with M<=6 is still the largest
    // finite binade (the 448 scale), only M==7 is NaN; in the other formats an
    // all-ones E field is reserved for Inf/NaN.
    const int emax_field = (1 << ebits) - 1 - (fn_no_inf ? 0 : 1);
    if (etarget > emax_field) {
        if (fn_no_inf) {
            return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
        }
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits));
    }

    if (etarget >= 1) {
        // Normal range: round the significand (with the implicit leading bit)
        // RN-even to mbits+1 bits; the implicit bit goes to the exponent, and
        // the mantissa field = the low mbits
        const unsigned int full = (float_mant | 0x800000u) >> (23 - mbits);  // truncated, implicit leading 1 included
        const unsigned int rest = float_mant & ((1u << (23 - mbits)) - 1u);
        const unsigned int half = 1u << (23 - mbits - 1);
        unsigned int rounded = full;
        if (rest > half || (rest == half && (full & 1u))) {
            ++rounded;  // the carry may push this to mbits+2 bits -> exponent +1
        }
        if (rounded >= (1u << (mbits + 1))) {
            rounded = 1u << mbits;  // rounding carry crossed the top bit: the implicit bit shifts right
            ++etarget;
            if (etarget > emax_field) {
                if (fn_no_inf) {
                    return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
                }
                return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits));
            }
        }
        // e4m3 variant with E=15 and M==7 -> NaN (above 448, or filled in by rounding)
        if (fn_no_inf && etarget == (1 << ebits) - 1 && rounded == (1u << mbits) - 1u) {
            return static_cast<unsigned char>((sign << (ebits + mbits)) | (((1u << ebits) - 1u) << mbits) | 1u);
        }
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (static_cast<unsigned int>(etarget) << mbits) |
            (rounded & ((1u << mbits) - 1u)));
    }

    // Subnormal/underflow region: exponent field 0, implicit bit 0. The target
    // step size = 2^(1-bias-mbits), and |v| measured in steps = (0x800000|mant)
    // divided by 2^(23-e_eff+1-bias-mbits).
    const int e_eff = float_exp - 127;                    // true exponent (< 1-bias)
    const int shift_div = 23 - e_eff + 1 - bias - mbits;  // divisor shift (>0: right shift)
    if (shift_div >= 24) {
        return static_cast<unsigned char>(sign << (ebits + mbits));  // deep underflow -> ±0
    }
    const unsigned int significand = 0x800000u | float_mant;
    unsigned int steps = significand >> shift_div;
    unsigned int rest_masked = 0u;
    unsigned int half_ulp = 0u;
    if (shift_div > 0) {
        rest_masked = significand & ((1u << shift_div) - 1u);
        half_ulp = 1u << (shift_div - 1);
    }
    if (rest_masked > half_ulp || (rest_masked == half_ulp && (steps & 1u))) {
        ++steps;  // RN-even
    }
    if (steps >= (1u << mbits)) {
        // the step-count carry lands exactly on the smallest normal
        return static_cast<unsigned char>((sign << (ebits + mbits)) | (1u << mbits));
    }
    return static_cast<unsigned char>((sign << (ebits + mbits)) | steps);
}

// e8m0 encoding (exponent-only format, truncation semantics): value -> 2^(floor(log2|v|)).
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr unsigned char __e8m0_encode(float value) noexcept
{
    const unsigned int float_bits = ::asc::std::bit_cast<unsigned int>(value);
    const unsigned int float_abs = float_bits & 0x7fffffffu;
    if (float_abs >= 0x7f800000u) {
        return 0xffu;  // NaN/Inf -> NaN pattern
    }
    if (float_abs == 0u) {
        return 0x00u;  // 0 -> 0
    }
    const int float_exp = static_cast<int>((float_abs >> 23) & 0xffu) - 127;
    // Truncation: |v| lies in [2^e, 2^(e+1)); the sign does not affect the
    // magnitude interval, so the exponent is e.
    const int field = float_exp + 127;
    if (field <= 0) {
        return 0x00u;  // deep underflow flushes to 0
    }
    if (field >= 255) {
        return 0xffu;  // NaN pattern (e8m0 has no Inf encoding)
    }
    return static_cast<unsigned char>(field);
}

}  // namespace __detail

template <class To, class From>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr To __fp_cast(From value) noexcept
{
    if constexpr (is_same_v<To, From>) {
        return value;
    } else if constexpr (__is_std_fp_v<To> && __is_std_fp_v<From>) {
        return static_cast<To>(value);
    } else if constexpr (__is_fp_v<To> && __is_fp_v<From> && __fp_format_of_v<To> == __fp_format_of_v<From>) {
        // same format: storage bits pass through (__asc_fp wrapper vs CCE native scalar)
        return __fp_from_storage<To>(__fp_get_storage(value));
    }
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    else if constexpr (__fp_format_of_v<From> == __fp_format::__fp8_e4m3) {
        return ::asc::std::__fp_cast<To>(::asc::std::__detail::__fp8_decode(__fp_get_storage(value), 4, 3, true));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    else if constexpr (__fp_format_of_v<From> == __fp_format::__fp8_e5m2) {
        return ::asc::std::__fp_cast<To>(::asc::std::__detail::__fp8_decode(__fp_get_storage(value), 5, 2, false));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    else if constexpr (__fp_format_of_v<From> == __fp_format::__fp8_e8m0) {
        // e8m0 has no sign bit: 0x00 -> 0, 0xff -> NaN, other values = 2^(field-127)
        const unsigned char field = __fp_get_storage(value);
        if (field == 0x00u) {
            return ::asc::std::__fp_cast<To>(0.0f);
        }
        if (field == 0xffu) {
            return ::asc::std::__fp_cast<To>(__builtin_nanf(""));
        }
        return ::asc::std::__fp_cast<To>(::asc::std::__detail::__fp8_decode(field, 8, 0, false));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    else if constexpr (__fp_format_of_v<To> == __fp_format::__fp8_e4m3) {
        return __fp_from_storage<To>(
            ::asc::std::__detail::__fp8_encode(::asc::std::__fp_cast<float>(value), 4, 3, true));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    else if constexpr (__fp_format_of_v<To> == __fp_format::__fp8_e5m2) {
        return __fp_from_storage<To>(
            ::asc::std::__detail::__fp8_encode(::asc::std::__fp_cast<float>(value), 5, 2, false));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    else if constexpr (__fp_format_of_v<To> == __fp_format::__fp8_e8m0) {
        return __fp_from_storage<To>(::asc::std::__detail::__e8m0_encode(::asc::std::__fp_cast<float>(value)));
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    else if constexpr (is_same_v<From, float>) {
        // float -> half/bfloat16_t/long double: compiler-native conversion (CCE device built-in)
        return static_cast<To>(value);
    } else if constexpr (__is_fp_v<From> && __is_fp_v<To>) {
        // remaining cross-format conversions of double/long double/half/bfloat16_t:
        // relayed through float as the pivot
        return ::asc::std::__fp_cast<To>(static_cast<float>(value));
    } else {
        static_assert(__always_false_v<To>, "Unsupported floating point conversion");
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_CAST_H
