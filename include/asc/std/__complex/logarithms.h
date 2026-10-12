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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_LOGARITHMS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_LOGARITHMS_H

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
#include <asc/std/__cmath/abs.h>
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/inverse_trigonometric_functions.h>
#include <asc/std/__complex/arg.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/math.h>
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

// log

// 0.5 * log1p on [-0.25, 0.5]:
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float __internal_unsafe_log1p_poly(float x) noexcept
{
    float log1p_poly = 0.5f * -4.50736098e-2f;
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * 0.10464530f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * -0.13162985f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * 0.14478821f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * -0.16647165f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * 0.19990806f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * -0.25000098f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * 0.33333451f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * -0.5f);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5f * 1.0f);
    log1p_poly *= x;
    return log1p_poly;
}

// 0.5 * log1p on [-0.25, 0.5] (Host double polynomial; fp64 is a host-only
// math path):
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API double __internal_unsafe_log1p_poly(double x) noexcept
{
    double log1p_poly = 0.5 * -7.09111630733153322503e-3;
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 2.66022308034025677103e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -4.72224506011362787916e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 5.65972221291394378406e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -5.77824005018098968423e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 5.89181707234033569254e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -6.22470356657013820789e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 6.66071144648464480431e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -7.143929943708668406366e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 7.692821470788910320771e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -8.33332949182035986890e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 9.09088791817835584208e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -9.99999883706452485921e-2);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 0.11111111583539913517);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -0.12500000038299266536);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 0.14285714280067426940);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -0.16666666666197160751);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 0.20000000000032358560);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -0.25000000000001904032);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 0.33333333333333270421);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * -0.5);
    log1p_poly = ::asc::std::fma(log1p_poly, x, 0.5 * 1.0);
    log1p_poly *= x;
    return log1p_poly;
}
#endif  // Host double polynomial

// Bit-level range reduction plus a log1p polynomial: hypot(x, y)^2 is
// evaluated close to 1 with double-double high/low splitting, so log keeps
// near-libm accuracy without calling the heavy hypot/log pair, and denormal,
// NaN, infinite and zero inputs are handled explicitly.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> log(const complex<T>& value) noexcept
{
    // Uint of the same size as our fp type. Shouldn't need make_unsigned, but
    // just in case:
    using uint_t = make_unsigned_t<__fp_storage_of_t<T>>;

    // Some needed constants:
    constexpr uint_t mant_mask = __fp_mant_mask_of_v<T>;
    constexpr uint_t exp_mask = __fp_exp_mask_of_v<T>;

    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_bias = __fp_exp_bias_v<__fp_format_of_v<T>>;

    // Cut off the hi and low bit of exp_mask. 0x3F000000 for fp32,
    // 0x3FE0000000000000 for fp64 etc.
    constexpr uint_t exp_mask_of_half = ((exp_mask >> (mant_nbits + 2)) << (mant_nbits + 1));

    const T real_abs = ::asc::std::fabs(value.real());
    const T imag_abs = ::asc::std::fabs(value.imag());

    T max = (real_abs > imag_abs) ? real_abs : imag_abs;
    T min = (real_abs > imag_abs) ? imag_abs : real_abs;

    // Range-reduce so that abs(x) ~ 1 before taking the logarithm. The code
    // below inlines and removes these two calls:
    //    T max_reduced = ::asc::std::frexp(max, &exp);
    //    T min_reduced = ::asc::std::ldexp(min, -exp);

    // Unbiased exponent of 2.0*max.
    int32_t exp = static_cast<int32_t>(::asc::std::bit_cast<uint_t>(max) >> mant_nbits) - exp_bias + 1;

    // Quick frexp:
    const uint_t max_reduced_as_uint = (::asc::std::bit_cast<uint_t>(max) & mant_mask) | exp_mask_of_half;
    T max_reduced = ::asc::std::bit_cast<T>(max_reduced_as_uint);

    // Create an exponent for an inline ldexp(min, -exp).
    const uint_t exp_neg_as_uint = (static_cast<uint_t>(exp_bias - exp) << mant_nbits);
    const T exp_neg = ::asc::std::bit_cast<T>(exp_neg_as_uint);

    T min_reduced = min * exp_neg;

    // Slowpath, denormal/nan/zero/rare-underflow:
    if ((exp == (1 - exp_bias)) || (exp >= exp_bias)) {
        // Here exp can also be (eg for double) 3073, as fabs(NaN) can still
        // return a "negative" NaN, and our exponent extraction does not strip
        // the sign. We can still check for this with "exp >= 1025" as opposed
        // to "exp == 1025", which only catches "positive" NaNs.
        if (max == T(0.0) || exp >= (exp_bias + 2)) {
            // NaN/inf/0.0 (inf doesn't matter, gets fixed later by hypot).
            max_reduced = max;
        } else {
            if (exp >= exp_bias) {
                // Here exp is (eg for double) only 1023 or 1024. Create a
                // fast ldexp power of 2 as above underflows, and split it
                // into two separate multiplications. Inlined version of:
                //   min_reduced = ::asc::std::ldexp(min, -exp);
                const uint_t ldexp_factor_2_uint = (static_cast<uint_t>(exp_bias + mant_nbits - exp) << mant_nbits);
                const uint_t two_m_mant_bits = static_cast<uint_t>(-mant_nbits + exp_bias) << mant_nbits;

                const T ldexp_factor_1 = ::asc::std::bit_cast<T>(two_m_mant_bits);  // 2^(-mant_nbits)
                const T ldexp_factor_2 = ::asc::std::bit_cast<T>(ldexp_factor_2_uint);
                min_reduced = (min * ldexp_factor_1) * ldexp_factor_2;
            } else {
                // max is denormal (so min is also denormal or 0.0). Scale
                // things up by 2^mant_nbits then do the fast ldexp.
                const uint_t two_mant_bits = static_cast<uint_t>(mant_nbits + exp_bias) << mant_nbits;
                const T ldexp_factor = ::asc::std::bit_cast<T>(two_mant_bits);
                max_reduced = max * ldexp_factor;  // 2^mant_nbits
                min_reduced = min * ldexp_factor;  // 2^mant_nbits

                const int32_t exp_no_denorm_bias =
                    static_cast<int32_t>(::asc::std::bit_cast<uint_t>(max_reduced) >> mant_nbits) - exp_bias + 1;
                const uint_t ldexp_factor_no_denorm_bias = static_cast<uint_t>(exp_bias - exp_no_denorm_bias)
                    << mant_nbits;

                max_reduced *= ::asc::std::bit_cast<T>(ldexp_factor_no_denorm_bias);
                min_reduced *= ::asc::std::bit_cast<T>(ldexp_factor_no_denorm_bias);

                exp = exp_no_denorm_bias - mant_nbits;
            }
        }
    }

    // We now have max and min reduced so that 0.5 <= max <= 1.0. However, we
    // need to have it so hypot(max, min)^2 is reduced. At the moment we have:
    //   0.5 <= hypot(min_reduced, max_reduced) <= sqrt(2)
    // We will take the logarithm of this; for the most accuracy (and to
    // reduce the log1p polynomial length) we would like
    // hypot_sq_scaled to be close to 1.
    T hypot_sq_scaled = ::asc::std::fma(max_reduced, max_reduced, min_reduced * min_reduced);

    if (hypot_sq_scaled < T(0.5)) {
        max_reduced *= T(2.0);
        min_reduced *= T(2.0);
        exp -= 1;
    }

    // hypot(max_reduced, min_reduced) is now ~1.0. We can end up with large
    // ulp errors due to catastrophic cancellation with hypot, so we instead
    // calculate ((real^2 + imag^2) - 1) accurately and use log1p.
    const T max_2_hi = max_reduced * max_reduced;
    const T max_2_lo = ::asc::std::fma(max_reduced, max_reduced, -max_2_hi);

    const T min_2_hi = min_reduced * min_reduced;
    const T min_2_lo = ::asc::std::fma(min_reduced, min_reduced, -min_2_hi);

    T sum_hi = max_2_hi + min_2_hi;
    T sum_lo = min_2_hi + (max_2_hi - sum_hi);

    // Exact where it matters, with the previous range reduction.
    sum_hi -= T(1.0);

    // The compiler can rearrange the sum in brackets, same max error. Need
    // all terms.
    hypot_sq_scaled = sum_hi + (sum_lo + max_2_lo + min_2_lo);

    // We now need log1p(hypot_sq_scaled). The range of hypot_sq_scaled is too
    // large for a simple polynomial at the moment, and the log1p function
    // itself is quite heavy. We do yet more reduction using:
    //    log1p(x) = -ln(C) + log1p(C-1 + C*x)
    T exp_d = static_cast<T>(exp);

    // C = 2: log1p = ln(1/2) + log1p(1 + 2*x)
    if (hypot_sq_scaled < T(-0.25)) {
        hypot_sq_scaled = ::asc::std::fma(T(2.0), hypot_sq_scaled, T(1.0));
        exp_d -= T(0.5);
    }

    // C = 0.5: log1p = ln(2) + log1p(0.5 + 0.5*x)
    if (hypot_sq_scaled >= T(0.5)) {
        hypot_sq_scaled = ::asc::std::fma(T(0.5), hypot_sq_scaled, T(-0.5));
        exp_d += T(0.5);
    }

    // hypot_sq_scaled is now in [-0.25, 0.5]; a log1p polynomial estimate
    // applies. ln2 is spelled directly: the mathematical-constant accessor
    // family is float-specialized in this tree.
    constexpr T ln2 = static_cast<T>(0.693147180559945309417232121458176568L);
    const T log1p_poly = ::asc::std::__internal_unsafe_log1p_poly(hypot_sq_scaled);

    // Scale our answer back up.
    T abs_rescaled = ::asc::std::fma(ln2, exp_d, log1p_poly);

    // Fix x == 0.0.
    if (value.real() == T(0.0) && value.imag() == T(0.0)) {
        abs_rescaled = -numeric_limits<T>::infinity();  // NOLINT(build/include_what_you_use)
    }

    // Fix hypot inf/nan case:
    if ((max == numeric_limits<T>::infinity()) ||      // NOLINT(build/include_what_you_use)
        (min == numeric_limits<T>::infinity())) {      // NOLINT(build/include_what_you_use)
        abs_rescaled = numeric_limits<T>::infinity();  // NOLINT(build/include_what_you_use)
    }

    return complex<T>(abs_rescaled, ::asc::std::atan2(value.imag(), value.real()));
}

// log10

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> log10(const complex<T>& value) noexcept
{
    // log10(e) spelled directly: the mathematical-constant accessor family is
    // float-specialized in this tree.
    constexpr T log10e = static_cast<T>(0.434294481903251827651128918916605082L);
    return ::asc::std::log(value) * log10e;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_LOGARITHMS_H
