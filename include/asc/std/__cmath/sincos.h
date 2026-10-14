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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_SINCOS_H
#define CANN_ASC_STL_ASC_STD___CMATH_SINCOS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__cmath/backend.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __sincos_result {
    T sin;
    T cos;
};

namespace __soft_trig_detail {
// Pure-f32 quadrant-aware sin/cos for vector-core images. Two-step argument
// reduction keeps r in [-pi/4, pi/4]; the minimax-style polynomials stay
// within ~1e-6 relative error on that range.
CANN_ASC_STL_HOST_DEVICE inline constexpr float __poly_sin(float r) noexcept
{
    const float r2 = r * r;
    return r * (1.0f + r2 * (-0.16666667f + r2 * (0.0083333310f + r2 * (-0.00019840874f + r2 * 2.7525562e-07f))));
}
CANN_ASC_STL_HOST_DEVICE inline constexpr float __poly_cos(float r) noexcept
{
    const float r2 = r * r;
    return 1.0f + r2 * (-0.5f + r2 * (0.041666638f + r2 * (-0.0013888378f + r2 * 2.4433157e-05f)));
}
CANN_ASC_STL_HOST_DEVICE inline __sincos_result<float> __sincos_poly(float value) noexcept
{
    // Round to nearest via the 2^23*1.5 magic add: k = nearest integer of
    // value * (2/pi), exact in f32 for the reduced-precision inputs the
    // runtime contract feeds.
    const float scaled = value * 0.6366197723f + 12582912.0f;
    const int k = static_cast<int>(scaled - 12582912.0f);
    const float r = value - static_cast<float>(k) * 1.5707963268f - static_cast<float>(k) * 4.371139e-08f;
    const float s = __poly_sin(r);
    const float c = __poly_cos(r);
    switch (k & 3) {
        case 0:
            return {s, c};
        case 1:
            return {c, -s};
        case 2:
            return {-s, -c};
        default:
            return {-c, s};
    }
}
}  // namespace __soft_trig_detail

CANN_ASC_STL_HOST_SIMT_API __sincos_result<float> __sincos(float value) noexcept
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    // Device scalar lane, routed through the backend macro so the devkit
    // version gate of <simt_api/math_functions.h> stays centralised in
    // backend.h: old-devkit SIMT lanes fall back to the discrete host
    // builtins instead of failing on the missing device header.
    return {CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(sinf, __builtin_sinf, (value)),
        CANN_ASC_STL_DETAIL_FLOAT_MATH_CALL(cosf, __builtin_cosf, (value))};
#elif CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    // Vector-core Host lane: no sincos intrinsic exists in this mode, so the
    // two directions are evaluated discretely through the same builtins that
    // back the public sin/cos here. Returning the input unchanged would feed
    // every complex exponential (exp/polar/sin/cos/...) silently wrong values.
    return __soft_trig_detail::__sincos_poly(value);
#else
    __sincos_result<float> result{};
    __builtin_sincosf(value, &result.sin, &result.cos);
    return result;
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_SINCOS_H
