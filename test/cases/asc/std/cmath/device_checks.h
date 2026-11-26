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

#ifndef ASC_STL_TEST_CMATH_DEVICE_CHECKS_H
#define ASC_STL_TEST_CMATH_DEVICE_CHECKS_H

#include <asc/std/cmath>
#include <asc/std/bit>

#include "binary64_checks.h"

namespace asc_stl_test_cmath {
struct math_outputs {
    int exponent;
    int quotient;
    float integral;
};

template <class T>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool extended_math(
    unsigned one_bits, unsigned two_bits, unsigned seed, math_outputs& results)
{
    namespace s = ::asc::std;
    using storage = s::__fp_storage_of_t<T>;
    const auto from_bits = [](unsigned bits) { return s::__fp_from_storage<T>(static_cast<storage>(bits)); };
    const auto bits = [](T value) { return s::__fp_get_storage(value); };
    const T zero = from_bits(0), one = from_bits(one_bits + seed - 7), two = from_bits(two_bits);
    if (bits(s::sqrt(one)) != one_bits || bits(s::cbrt(one)) != one_bits || bits(s::fabs(one)) != one_bits ||
        bits(s::exp(zero)) != one_bits || bits(s::exp2(one)) != two_bits || bits(s::expm1(zero)) != 0 ||
        bits(s::pow(two, one)) != two_bits || bits(s::erf(zero)) != 0 || bits(s::erfc(zero)) != one_bits ||
        bits(s::lgamma(one)) != 0 || bits(s::tgamma(one)) != one_bits)
        return false;
    if (bits(s::sin(zero)) != 0 || bits(s::cos(zero)) != one_bits || bits(s::tan(zero)) != 0 ||
        bits(s::asin(zero)) != 0 || bits(s::atan(zero)) != 0 || bits(s::acos(one)) != 0 ||
        bits(s::atan2(zero, one)) != 0 || bits(s::sinh(zero)) != 0 || bits(s::cosh(zero)) != one_bits ||
        bits(s::tanh(zero)) != 0 || bits(s::asinh(zero)) != 0 || bits(s::acosh(one)) != 0 || bits(s::atanh(zero)) != 0)
        return false;
    if (bits(s::log(one)) != 0 || bits(s::log10(one)) != 0 || bits(s::log2(two)) != one_bits ||
        bits(s::log1p(zero)) != 0 || bits(s::logb(two)) != one_bits || s::ilogb(two) != 1)
        return false;
    if (bits(s::ceil(one)) != one_bits || bits(s::floor(one)) != one_bits || bits(s::round(one)) != one_bits ||
        bits(s::trunc(one)) != one_bits || bits(s::rint(one)) != one_bits || bits(s::nearbyint(one)) != one_bits ||
        s::lrint(one) != 1 || s::llrint(one) != 1 || s::lround(one) != 1 || s::llround(one) != 1)
        return false;
    int& exponent = results.exponent;
    int& quotient = results.quotient;
    exponent = 0;
    quotient = 0;
    if (bits(s::frexp(two, &exponent)) != 2 * one_bits - two_bits || exponent != 2 ||
        bits(s::ldexp(one, 1)) != two_bits || bits(s::scalbn(one, 1)) != two_bits ||
        bits(s::scalbln(one, 1L)) != two_bits || bits(s::hypot(one, zero)) != one_bits ||
        bits(s::hypot(one, zero, zero)) != one_bits || bits(s::fdim(two, one)) != one_bits ||
        bits(s::fma(one, one, one)) != two_bits || bits(s::fmin(one, two)) != one_bits ||
        bits(s::fmax(one, two)) != two_bits || bits(s::fmod(two, one)) != 0 || bits(s::remainder(two, one)) != 0 ||
        bits(s::remquo(two, one, &quotient)) != 0 || (quotient & 7) != 2 ||
        bits(s::copysign(zero, from_bits(0x8000U))) != 0x8000U || bits(s::nextafter(one, two)) != one_bits + 1)
        return false;
    return true;
}

template <class T, unsigned ExponentBits, unsigned FractionBits>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool fp8_classification(unsigned seed, unsigned first, unsigned stride)
{
    namespace s = ::asc::std;
    for (unsigned i = first; i < 256; i += stride) {
        const unsigned bits = (i + seed) & 255U;
        const T value = s::__fp_from_storage<T>(static_cast<unsigned char>(bits));
        int category = FP_NORMAL;
        if constexpr (ExponentBits == 8) {
            if (bits == 255)
                category = FP_NAN;
        } else {
            const unsigned magnitude = bits & 127U;
            const unsigned exponent = magnitude >> FractionBits;
            const unsigned fraction = magnitude & ((1u << FractionBits) - 1);
            if (!exponent)
                category = fraction ? FP_SUBNORMAL : FP_ZERO;
            if constexpr (ExponentBits == 4) {
                if (magnitude == 127)
                    category = FP_NAN;
            } else if (exponent == 31) {
                category = fraction ? FP_NAN : FP_INFINITE;
            }
        }
        if (s::fpclassify(value) != category || s::isnan(value) != (category == FP_NAN) ||
            s::isinf(value) != (category == FP_INFINITE) || s::isnormal(value) != (category == FP_NORMAL) ||
            s::isfinite(value) != (category != FP_INFINITE && category != FP_NAN))
            return false;
    }
    return true;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool atan2_axis(float x, unsigned upper, unsigned lower)
{
    namespace s = ::asc::std;
    return s::bit_cast<unsigned>(s::atan2(0.0F, x)) == upper && s::bit_cast<unsigned>(s::atan2(-0.0F, x)) == lower &&
        s::bit_cast<unsigned>(s::atan2f(0.0F, x)) == upper && s::bit_cast<unsigned>(s::atan2f(-0.0F, x)) == lower;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool atan2_vertical(float y, unsigned expected)
{
    namespace s = ::asc::std;
    return s::bit_cast<unsigned>(s::atan2(y, 0.0F)) == expected &&
        s::bit_cast<unsigned>(s::atan2f(y, -0.0F)) == expected;
}

CANN_ASC_STL_API int check_atan2_axis(float one)
{
    namespace s = ::asc::std;
    // The sign of x selects zero or pi. The sign of y selects the side of the real axis.
    constexpr unsigned minus_zero = 0x80000000U, pi = 0x40490fdbU, minus_pi = 0xc0490fdbU;
    const float inf = s::bit_cast<float>(0x7f800000U), nan = s::bit_cast<float>(0x7fc01234U);
    if (!atan2_axis(one, 0, minus_zero) || !atan2_axis(-one, pi, minus_pi) || !atan2_axis(0.0F, 0, minus_zero) ||
        !atan2_axis(-0.0F, pi, minus_pi) || !atan2_axis(inf, 0, minus_zero) || !atan2_axis(-inf, pi, minus_pi) ||
        !atan2_axis(s::bit_cast<float>(1U), 0, minus_zero) ||
        !atan2_axis(s::bit_cast<float>(0x80000001U), pi, minus_pi))
        return 25;
    if (!s::isnan(s::atan2(0.0F, nan)) || !s::isnan(s::atan2(-0.0F, nan)) || !s::isnan(s::atan2f(0.0F, -nan)) ||
        !s::isnan(s::atan2f(-0.0F, -nan)))
        return 26;
    const unsigned magnitude = static_cast<unsigned>(one);
    constexpr unsigned half_pi = 0x3fc90fdbU, minus_half_pi = 0xbfc90fdbU;
    if (!atan2_vertical(s::bit_cast<float>(magnitude), half_pi) ||
        !atan2_vertical(s::bit_cast<float>(magnitude | minus_zero), minus_half_pi) ||
        !atan2_vertical(s::bit_cast<float>(0x007fffffU), half_pi) ||
        !atan2_vertical(s::bit_cast<float>(0x80800000U), minus_half_pi) || !atan2_vertical(one, half_pi) ||
        !atan2_vertical(-one, minus_half_pi) || !atan2_vertical(inf, half_pi) || !atan2_vertical(-inf, minus_half_pi))
        return 27;
    if (!s::isnan(s::atan2(nan, 0.0F)) || !s::isnan(s::atan2f(-nan, -0.0F)))
        return 26;
    return 0;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int elementary(float one)
{
    namespace s = ::asc::std;
    const float zero = one - 1;
    if (s::sqrt(one) != one || s::cbrt(-one) != -one || s::hypot(3.0F, 4 * one) != 5)
        return 1;
    // The three-argument form composes two rounded hypot operations.
    if (!(s::fabs(s::hypot(2 * one, 3.0F, 6.0F) - 7.0F) <= 0x1p-20F))
        return 1;
    if (s::exp(zero) != one || s::exp2(one) != 2 || s::expm1(zero) != 0 || s::log(one) != 0 || s::log1p(zero) != 0 ||
        s::log10(one) != 0 || s::log2(one) != 0 || s::logb(one) != 0 || s::ilogb(one) != 0 ||
        s::pow(2.0F, 3 * one) != 8)
        return 2;
    if (s::sin(zero) != 0 || s::cos(zero) != 1 || s::tan(zero) != 0 || s::atan(zero) != 0 || s::asin(zero) != 0 ||
        s::acos(one) != 0 || s::atan2(zero, one) != 0 || s::sinh(zero) != 0 || s::cosh(zero) != 1 ||
        s::tanh(zero) != 0 || s::asinh(zero) != 0 || s::acosh(one) != 0 || s::atanh(zero) != 0)
        return 3;
    if (s::erf(zero) != 0 || s::erfc(zero) != 1 || s::fabs(s::tgamma(3 * one) - 2.0F) > 0.00001F ||
        s::fabs(s::lgamma(one)) > 0.00001F)
        return 4;
    return 0;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int split_and_round(float one, math_outputs& results)
{
    namespace s = ::asc::std;
    const float x = -one - 0.5F;
    if (s::round(x) != -2 || s::trunc(x) != -1 || s::floor(x) != -2 || s::ceil(x) != -1 || s::rint(x) != -2 ||
        s::nearbyint(x) != -2 || s::lrint(x) != -2 || s::llrint(x) != -2 || s::lround(x) != -2 || s::llround(x) != -2)
        return 5;
    int& exponent = results.exponent;
    int& quotient = results.quotient;
    exponent = 0;
    quotient = 0;
    float& integral = results.integral;
    integral = 0;
    if (s::frexp(x, &exponent) != -0.75F || exponent != 1 || s::modf(x, &integral) != -0.5F || integral != -1 ||
        s::scalbn(x, 2) != -6 || s::scalbln(x, -1) != -0.75F || s::ldexp(one, -2) != 0.25F ||
        s::fmod(7 * one, 2.0F) != 1 || s::remainder(7 * one, 2.0F) != -1 || s::remquo(7 * one, 2.0F, &quotient) != -1 ||
        (quotient & 7) != 4)
        return 6;
    // Exact division, both directions of a tie, sign handling and subnormal remainders.
    if (s::remquof(2 * one, -one, &quotient) != 0 || quotient != -2 || s::remquof(5 * one, 2.0F, &quotient) != 1 ||
        quotient != 2 || s::remquof(-7 * one, 2.0F, &quotient) != 1 || quotient != -4 ||
        s::bit_cast<unsigned>(s::remquof(-4 * one, 2.0F, &quotient)) != 0x80000000U || quotient != -2 ||
        s::bit_cast<unsigned>(s::remquof(s::bit_cast<float>(5U), s::bit_cast<float>(2U), &quotient)) != 1 ||
        quotient != 2 || s::remquof(0x1p120F, one, &quotient) != 0 || quotient % 8 != 0)
        return 15;
    const auto split = [&](unsigned input, unsigned integer_bits, unsigned fraction_bits) {
        const auto fraction = s::modff(s::bit_cast<float>(input), &integral);
        return s::bit_cast<unsigned>(integral) == integer_bits && s::bit_cast<unsigned>(fraction) == fraction_bits;
    };
    if (!split(0x80000000u, 0x80000000u, 0x80000000u) || !split(0x00000001u, 0, 0x00000001u) ||
        !split(0xbe800000u, 0x80000000u, 0xbe800000u) || !split(0xbfc00000u, 0xbf800000u, 0xbf000000u) ||
        !split(0xcb000000u, 0xcb000000u, 0x80000000u) || !split(0x7f800000u, 0x7f800000u, 0) ||
        !split(0xff800000u, 0xff800000u, 0x80000000u) || !split(0x7fc00001u, 0x7fc00001u, 0x7fc00001u))
        return 9;
    return 0;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int classify_and_compare(float one)
{
    namespace s = ::asc::std;
    const float zero = one - 1;
    const float x = -one - 0.5F;
    const float nan = s::bit_cast<float>(0x7fc00001U), inf = s::bit_cast<float>(0x7f800000U);
    if (s::fpclassify(-zero) != FP_ZERO || s::fpclassify(s::bit_cast<float>(1u)) != FP_SUBNORMAL || !s::isnormal(one) ||
        !s::isfinite(x) || !s::isinf(inf) || !s::isnan(nan) || !s::signbit(s::copysign(zero, -one)) ||
        !s::isunordered(nan, one) || s::islessgreater(nan, one) || !s::isgreater(one, zero) ||
        !s::isgreaterequal(one, one) || !s::isless(zero, one) || !s::islessequal(-zero, zero))
        return 7;
    if (s::fmin(one, nan) != one || s::fmax(nan, one) != one || s::fdim(one, 3 * one) != 0 ||
        s::fma(one + 1, one + 2, -one) != 5 || s::lerp(-one, one, 0.25F) != -0.5F ||
        s::bit_cast<unsigned>(s::nextafter(one, 2 * one)) != 0x3f800001u)
        return 8;
    return 0;
}

CANN_ASC_STL_API int check_partition(int seed, void* workspace, unsigned first, [[maybe_unused]] unsigned stride)
{
    // Lane k visits k, k + stride, ... for each format. Only lane zero writes the shared math outputs.
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    if (!fp8_classification<float8_e4m3_t, 4, 3>(seed, first, stride))
        return 10;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    if (!fp8_classification<float8_e5m2_t, 5, 2>(seed, first, stride))
        return 11;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    if (!fp8_classification<float8_e8m0_t, 8, 0>(seed, first, stride))
        return 12;
#endif
    if (first != 0)
        return 0;
    const float one = static_cast<float>(seed) - 6.0F;
    auto& results = *static_cast<math_outputs*>(workspace);
    if (const int status = check_atan2_axis(one))
        return status;
    if (const int status = elementary(one))
        return status;
    if (const int status = split_and_round(one, results))
        return status;
    if (const int status = classify_and_compare(one))
        return status;
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    if (!extended_math<half>(0x3c00U, 0x4000U, seed, results))
        return 13;
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    if (!extended_math<bfloat16_t>(0x3f80U, 0x4000U, seed, results))
        return 14;
#endif
    return check_binary64(seed) ? 0 : 24;
}
CANN_ASC_STL_API int check(int seed, void* workspace)
{
    return check_partition(seed, workspace, 0, 1);
}
}  // namespace asc_stl_test_cmath

#endif  // ASC_STL_TEST_CMATH_DEVICE_CHECKS_H
