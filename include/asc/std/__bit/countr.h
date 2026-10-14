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

#ifndef CANN_ASC_STL_ASC_STD___BIT_COUNTR_H
#define CANN_ASC_STL_ASC_STD___BIT_COUNTR_H

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
#include <asc/std/__bit/countl.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

// The shared <asc/__config> does not provide CANN_ASC_STL_DETAIL_ASSUME /
// PRAGMA_UNROLL_FULL: inline minimal equivalents of their semantics, guarded
// by #ifndef so a future centralized definition wins.
#ifndef CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) __builtin_assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) ((void)sizeof(!(__VA_ARGS__)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSUME
#ifndef CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || defined(__clang__)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() _Pragma("unroll")
#elif defined(__GNUC__) && __GNUC__ >= 8
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() _Pragma("GCC unroll 65534")
#else
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
#endif
#endif  // CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Core implementation of trailing-zero counting.
//!
//! __builtin_ctz/ctzll are usable and correct on CANN 9.2 hardware, but the
//! CANN 9.0.0 dav vector-core backend lowers ctz (64-bit in particular) to a
//! floating-point conversion path (fp_to_uint) that cannot be selected. For
//! consistency across CANN versions, everything uses the "lowest set bit +
//! leading zeros" identity: for v != 0, v & -v == 2^k where k is the number of
//! trailing zeros, hence countr = digits - 1 - countl_zero(v & -v); the
//! primitives involved (negation, bitwise and, the countl_zero already verified
//! on both backends) are reliable on host and device alike.
template <typename _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __countr_zero_impl(_Tp __v) noexcept
{
    static_assert(is_same_v<_Tp, uint32_t> || is_same_v<_Tp, uint64_t>);
    if (__v == 0) {
        return static_cast<int>(numeric_limits<_Tp>::digits);
    }
    constexpr int __digits = numeric_limits<_Tp>::digits;
    const _Tp __lowest = __v & static_cast<_Tp>(-__v);
    return static_cast<int>(__digits - 1 - ::asc::std::countl_zero(__lowest));
}

//! @brief Counts the binary trailing zeros of @p value; returns the type's
//! width when @p value is 0.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> countr_zero(T value) noexcept
{
    int __count{};
    if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        using _Sp = _If<(sizeof(T) <= sizeof(uint32_t)), uint32_t, uint64_t>;
        __count = (value != 0) ? ::asc::std::__countr_zero_impl(static_cast<_Sp>(value)) :
                                 static_cast<int>(numeric_limits<T>::digits);
    } else {
        // Types wider than 64 bits: scan 64-bit chunks from the low end up,
        // where the trailing zeros live.
        CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
        for (__SIZE_TYPE__ __index = 0; __index < sizeof(T) / sizeof(uint64_t); ++__index) {
            const auto __value64 = static_cast<uint64_t>(value);
            if (__value64 != 0) {
                __count += ::asc::std::countr_zero(__value64);
                break;
            }
            __count += numeric_limits<uint64_t>::digits;
            value >>= numeric_limits<uint64_t>::digits;
        }
    }
    CANN_ASC_STL_DETAIL_ASSUME(
        __count >= 0 && __count <= numeric_limits<T>::digits);  // NOLINT(build/include_what_you_use)
    return __count;
}

//! @brief Counts the binary trailing ones of @p value (as trailing zeros of
//! the bitwise negation).
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> countr_one(T value) noexcept
{
    return ::asc::std::countr_zero(static_cast<T>(~value));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_COUNTR_H
