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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H
#define CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__random/is_valid.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Safely convert a URNG draw value to float.
//!
//! On the dav-c310 AI Core, scalar uint32 -> float conversion sign-extends
//! as if the value were int32 when bit 31 is set (compile-time constant
//! folding is unaffected; only runtime values are). Split the unsigned
//! 32-bit value into a 24-bit high part and an 8-bit low part, convert each
//! safely, and recombine; the decomposition is bit-for-bit equivalent to the
//! direct IEEE conversion (brute-force verified over 2e6 samples including
//! rounding boundaries, zero differences), host semantics are unchanged, and
//! the device path produces correct results.
template <class Draw>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr float __asc_random_draw_to_float(Draw draw) noexcept
{
    const uint32_t value = static_cast<uint32_t>(draw);
    return static_cast<float>(static_cast<float>(value >> 8)) * 256.0f + static_cast<float>(value & 0xFFu);
}

//! @brief Dispatch the draw-value conversion on the target real type: float
//! with unsigned draws of at most 32 bits takes the safe decomposition; the
//! rest (host double, wider engine values) convert directly.
template <class RealType, class Draw>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr RealType __asc_random_draw_to_real(Draw draw) noexcept
{
    if constexpr (is_same_v<RealType, float> && __asc_random_is_valid_uinttype<Draw> && sizeof(Draw) <= 4) {
        return ::asc::std::__asc_random_draw_to_float(draw);
    } else {
        return static_cast<RealType>(draw);
    }
}

//! @brief The product contract restricts generate_canonical to float results
//! ("float result with delivered URBGs"; the double_excluded.fail negative
//! test pins this boundary): the primary template is deliberately
//! incomplete, so instantiating it with RealType != float is ill-formed.
template <class RealType>
struct __generate_canonical_result;

template <>
struct __generate_canonical_result<float> {
    using type = float;
};

//! @brief Generate a canonical floating-point value of the requested
//! precision in the half-open interval [0, 1) from a uniform random bit
//! generator.
//!
//! The draw count is determined by the target precision and the base-2
//! logarithm of the engine range (via __bit_log2); the pure-arithmetic path
//! has no platform dependency, so host and AI-core are unified. A result
//! that rounds up to exactly 1 is clamped to 1 - epsilon/2, the largest
//! representable value below 1, preserving the half-open [0, 1) contract.
template <class RealType, size_t Bits, class UniformRandomBitGenerator>
CANN_ASC_STL_API constexpr typename __generate_canonical_result<RealType>::type generate_canonical(
    UniformRandomBitGenerator& generator) noexcept
{
    constexpr size_t digits =
        static_cast<size_t>(numeric_limits<RealType>::digits);  // NOLINT(build/include_what_you_use)
    const size_t requested = Bits < digits ? Bits : digits;
    const size_t log_range = static_cast<size_t>(
        ::asc::std::__bit_log2<uint64_t>(generator.max() - generator.min() + static_cast<uint64_t>(1)));
    const size_t draws = requested / log_range + (requested % log_range != 0) + (requested == 0);
    const RealType range = static_cast<RealType>(generator.max() - generator.min()) + RealType(1);
    RealType scale = range;
    RealType sum = ::asc::std::__asc_random_draw_to_real<RealType>(generator() - generator.min());
    for (size_t index = 1; index < draws; ++index, scale *= range) {
        sum += ::asc::std::__asc_random_draw_to_real<RealType>(generator() - generator.min()) * scale;
    }
    const RealType result = sum / scale;
    return result < RealType(1) ? result : RealType(1) - static_cast<RealType>(__FLT_EPSILON__) / RealType(2);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H
