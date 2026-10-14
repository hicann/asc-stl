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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_EXT_H
#define CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_EXT_H

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
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Extended floating-point facets of __numeric_limits_impl. The device scalar
// types (half, bfloat16_t and the fp8 spellings) are AI-core builtin types
// gated by the capability macros inlined in
// __type_traits/is_extended_floating_point.h; the facets materialize their
// values from the raw bit patterns via bit_cast.

// ASC half

#if CANN_ASC_STL_DETAIL_HAS_HALF()
template <class _Tp>
class __numeric_limits_impl<half, __numeric_limits_type::__floating_point, _Tp> {
public:
    using type = _Tp;

    static constexpr bool is_specialized = true;

    static constexpr bool is_signed = true;
    static constexpr int digits = 11;
    static constexpr int digits10 = 3;
    static constexpr int max_digits10 = 5;
    CANN_ASC_STL_API static constexpr _Tp min() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x0400u));
    }
    CANN_ASC_STL_API static constexpr _Tp max() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7bffu));
    }
    CANN_ASC_STL_API static constexpr _Tp lowest() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0xfbffu));
    }

    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    CANN_ASC_STL_API static constexpr _Tp epsilon() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x1400u));
    }
    CANN_ASC_STL_API static constexpr _Tp round_error() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x3800u));
    }

    static constexpr int min_exponent = -13;
    static constexpr int min_exponent10 = -4;
    static constexpr int max_exponent = 16;
    static constexpr int max_exponent10 = 4;

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr _Tp infinity() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7c00u));
    }
    CANN_ASC_STL_API static constexpr _Tp quiet_NaN() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7e00u));
    }
    CANN_ASC_STL_API static constexpr _Tp signaling_NaN() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7d00u));
    }
    CANN_ASC_STL_API static constexpr _Tp denorm_min() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x0001u));
    }

    static constexpr bool is_iec559 = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF()

// ASC bfloat16

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
template <class _Tp>
class __numeric_limits_impl<bfloat16_t, __numeric_limits_type::__floating_point, _Tp> {
public:
    using type = _Tp;

    static constexpr bool is_specialized = true;

    static constexpr bool is_signed = true;
    static constexpr int digits = 8;
    static constexpr int digits10 = 2;
    static constexpr int max_digits10 = 4;
    CANN_ASC_STL_API static constexpr _Tp min() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x0080u));
    }
    CANN_ASC_STL_API static constexpr _Tp max() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7f7fu));
    }
    CANN_ASC_STL_API static constexpr _Tp lowest() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0xff7fu));
    }

    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    CANN_ASC_STL_API static constexpr _Tp epsilon() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x3c00u));
    }
    CANN_ASC_STL_API static constexpr _Tp round_error() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x3f00u));
    }

    static constexpr int min_exponent = -125;
    static constexpr int min_exponent10 = -37;
    static constexpr int max_exponent = 128;
    static constexpr int max_exponent10 = 38;

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr _Tp infinity() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7f80u));
    }
    CANN_ASC_STL_API static constexpr _Tp quiet_NaN() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7fc0u));
    }
    CANN_ASC_STL_API static constexpr _Tp signaling_NaN() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x7fa0u));
    }
    CANN_ASC_STL_API static constexpr _Tp denorm_min() noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        return ::asc::std::bit_cast<_Tp>(uint16_t(0x0001u));
    }

    static constexpr bool is_iec559 = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16()

// ASC fp8 e4m3

#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
template <class _Tp>
class __numeric_limits_impl<float8_e4m3_t, __numeric_limits_type::__floating_point, _Tp> {
public:
    using type = _Tp;

    static constexpr bool is_specialized = true;

    static constexpr bool is_signed = true;
    static constexpr int digits = 4;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 3;
    CANN_ASC_STL_API static constexpr _Tp min() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x08u));
    }
    CANN_ASC_STL_API static constexpr _Tp max() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7eu));
    }
    CANN_ASC_STL_API static constexpr _Tp lowest() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0xfeu));
    }

    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    CANN_ASC_STL_API static constexpr _Tp epsilon() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x20u));
    }
    CANN_ASC_STL_API static constexpr _Tp round_error() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x30u));
    }

    static constexpr int min_exponent = -6;
    static constexpr int min_exponent10 = -2;
    static constexpr int max_exponent = 8;
    static constexpr int max_exponent10 = 2;

    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr _Tp infinity() noexcept
    {
        return _Tp{};
    }
    CANN_ASC_STL_API static constexpr _Tp quiet_NaN() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7fu));
    }
    CANN_ASC_STL_API static constexpr _Tp signaling_NaN() noexcept
    {
        return _Tp{};
    }
    CANN_ASC_STL_API static constexpr _Tp denorm_min() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x01u));
    }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()

// ASC fp8 e5m2

#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
template <class _Tp>
class __numeric_limits_impl<float8_e5m2_t, __numeric_limits_type::__floating_point, _Tp> {
public:
    using type = _Tp;

    static constexpr bool is_specialized = true;

    static constexpr bool is_signed = true;
    static constexpr int digits = 3;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 2;
    CANN_ASC_STL_API static constexpr _Tp min() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x04u));
    }
    CANN_ASC_STL_API static constexpr _Tp max() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7bu));
    }
    CANN_ASC_STL_API static constexpr _Tp lowest() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0xfbu));
    }

    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    CANN_ASC_STL_API static constexpr _Tp epsilon() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x34u));
    }
    CANN_ASC_STL_API static constexpr _Tp round_error() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x38u));
    }

    static constexpr int min_exponent = -15;
    static constexpr int min_exponent10 = -5;
    static constexpr int max_exponent = 15;
    static constexpr int max_exponent10 = 4;

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr _Tp infinity() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7cu));
    }
    CANN_ASC_STL_API static constexpr _Tp quiet_NaN() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7eu));
    }
    CANN_ASC_STL_API static constexpr _Tp signaling_NaN() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7du));
    }
    CANN_ASC_STL_API static constexpr _Tp denorm_min() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x01u));
    }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()

// ASC fp8 e8m0

#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
template <class _Tp>
class __numeric_limits_impl<float8_e8m0_t, __numeric_limits_type::__floating_point, _Tp> {
public:
    using type = _Tp;

    static constexpr bool is_specialized = true;

    static constexpr bool is_signed = false;
    static constexpr int digits = 1;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 2;
    CANN_ASC_STL_API static constexpr _Tp min() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x00u));
    }
    CANN_ASC_STL_API static constexpr _Tp max() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0xfeu));
    }
    CANN_ASC_STL_API static constexpr _Tp lowest() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x00u));
    }

    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    CANN_ASC_STL_API static constexpr _Tp epsilon() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7fu));
    }
    CANN_ASC_STL_API static constexpr _Tp round_error() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0x7fu));
    }

    static constexpr int min_exponent = -127;
    static constexpr int min_exponent10 = -39;
    static constexpr int max_exponent = 127;
    static constexpr int max_exponent10 = 38;

    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr _Tp infinity() noexcept
    {
        return _Tp{};
    }
    CANN_ASC_STL_API static constexpr _Tp quiet_NaN() noexcept
    {
        return ::asc::std::bit_cast<_Tp>(uint8_t(0xffu));
    }
    CANN_ASC_STL_API static constexpr _Tp signaling_NaN() noexcept
    {
        return _Tp{};
    }
    CANN_ASC_STL_API static constexpr _Tp denorm_min() noexcept
    {
        return _Tp{};
    }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()

// __float128

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
template <>
class __numeric_limits_impl<__float128, __numeric_limits_type::__floating_point> {
public:
    using type = __float128;

    static constexpr bool is_specialized = true;

    static constexpr bool is_signed = true;
    static constexpr int digits = 113;
    static constexpr int digits10 = 33;
    static constexpr int max_digits10 = 36;

    CANN_ASC_STL_API static constexpr type min() noexcept
    {
        return 3.36210314311209350626267781732175260e-4932q;
    }
    CANN_ASC_STL_API static constexpr type max() noexcept
    {
        return 1.18973149535723176508575932662800702e+4932q;
    }
    CANN_ASC_STL_API static constexpr type lowest() noexcept
    {
        return -max();
    }

    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    CANN_ASC_STL_API static constexpr type epsilon() noexcept
    {
        return 1.92592994438723585305597794258492732e-34q;
    }
    CANN_ASC_STL_API static constexpr type round_error() noexcept
    {
        return 0.5q;
    }

    static constexpr int min_exponent = -16381;
    static constexpr int min_exponent10 = -4931;
    static constexpr int max_exponent = 16384;
    static constexpr int max_exponent10 = 4932;

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;

    CANN_ASC_STL_API static constexpr type infinity() noexcept
    {
        using _UInt128 = unsigned __int128;
        return ::asc::std::bit_cast<type>(_UInt128{0x7fff'0000'0000'0000} << 64);
    }
    CANN_ASC_STL_API static constexpr type quiet_NaN() noexcept
    {
        using _UInt128 = unsigned __int128;
        return ::asc::std::bit_cast<type>(_UInt128{0x7fff'8000'0000'0000} << 64);
    }
    CANN_ASC_STL_API static constexpr type signaling_NaN() noexcept
    {
        using _UInt128 = unsigned __int128;
        return ::asc::std::bit_cast<type>(_UInt128{0x7fff'4000'0000'0000} << 64);
    }
    CANN_ASC_STL_API static constexpr type denorm_min() noexcept
    {
        return 6.47517511943802511092443895822764655e-4966q;
    }

    static constexpr bool is_iec559 = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_EXT_H
