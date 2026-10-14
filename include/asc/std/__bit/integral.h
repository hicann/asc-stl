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

#ifndef CANN_ASC_STL_ASC_STD___BIT_INTEGRAL_H
#define CANN_ASC_STL_ASC_STD___BIT_INTEGRAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/builtin.h>
#include <asc/std/__algorithm/max.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

// The shared <asc/__config> does not provide CANN_ASC_STL_DETAIL_ASSUME /
// ASSERT: inline minimal equivalents of their semantics, guarded by #ifndef so
// a future centralized definition wins.
#ifndef CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) __builtin_assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) ((void)sizeof(!(__VA_ARGS__)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSUME
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// Always a no-op on device (no assertion mechanism); on host, checked only
// when ASC_ENABLE_HOST_ASSERTIONS is explicitly enabled.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Floor of log2: the position of the highest set bit.
//!
//! The PTX `bfind`/`shl` fast path has no equivalent ASC intrinsic, while
//! `countl_zero` is verified on hardware (builtin clz, one form shared by
//! host/device/constexpr), so all three paths use the single expression
//! `digits - 1 - countl_zero`; for @p __t == 0 the result is -1, which wraps
//! as unsigned and is relied on by the callers below.
template <class _Tp>
CANN_ASC_STL_API constexpr uint32_t __bit_log2(_Tp __t) noexcept
{
    return static_cast<uint32_t>(numeric_limits<_Tp>::digits - 1) - static_cast<uint32_t>(::asc::std::countl_zero(__t));
}

//! @brief Minimum number of bits needed to represent @p value; 0 for
//! @p value == 0.
//!
//! For @p value == 0, __bit_log2 wraps to 0xFFFFFFFF and adding 1 yields 0.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> bit_width(T value) noexcept
{
    auto __ret = ::asc::std::__bit_log2(value) + 1;
    CANN_ASC_STL_DETAIL_ASSUME(__ret <= numeric_limits<T>::digits);
    return static_cast<int>(__ret);
}

//! @brief Smallest power of 2 not less than @p value.
//!
//! Measured on hardware, over-wide shifts (`1u << 32` etc.) in fact yield 0
//! (matching PTX semantics), but CCE emits -Wshift-count-overflow for them and
//! the C++ standard makes them undefined behavior. An explicit ternary guard is
//! therefore used instead of the `max(1, shl)` shift trick, keeping the 0/1
//! results on a constant branch.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, T> bit_ceil(T value) noexcept
{
    using _Up = _If<(sizeof(T) <= 4), uint32_t, T>;
    CANN_ASC_STL_DETAIL_ASSERT(
        value <= numeric_limits<T>::max() / 2, "bit_ceil overflow");  // NOLINT(build/include_what_you_use)
    // For value == 0, value - 1 is all ones, bit_width yields the width, and
    // the constant branch returns 1
    const auto __width = static_cast<uint32_t>(::asc::std::bit_width(static_cast<_Up>(value) - 1));
    const auto __ret = static_cast<T>(value <= 1 ? _Up{1} : _Up{1} << __width);
    CANN_ASC_STL_DETAIL_ASSUME(__ret >= value);
    return __ret;
}

//! @brief Largest power of 2 not greater than @p value; 0 for @p value == 0.
//!
//! As with bit_ceil: the 0 case lands on a constant branch and does not rely
//! on over-wide shift semantics.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, T> bit_floor(T value) noexcept
{
    using _Up = _If<(sizeof(T) <= 4), uint32_t, T>;
    const auto __log2 = ::asc::std::__bit_log2(static_cast<_Up>(value));
    const auto __ret = static_cast<T>(value == 0 ? _Up{0} : _Up{1} << __log2);
    CANN_ASC_STL_DETAIL_ASSUME(__ret >= value / 2 && __ret <= value);
    return __ret;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_INTEGRAL_H
