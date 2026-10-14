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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_OVERFLOW_HANDLER_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_OVERFLOW_HANDLER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/arithmetic.h>
#include <asc/std/__floating_point/constants.h>
#include <asc/std/__floating_point/format.h>
#include <asc/std/__floating_point/properties.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__type_traits/always_false.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Overflow handling policies (pure compile time, identical on host and
// device): __no_sat — Inf when the format has Inf, NaN when it has NaN, and
// the FP6/FP4 variants with neither take the positive maximum; __sat_finite —
// overflow takes max, underflow takes lowest. The source-side nv variant
// format names (__fp6_nv_* / __fp4_nv_*) map to the unsuffixed spellings in
// this tree (same format family; properties/format carry them as unsuffixed
// enumerators).

enum class __fp_overflow_handler_kind {
    __no_sat,
    __sat_finite,
};

template <__fp_overflow_handler_kind Kind>
struct __fp_overflow_handler;

// __fp_overflow_handler<__no_sat>

//! @brief Detects the FP6/FP4 no-Inf/NaN variant family (FP6 E2M3 / FP6 E3M2 /
//!        FP4 E2M1, judged by exponent-mantissa bit layout). The __fp_format
//!        enum carries no __fp6_e2m3/__fp6_e3m2/__fp4_e2m1 enumerators, so an
//!        equivalent bit-layout test is inlined; it is false for every format
//!        that currently exists.
template <__fp_format Fmt>
inline constexpr bool __fp_is_fp6_fp4_variant_v = (__fp_exp_nbits_v<Fmt> == 2 && __fp_mant_nbits_v<Fmt> == 3) ||
    (__fp_exp_nbits_v<Fmt> == 3 && __fp_mant_nbits_v<Fmt> == 2) ||
    (__fp_exp_nbits_v<Fmt> == 1 && __fp_mant_nbits_v<Fmt> == 2);

template <>
struct __fp_overflow_handler<__fp_overflow_handler_kind::__no_sat> {
    template <class T>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr T __handle_overflow() noexcept
    {
        constexpr auto fmt = __fp_format_of_v<T>;

        if constexpr (__fp_has_inf_v<fmt>) {
            return __fp_inf<T>();
        } else if constexpr (__fp_has_nan_v<fmt>) {
            return __fp_nan<T>();
        } else if constexpr (__fp_is_fp6_fp4_variant_v<fmt>) {
            // This variant family has no Inf/NaN: overflow maps to the positive
            // maximum
            return __fp_max<T>();
        } else {
            static_assert(__always_false_v<T>, "Unhandled floating-point format");
        }
    }

    template <class T>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr T __handle_underflow() noexcept
    {
        constexpr auto fmt = __fp_format_of_v<T>;

        if constexpr (__fp_has_inf_v<fmt>) {
            return __fp_neg(__fp_inf<T>());
        } else if constexpr (__fp_has_nan_v<fmt>) {
            return __fp_neg(__fp_nan<T>());
        } else if constexpr (__fp_is_fp6_fp4_variant_v<fmt>) {
            // This variant family has no Inf/NaN: underflow maps to the
            // positive maximum
            return __fp_max<T>();
        } else {
            static_assert(__always_false_v<T>, "Unhandled floating-point format");
        }
    }
};

// __fp_overflow_handler<__sat_finite>

template <>
struct __fp_overflow_handler<__fp_overflow_handler_kind::__sat_finite> {
    template <class T>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr T __handle_overflow() noexcept
    {
        return __fp_max<T>();
    }

    template <class T>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr T __handle_underflow() noexcept
    {
        return __fp_lowest<T>();
    }
};

// __fp_is_overflow_handler_v

template <class T>
inline constexpr bool __fp_is_overflow_handler_v = false;

template <class T>
inline constexpr bool __fp_is_overflow_handler_v<const T> = __fp_is_overflow_handler_v<T>;

template <class T>
inline constexpr bool __fp_is_overflow_handler_v<volatile T> = __fp_is_overflow_handler_v<T>;

template <class T>
inline constexpr bool __fp_is_overflow_handler_v<const volatile T> = __fp_is_overflow_handler_v<T>;

template <__fp_overflow_handler_kind Kind>
inline constexpr bool __fp_is_overflow_handler_v<__fp_overflow_handler<Kind>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_OVERFLOW_HANDLER_H
