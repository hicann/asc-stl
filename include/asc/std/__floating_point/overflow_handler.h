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

// 溢出处置策略（纯编译期，host/device 同码）：__no_sat——有 Inf 取 Inf、
// 有 NaN 取 NaN、无二者的 FP6/FP4 变体取正最大值；__sat_finite——上溢取
// max、下溢取 lowest。源侧 nv 变体格式名（__fp6_nv_* / __fp4_nv_*）映射
// 为本树无后缀拼写（同一格式族，properties/format 已按无后缀枚举承载）。

enum class __fp_overflow_handler_kind {
    __no_sat,
    __sat_finite,
};

template <__fp_overflow_handler_kind Kind>
struct __fp_overflow_handler;

// __fp_overflow_handler<__no_sat>

//! @brief FP6/FP4 无 Inf/NaN 变体族探测（FP6 E2M3 / FP6 E3M2 / FP4 E2M1，
//!        按指数-尾数位布局判定）。master 的 __fp_format 枚举尚未承载
//!        __fp6_e2m3/__fp6_e3m2/__fp4_e2m1 枚举值，故按位布局内联等价
//!        判定；对现存全部格式恒为 false，枚举值合入后判定结果不变。
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
            // 该变体族无 Inf/NaN：上溢折算正最大值
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
            // 该变体族无 Inf/NaN：下溢折算正最大值
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
