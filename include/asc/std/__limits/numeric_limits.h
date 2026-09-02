/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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
template <class T>
struct numeric_limits {
    static constexpr bool is_specialized = false;
    static constexpr T min() noexcept
    {
        return T();
    }
    static constexpr T max() noexcept
    {
        return T();
    }
    static constexpr T lowest() noexcept
    {
        return T();
    }
    static constexpr int digits = 0;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 0;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = 0;
    static constexpr T epsilon() noexcept
    {
        return T();
    }
    static constexpr T round_error() noexcept
    {
        return T();
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
    static constexpr T infinity() noexcept
    {
        return T();
    }
    static constexpr T quiet_NaN() noexcept
    {
        return T();
    }
    static constexpr T signaling_NaN() noexcept
    {
        return T();
    }
    static constexpr T denorm_min() noexcept
    {
        return T();
    }
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;
};
#define CANN_ASC_STL_DETAIL_INTEGER_LIMITS(Type, Minimum, Maximum, Signed)                                  \
    template <>                                                                                             \
    struct numeric_limits<Type> {                                                                           \
        static constexpr bool is_specialized = true;                                                        \
        CANN_ASC_STL_API static constexpr Type min() noexcept                                               \
        {                                                                                                   \
            return Minimum;                                                                                 \
        }                                                                                                   \
        CANN_ASC_STL_API static constexpr Type max() noexcept                                               \
        {                                                                                                   \
            return Maximum;                                                                                 \
        }                                                                                                   \
        static constexpr Type lowest() noexcept                                                             \
        {                                                                                                   \
            return Minimum;                                                                                 \
        }                                                                                                   \
        static constexpr int digits = static_cast<int>(sizeof(Type) * CHAR_BIT) - static_cast<int>(Signed); \
        static constexpr int digits10 = digits * 301 / 1000;                                                \
        static constexpr int max_digits10 = 0;                                                              \
        static constexpr bool is_signed = Signed;                                                           \
        static constexpr bool is_integer = true;                                                            \
        static constexpr bool is_exact = true;                                                              \
        static constexpr int radix = 2;                                                                     \
        static constexpr Type epsilon() noexcept                                                            \
        {                                                                                                   \
            return 0;                                                                                       \
        }                                                                                                   \
        static constexpr Type round_error() noexcept                                                        \
        {                                                                                                   \
            return 0;                                                                                       \
        }                                                                                                   \
        static constexpr int min_exponent = 0;                                                              \
        static constexpr int min_exponent10 = 0;                                                            \
        static constexpr int max_exponent = 0;                                                              \
        static constexpr int max_exponent10 = 0;                                                            \
        static constexpr bool has_infinity = false;                                                         \
        static constexpr bool has_quiet_NaN = false;                                                        \
        static constexpr bool has_signaling_NaN = false;                                                    \
        static constexpr float_denorm_style has_denorm = denorm_absent;                                     \
        static constexpr bool has_denorm_loss = false;                                                      \
        static constexpr Type infinity() noexcept                                                           \
        {                                                                                                   \
            return 0;                                                                                       \
        }                                                                                                   \
        static constexpr Type quiet_NaN() noexcept                                                          \
        {                                                                                                   \
            return 0;                                                                                       \
        }                                                                                                   \
        static constexpr Type signaling_NaN() noexcept                                                      \
        {                                                                                                   \
            return 0;                                                                                       \
        }                                                                                                   \
        static constexpr Type denorm_min() noexcept                                                         \
        {                                                                                                   \
            return 0;                                                                                       \
        }                                                                                                   \
        static constexpr bool is_iec559 = false;                                                            \
        static constexpr bool is_bounded = true;                                                            \
        static constexpr bool is_modulo = !(Signed);                                                        \
        static constexpr bool traps = true;                                                                 \
        static constexpr bool tinyness_before = false;                                                      \
        static constexpr float_round_style round_style = round_toward_zero;                                 \
    };
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(char, CHAR_MIN, CHAR_MAX, CHAR_MIN < 0)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(signed char, SCHAR_MIN, SCHAR_MAX, true)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(unsigned char, 0, UCHAR_MAX, false)
template <>
struct numeric_limits<bool> {
    static constexpr bool is_specialized = true;
    static constexpr bool min() noexcept
    {
        return false;
    }
    static constexpr bool max() noexcept
    {
        return true;
    }
    static constexpr bool lowest() noexcept
    {
        return false;
    }
    static constexpr int digits = 1;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 0;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr int radix = 2;
    static constexpr bool epsilon() noexcept
    {
        return false;
    }
    static constexpr bool round_error() noexcept
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
    static constexpr bool infinity() noexcept
    {
        return false;
    }
    static constexpr bool quiet_NaN() noexcept
    {
        return false;
    }
    static constexpr bool signaling_NaN() noexcept
    {
        return false;
    }
    static constexpr bool denorm_min() noexcept
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
using __wchar_unsigned = make_unsigned_t<wchar_t>;
inline constexpr bool __wchar_is_signed = static_cast<wchar_t>(-1) < static_cast<wchar_t>(0);
inline constexpr wchar_t __wchar_max = static_cast<wchar_t>(
    __wchar_is_signed ? static_cast<__wchar_unsigned>(~__wchar_unsigned(0)) >> 1 : ~__wchar_unsigned(0));
inline constexpr wchar_t __wchar_min =
    __wchar_is_signed ? static_cast<wchar_t>(-__wchar_max - 1) : static_cast<wchar_t>(0);
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(wchar_t, __wchar_min, __wchar_max, __wchar_is_signed)
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(char8_t, 0, __UINT8_MAX__, false)
#endif
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(char16_t, 0, __UINT16_MAX__, false)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(char32_t, 0, __UINT32_MAX__, false)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(short, SHRT_MIN, SHRT_MAX, true)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(unsigned short, 0, USHRT_MAX, false)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(int, INT_MIN, INT_MAX, true)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(unsigned int, 0, UINT_MAX, false)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(long, LONG_MIN, LONG_MAX, true)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(unsigned long, 0, ULONG_MAX, false)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(long long, LLONG_MIN, LLONG_MAX, true)
CANN_ASC_STL_DETAIL_INTEGER_LIMITS(unsigned long long, 0, ULLONG_MAX, false)
#undef CANN_ASC_STL_DETAIL_INTEGER_LIMITS
#define CANN_ASC_STL_DETAIL_FLOAT_LIMITS(Type, Prefix, Huge, Nan, Nans)      \
    template <>                                                              \
    struct numeric_limits<Type> {                                            \
        static constexpr bool is_specialized = true;                         \
        static constexpr Type min() noexcept                                 \
        {                                                                    \
            return Prefix##_MIN;                                             \
        }                                                                    \
        static constexpr Type max() noexcept                                 \
        {                                                                    \
            return Prefix##_MAX;                                             \
        }                                                                    \
        static constexpr Type lowest() noexcept                              \
        {                                                                    \
            return -Prefix##_MAX;                                            \
        }                                                                    \
        static constexpr int digits = Prefix##_MANT_DIG;                     \
        static constexpr int digits10 = Prefix##_DIG;                        \
        static constexpr int max_digits10 = 2 + (digits * 30103L) / 100000L; \
        static constexpr bool is_signed = true;                              \
        static constexpr bool is_integer = false;                            \
        static constexpr bool is_exact = false;                              \
        static constexpr int radix = FLT_RADIX;                              \
        static constexpr Type epsilon() noexcept                             \
        {                                                                    \
            return Prefix##_EPSILON;                                         \
        }                                                                    \
        static constexpr Type round_error() noexcept                         \
        {                                                                    \
            return static_cast<Type>(0.5L);                                  \
        }                                                                    \
        static constexpr int min_exponent = Prefix##_MIN_EXP;                \
        static constexpr int min_exponent10 = Prefix##_MIN_10_EXP;           \
        static constexpr int max_exponent = Prefix##_MAX_EXP;                \
        static constexpr int max_exponent10 = Prefix##_MAX_10_EXP;           \
        static constexpr bool has_infinity = true;                           \
        static constexpr bool has_quiet_NaN = true;                          \
        static constexpr bool has_signaling_NaN = true;                      \
        static constexpr float_denorm_style has_denorm = denorm_present;     \
        static constexpr bool has_denorm_loss = false;                       \
        static constexpr Type infinity() noexcept                            \
        {                                                                    \
            return Huge;                                                     \
        }                                                                    \
        static constexpr Type quiet_NaN() noexcept                           \
        {                                                                    \
            return Nan;                                                      \
        }                                                                    \
        static constexpr Type signaling_NaN() noexcept                       \
        {                                                                    \
            return Nans;                                                     \
        }                                                                    \
        static constexpr Type denorm_min() noexcept                          \
        {                                                                    \
            return Prefix##_TRUE_MIN;                                        \
        }                                                                    \
        static constexpr bool is_iec559 = true;                              \
        static constexpr bool is_bounded = true;                             \
        static constexpr bool is_modulo = false;                             \
        static constexpr bool traps = false;                                 \
        static constexpr bool tinyness_before = false;                       \
        static constexpr float_round_style round_style = round_to_nearest;   \
    };
CANN_ASC_STL_DETAIL_FLOAT_LIMITS(float, FLT, __builtin_huge_valf(), __builtin_nanf(""), __builtin_nansf(""))
CANN_ASC_STL_DETAIL_FLOAT_LIMITS(double, DBL, __builtin_huge_val(), __builtin_nan(""), __builtin_nans(""))
CANN_ASC_STL_DETAIL_FLOAT_LIMITS(long double, LDBL, __builtin_huge_vall(), __builtin_nanl(""), __builtin_nansl(""))
#undef CANN_ASC_STL_DETAIL_FLOAT_LIMITS
template <class T>
struct numeric_limits<const T> : numeric_limits<T> {};
template <class T>
struct numeric_limits<volatile T> : numeric_limits<T> {};
template <class T>
struct numeric_limits<const volatile T>  // NOLINT(build/include_what_you_use)
    : numeric_limits<T> {                // NOLINT(build/include_what_you_use)
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__LIMITS_NUMERIC_LIMITS_H
