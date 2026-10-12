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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_H
#define CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_H

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
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/cfloat>
#include <asc/std/climits>

CANN_ASC_STL_BEGIN_NAMESPACE

enum float_round_style {
    round_indeterminate = -1,
    round_toward_zero = 0,
    round_to_nearest = 1,
    round_toward_infinity = 2,
    round_toward_neg_infinity = 3
};
enum float_denorm_style { denorm_indeterminate = -1, denorm_absent = 0, denorm_present = 1 };

// Dispatch tag selecting the specialization family of __numeric_limits_impl:
// integral types share one generic implementation, bool keeps its dedicated
// facet, standard and extended floating-point types funnel into the
// floating-point facet (extended formats specialize it in
// __limits/numeric_limits_ext.h), and everything else keeps the unspecialized
// defaults.
enum class __numeric_limits_type {
    __integral,
    __bool,
    __floating_point,
    __other,
};

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __numeric_limits_type __make_numeric_limits_type() noexcept
{
    if constexpr (is_same_v<_Tp, bool>) {
        return __numeric_limits_type::__bool;
    } else if constexpr (is_integral_v<_Tp>) {
        return __numeric_limits_type::__integral;
    } else if constexpr (is_floating_point_v<_Tp> || __is_extended_floating_point_v<_Tp>) {
        return __numeric_limits_type::__floating_point;
    } else {
        return __numeric_limits_type::__other;
    }
}

template <class _Tp, __numeric_limits_type = __make_numeric_limits_type<_Tp>(), class _Up = _Tp>
class __numeric_limits_impl {
public:
    using type = _Tp;

    static constexpr bool is_specialized = false;
    CANN_ASC_STL_API static constexpr type min() noexcept
    {
        return type();
    }
    CANN_ASC_STL_API static constexpr type max() noexcept
    {
        return type();
    }
    CANN_ASC_STL_API static constexpr type lowest() noexcept
    {
        return type();
    }

    static constexpr int digits = 0;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 0;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = 0;
    CANN_ASC_STL_API static constexpr type epsilon() noexcept
    {
        return type();
    }
    CANN_ASC_STL_API static constexpr type round_error() noexcept
    {
        return type();
    }

    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;

    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr type infinity() noexcept
    {
        return type();
    }
    CANN_ASC_STL_API static constexpr type quiet_NaN() noexcept
    {
        return type();
    }
    CANN_ASC_STL_API static constexpr type signaling_NaN() noexcept
    {
        return type();
    }
    CANN_ASC_STL_API static constexpr type denorm_min() noexcept
    {
        return type();
    }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;
};

// Generic integral facet: min/max derive from the value representation
// itself, so signedness is detected at compile time instead of being spelled
// out per type.
template <class _Tp>
class __numeric_limits_impl<_Tp, __numeric_limits_type::__integral> {
public:
    using type = _Tp;

    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = type(-1) < type(0);
    static constexpr int digits = static_cast<int>(sizeof(type) * CHAR_BIT - is_signed);
    static constexpr int digits10 = digits * 3 / 10;
    static constexpr int max_digits10 = 0;
    CANN_ASC_STL_API static constexpr type min() noexcept
    {
        return static_cast<_Tp>(~max());
    }
    CANN_ASC_STL_API static constexpr type max() noexcept
    {
        using _Unsigned = make_unsigned_t<_Tp>;
        return static_cast<_Tp>(static_cast<_Unsigned>(~_Unsigned{0}) >> static_cast<int>(is_signed));
    }
    CANN_ASC_STL_API static constexpr type lowest() noexcept
    {
        return min();
    }

    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr int radix = 2;
    CANN_ASC_STL_API static constexpr type epsilon() noexcept
    {
        return type(0);
    }
    CANN_ASC_STL_API static constexpr type round_error() noexcept
    {
        return type(0);
    }

    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr type infinity() noexcept
    {
        return type(0);
    }
    CANN_ASC_STL_API static constexpr type quiet_NaN() noexcept
    {
        return type(0);
    }
    CANN_ASC_STL_API static constexpr type signaling_NaN() noexcept
    {
        return type(0);
    }
    CANN_ASC_STL_API static constexpr type denorm_min() noexcept
    {
        return type(0);
    }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = !is_signed;
    // Integer division only traps on targets where it raises a signal
    // (x86-64 Linux, pnacl, wasm); AArch64-family targets — including the
    // AI-core backends — yield zero instead of trapping.
#if ((defined(__x86_64__) || defined(_M_X64)) && defined(__linux__)) || defined(__pnacl__) || defined(__wasm__)
    static constexpr bool traps = true;
#else
    static constexpr bool traps = false;
#endif
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;
};

template <>
class __numeric_limits_impl<bool, __numeric_limits_type::__bool> {
public:
    using type = bool;
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = false;
    static constexpr int digits = 1;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 0;
    CANN_ASC_STL_API static constexpr type min() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr type max() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr type lowest() noexcept
    {
        return false;
    }
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr int radix = 2;
    CANN_ASC_STL_API static constexpr type epsilon() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr type round_error() noexcept
    {
        return false;
    }
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr type infinity() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr type quiet_NaN() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr type signaling_NaN() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr type denorm_min() noexcept
    {
        return false;
    }
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;
};

template <>
class __numeric_limits_impl<float, __numeric_limits_type::__floating_point> {
public:
    using type = float;
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = true;
    static constexpr int digits = FLT_MANT_DIG;
    static constexpr int digits10 = FLT_DIG;
    static constexpr int max_digits10 = 2 + (digits * 30103l) / 100000l;
    CANN_ASC_STL_API static constexpr type min() noexcept
    {
        return FLT_MIN;
    }
    CANN_ASC_STL_API static constexpr type max() noexcept
    {
        return FLT_MAX;
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
        return FLT_EPSILON;
    }
    CANN_ASC_STL_API static constexpr type round_error() noexcept
    {
        return 0.5F;
    }
    static constexpr int min_exponent = FLT_MIN_EXP;
    static constexpr int min_exponent10 = FLT_MIN_10_EXP;
    static constexpr int max_exponent = FLT_MAX_EXP;
    static constexpr int max_exponent10 = FLT_MAX_10_EXP;
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    CANN_ASC_STL_API static constexpr type infinity() noexcept
    {
        return __builtin_huge_valf();
    }
    CANN_ASC_STL_API static constexpr type quiet_NaN() noexcept
    {
        return __builtin_nanf("");
    }
    CANN_ASC_STL_API static constexpr type signaling_NaN() noexcept
    {
        return __builtin_nansf("");
    }
    CANN_ASC_STL_API static constexpr type denorm_min() noexcept
    {
        return FLT_TRUE_MIN;
    }
    static constexpr bool is_iec559 = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};

template <>
class __numeric_limits_impl<double, __numeric_limits_type::__floating_point> {
public:
    // AI Core scalar code does not support double-precision operations. Keep
    // the metadata visible during CCE compilation, but do not mark the value
    // producing functions as device-callable.
    using type = double;
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = true;
    static constexpr int digits = DBL_MANT_DIG;
    static constexpr int digits10 = DBL_DIG;
    static constexpr int max_digits10 = 2 + (digits * 30103l) / 100000l;
    static constexpr type min() noexcept
    {
        return DBL_MIN;
    }
    static constexpr type max() noexcept
    {
        return DBL_MAX;
    }
    static constexpr type lowest() noexcept
    {
        return -max();
    }
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    static constexpr type epsilon() noexcept
    {
        return DBL_EPSILON;
    }
    static constexpr type round_error() noexcept
    {
        return 0.5;
    }
    static constexpr int min_exponent = DBL_MIN_EXP;
    static constexpr int min_exponent10 = DBL_MIN_10_EXP;
    static constexpr int max_exponent = DBL_MAX_EXP;
    static constexpr int max_exponent10 = DBL_MAX_10_EXP;
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    static constexpr type infinity() noexcept
    {
        return __builtin_huge_val();
    }
    static constexpr type quiet_NaN() noexcept
    {
        return __builtin_nan("");
    }
    static constexpr type signaling_NaN() noexcept
    {
        return __builtin_nans("");
    }
    static constexpr type denorm_min() noexcept
    {
        return DBL_TRUE_MIN;
    }
    static constexpr bool is_iec559 = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};

// Unlike the source tree, the long double facet stays unconditionally
// defined: the public contract requires numeric_limits to stay instantiable
// for every standard arithmetic type in every compilation mode, and the
// metadata below is compile-time constant regardless of AI-core support for
// long double arithmetic.
template <>
class __numeric_limits_impl<long double, __numeric_limits_type::__floating_point> {
public:
    using type = long double;
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = true;
    static constexpr int digits = LDBL_MANT_DIG;
    static constexpr int digits10 = LDBL_DIG;
    static constexpr int max_digits10 = 2 + (digits * 30103l) / 100000l;
    static constexpr type min() noexcept
    {
        return LDBL_MIN;
    }
    static constexpr type max() noexcept
    {
        return LDBL_MAX;
    }
    static constexpr type lowest() noexcept
    {
        return -max();
    }
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = FLT_RADIX;
    static constexpr type epsilon() noexcept
    {
        return LDBL_EPSILON;
    }
    static constexpr type round_error() noexcept
    {
        return 0.5L;
    }
    static constexpr int min_exponent = LDBL_MIN_EXP;
    static constexpr int min_exponent10 = LDBL_MIN_10_EXP;
    static constexpr int max_exponent = LDBL_MAX_EXP;
    static constexpr int max_exponent10 = LDBL_MAX_10_EXP;
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = false;
    static constexpr type infinity() noexcept
    {
        return __builtin_huge_vall();
    }
    static constexpr type quiet_NaN() noexcept
    {
        return __builtin_nanl("");
    }
    static constexpr type signaling_NaN() noexcept
    {
        return __builtin_nansl("");
    }
    static constexpr type denorm_min() noexcept
    {
        return LDBL_TRUE_MIN;
    }
    static constexpr bool is_iec559 = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest;
};

template <class _Tp>
class numeric_limits : public __numeric_limits_impl<_Tp> {};

template <class _Tp>
class numeric_limits<const _Tp> : public numeric_limits<_Tp> {};

template <class _Tp>
class numeric_limits<volatile _Tp> : public numeric_limits<_Tp> {};

template <class _Tp>
class numeric_limits<const volatile _Tp>  // NOLINT(build/include_what_you_use)
    : public numeric_limits<_Tp> {        // NOLINT(build/include_what_you_use)
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_H
