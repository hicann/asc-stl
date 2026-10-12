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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_HYPERBOLIC_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_HYPERBOLIC_FUNCTIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/abs.h>
#include <asc/std/__cmath/copysign.h>
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/inverse_trigonometric_functions.h>
#include <asc/std/__cmath/isfinite.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/logarithms.h>
#include <asc/std/__cmath/min_max.h>
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/exponential_functions.h>
#include <asc/std/__complex/logarithms.h>
#include <asc/std/__complex/roots.h>
#include <asc/std/__floating_point/constants.h>
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstdint>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

// Specialization of 1/sqrt(x); the pure-SIMT math API exposes a native
// reciprocal sqrt, other spaces and precisions keep the mathematically
// equivalent division path.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API T __internal_rsqrt_inverse_hyperbloic(T value) noexcept
{
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    if constexpr (is_same_v<T, float>) {
        return ::rsqrtf(value);
    }
#endif
    return T(1) / ::asc::std::sqrt(value);
}

template <class T>
struct alignas(2 * sizeof(T)) __asc_asinh_sqrt_return_hilo {
    T hi;
    T lo;
};

// An unsafe sqrt(hi + lo) extended precision sqrt: a Newton-Raphson
// refinement of an rsqrt seed over the double-double input, keeping both the
// high and the low result parts.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API __asc_asinh_sqrt_return_hilo<T> __internal_double_T_sqrt_unsafe(
    T hi, T lo) noexcept
{
    // rsqrt
    const T initial_guess = ::asc::std::__internal_rsqrt_inverse_hyperbloic<T>(hi);

    // Newton-Raphson, assume we have a reasonable rsqrt above and that we
    // don't need to update the first term (initial_guess).
    //     x_(n+1) = x_n - 0.5*x_n*((hi + lo)(x_n^2) - 1)

    // initial_guess^2:
    const T init_sq_hi = initial_guess * initial_guess;
    const T init_sq_lo = ::asc::std::fma(initial_guess, initial_guess, -init_sq_hi);

    // Times (hi + lo). We need to add the -1.0 here in an fma, or different
    // compilers (eg host vs device) optimize differently and give (sometimes
    // very) different results.
    const T hi_hi_hi = ::asc::std::fma(hi, init_sq_hi, T(-1.0));
    // Low part not needed for fp32/fp64, but might be if this is extended to
    // other types:
    // T hi_hi_lo = fma(hi, init_sq_hi, -hi_hi_hi);

    // Add all terms:
    const T full_term = hi_hi_hi + (::asc::std::fma(lo, init_sq_hi, hi * init_sq_lo) /*+ hi_hi_lo*/);

    const T correction_term = T(-0.5) * initial_guess * full_term;

    // rsqrt(hi + lo) is now estimated well by (initial_guess +
    // correction_term). Multiply everything by (hi + lo) to get sqrt(hi + lo):
    const T ans_hi_hi = hi * initial_guess;
    T ans_hi_lo = ::asc::std::fma(hi, initial_guess, -ans_hi_hi);

    // All terms needed, allow the compiler to pick which way to optimize this
    // to fma, same accuracy:
    ans_hi_lo += initial_guess * lo + correction_term * hi;

    return __asc_asinh_sqrt_return_hilo<T>{ans_hi_hi, ans_hi_lo};
}

// asinh

// Extended-precision evaluation with C99 Annex G special-value coverage: the
// |sqrt(z^2 + 1)| term is formed in double-double arithmetic, large inputs
// are scaled through the asinh(x) ~ log(2x) estimate, and the final log goes
// through log1p on |w| - 1 to avoid catastrophic cancellation.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> asinh(const complex<T>& value) noexcept
{
    // Uint of the same size as our fp type.
    using uint_t = __fp_storage_of_t<T>;

    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_max = __fp_exp_max_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_bias = __fp_exp_bias_v<__fp_format_of_v<T>>;

    // pi and ln2 spelled directly: the mathematical-constant accessor family
    // is float-specialized in this tree.
    constexpr T pi = static_cast<T>(3.141592653589793238462643383279502884L);
    constexpr T ln2 = static_cast<T>(0.693147180559945309417232121458176568L);

    T realx = ::asc::std::fabs(value.real());
    T imagx = ::asc::std::fabs(value.imag());

    // Special cases that do not pass through:
    if (!::asc::std::isfinite(realx) || !::asc::std::isfinite(imagx)) {
        // If z is (x,+inf) (for any positive finite x), the result is
        // (+inf, pi/2)
        if (::asc::std::isfinite(realx) && ::asc::std::isinf(imagx)) {
            return complex<T>(::asc::std::copysign(
                                  numeric_limits<T>::infinity(), value.real()),  // NOLINT(build/include_what_you_use)
                ::asc::std::copysign(T(0.5) * pi, value.imag()));
        }

        // If z is (+inf,y) (for any positive finite y), the result is
        // (+inf,+0)
        if (::asc::std::isinf(realx) && ::asc::std::isfinite(imagx)) {
            return complex<T>(::asc::std::copysign(
                                  numeric_limits<T>::infinity(), value.real()),  // NOLINT(build/include_what_you_use)
                ::asc::std::copysign(T(0), value.imag()));
        }

        // If z is (+inf,+inf), the result is (+inf, pi/4)
        if (::asc::std::isinf(realx) && ::asc::std::isinf(imagx)) {
            return complex<T>(::asc::std::copysign(
                                  numeric_limits<T>::infinity(), value.real()),  // NOLINT(build/include_what_you_use)
                ::asc::std::copysign(T(0.25) * pi, value.imag()));
        }

        // If z is (+inf,NaN), the result is (+inf,NaN)
        if (::asc::std::isinf(realx) && ::asc::std::isnan(imagx)) {
            return value;
        }

        // If z is (NaN,+0), the result is (NaN,+0)
        if (::asc::std::isnan(realx) && (imagx == T(0))) {
            return value;
        }

        // If z is (NaN,+inf), the result is (±INF,NaN) (the sign of the real
        // part is unspecified)
        if (::asc::std::isnan(realx) && ::asc::std::isinf(imagx)) {
            return complex<T>(value.imag(), numeric_limits<T>::quiet_NaN());  // NOLINT(build/include_what_you_use)
        }
    }

    // Special case that for various reasons does not pass easily through the
    // algorithm below:
    if ((realx == T(0)) && (imagx == T(1))) {
        return complex<T>(value.real(), ::asc::std::copysign(T(0.5) * pi, value.imag()));
    }

    // It is a little involved to account for large inputs in an
    // inlined-into-existing-code fashion. The easiest place to account for
    // large values appears to be here at the start. Use asinh(x) ~ log(2x)
    // for large x. Get the largest exponent that passes through the
    // algorithm without issue. This is ~(max_exponent / 4), with a small bias
    // to make sure edge cases get caught: ~254 for double, ~30 for float.
    constexpr int32_t max_allowed_exponent = (exp_max / 4) - 2;
    constexpr uint_t max_allowed_val_as_uint =
        (uint_t(max_allowed_exponent + exp_bias) << mant_nbits) | __fp_explicit_bit_mask_of_v<T>;

    // Check if the largest component of x is > 2^max_allowed_exponent:
    T x_big_factor = T(0);
    const T max = ::asc::std::fmax(realx, imagx);
    const bool x_big = ::asc::std::__fp_get_storage(max) > max_allowed_val_as_uint;

    if (x_big) {
        // We need max to be <= ~(2^max_allowed_exponent), but not small
        // enough that the asinh(x) ~ log(2x) estimate does not break down. We
        // are not able to reduce this with a single simple reduction, so we
        // do a fast/inlined frexp/ldexp:
        const int32_t exp_biased = static_cast<int32_t>(::asc::std::__fp_get_storage(max) >> mant_nbits);

        // Get a factor such that (max * exp_mul_factor) <= max_allowed_exponent:
        const uint_t exp_reduce_factor =
            (uint_t((2 * exp_max) + max_allowed_exponent - exp_biased) << mant_nbits) | __fp_explicit_bit_mask_of_v<T>;
        const T exp_mul_factor = ::asc::std::__fp_from_storage<T>(exp_reduce_factor);

        // Scale down to a working range.
        realx *= exp_mul_factor;
        imagx *= exp_mul_factor;

        x_big_factor = static_cast<T>((exp_biased - exp_max) - max_allowed_exponent) * ln2;
    }

    // Let the compiler pick which way to fma this, accuracy stays the same.
    const T diffx_m1 = realx * realx - (imagx - T(1)) * (imagx + T(1));

    // Get the real and imag parts of |sqrt(z^2 + 1)|^2. This equates to
    // calculating:
    //     sqrt((re*re + (im + 1.0)*(im + 1.0))*(re*re + (im - 1.0)*(im - 1.0)));
    // Where we need both the term inside the sqrt in extended precision, as
    // well as evaluating the sqrt itself in extended precision.

    // Get re^2 + im^2 + 1 in extended precision. The low part of re^2 doesn't
    // seem to matter.
    const T imagx_sq_hi = imagx * imagx;
    const T imagx_sq_lo = ::asc::std::fma(imagx, imagx, -imagx_sq_hi);

    const T x_abs_sq_hi = imagx_sq_hi;
    const T x_abs_sq_lo = ::asc::std::fma(realx, realx, imagx_sq_lo);

    // Add one:
    const T x_abs_sq_p1_hi = (x_abs_sq_hi + T(1));
    const T x_abs_sq_p1_lo = x_abs_sq_lo - ((x_abs_sq_p1_hi - T(1)) - x_abs_sq_hi);

    // Square:
    const T x_abs_sq_p1_sq_hi = x_abs_sq_p1_hi * x_abs_sq_p1_hi;
    T x_abs_sq_p1_sq_lo = ::asc::std::fma(x_abs_sq_p1_hi, x_abs_sq_p1_hi, -x_abs_sq_p1_sq_hi);

    // Add in the lower square terms, all needed:
    x_abs_sq_p1_sq_lo = ::asc::std::fma(x_abs_sq_p1_lo, (T(2) * x_abs_sq_p1_hi + x_abs_sq_p1_lo), x_abs_sq_p1_sq_lo);

    // Get x_abs_sq_p1_sq_hi/lo - 4.0*imagx_sq_hi/lo:
    // Subtract high parts:
    T inner_most_term_hi = x_abs_sq_p1_sq_hi - T(4) * imagx_sq_hi;
    T inner_most_term_lo = ((x_abs_sq_p1_sq_hi - inner_most_term_hi) - T(4) * imagx_sq_hi);
    // lo parts, all needed:
    inner_most_term_lo += x_abs_sq_p1_sq_lo - T(4) * imagx_sq_lo;

    // We can have some slightly bad cases here due to catastrophic
    // cancellation that can't be fixed easily. We still need to do the
    // extended-sqrt on these values, so we fix them now. It occurs around
    // "real ~= small" and "imag ~= (1 - small)", and imag < 1. Worked out
    // through targeted testing on fp64 and fp32.
    T realx_small_bound = T(1.0e-13);
    T imagx_close_bound = T(0.98);

    if constexpr (is_same_v<T, float>) {
        realx_small_bound = T(1.0e-5f);
        imagx_close_bound = T(0.9f);
    }

    if ((realx < realx_small_bound) && (imagx_close_bound < imagx) && (imagx <= T(1))) {
        // Get (real^2 + (1 - imag)^2) * (real^2 + (1 + imag)^2) in
        // double-double: term1 = (real^2 + (1 - imag)^2)
        const T term1_hi = (T(1) - imagx) * (T(1) - imagx);
        const T term1_lo = ::asc::std::fma(T(1) - imagx, T(1) - imagx, -term1_hi) + realx * realx;

        // Need (1.0 + imagx)^2 with nearly full accuracy.
        const T term2_sum_hi = (T(1) + imagx);
        const T term2_sum_lo = ((T(1) - term2_sum_hi) + imagx);

        const T term2_sq_hi = term2_sum_hi * term2_sum_hi;
        T term2_sq_lo = ::asc::std::fma(term2_sum_hi, term2_sum_hi, -term2_sq_hi);
        term2_sq_lo += T(2) * term2_sum_hi * term2_sum_lo;

        // Multiply term1_hi/lo and term2_sq_hi/lo:
        inner_most_term_hi = term1_hi * term2_sq_hi;
        inner_most_term_lo = ::asc::std::fma(term1_hi, term2_sq_hi, -inner_most_term_hi);
        // All needed:
        inner_most_term_lo += term1_hi * term2_sq_lo + term1_lo * term2_sq_hi;
    }

    // Normalize the above (assumed in the extended-sqrt function):
    const T norm_hi = inner_most_term_hi + inner_most_term_lo;
    const T norm_lo = -((norm_hi - inner_most_term_hi) - inner_most_term_lo);
    inner_most_term_hi = norm_hi;
    inner_most_term_lo = norm_lo;

    // Extended sqrt function:
    // (extended_sqrt_hi + extended_sqrt_lo) = sqrt(inner_most_term_hi + inner_most_term_lo)
    const __asc_asinh_sqrt_return_hilo<T> extended_sqrt_hilo =
        ::asc::std::__internal_double_T_sqrt_unsafe<T>(inner_most_term_hi, inner_most_term_lo);

    T extended_sqrt_hi = extended_sqrt_hilo.hi;
    T extended_sqrt_lo = extended_sqrt_hilo.lo;

    // 0.0, and some very particular values, do not survive this unsafe sqrt
    // function. This case occurs when (1 + x^2) is zero or denormal (and
    // rsqrt(x)*rsqrt(x) become inf).
    const T min_normal = ::asc::std::__fp_min<T>();

    if (inner_most_term_hi <= T(2) * min_normal) {
        extended_sqrt_hi = T(2) * realx;
        extended_sqrt_lo = T(0);
    }

    // Get sqrt(0.5*(extended_sqrt_hi + diffx_m1)). This can result in
    // catastrophic cancellation if diffx_m1 < 0; in this case we instead use
    // the equivalent (realx*imagx) / sqrt(0.5*(extended_sqrt_hi - diffx_m1)).
    const T inside_sqrt_term = T(0.5) * (::asc::std::fabs(diffx_m1) + extended_sqrt_hi);

    // Allow for rsqrt optimization: two slightly different paths depending
    // on whether the native reciprocal sqrt is available.
    const T recip_sqrt = ::asc::std::__internal_rsqrt_inverse_hyperbloic<T>(inside_sqrt_term);
    T pos_evaluation_real;

    // This reuses the sqrt already computed in recip_sqrt on the SIMT path,
    // and gets sqrt quickly using the rsqrt already calculated.
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    pos_evaluation_real = recip_sqrt * inside_sqrt_term;
#else
    pos_evaluation_real = ::asc::std::sqrt(inside_sqrt_term);
#endif

    // Here, in a happy coincidence(?), we happen to intermediately calculate
    // an accurate return value for the real part of the answer in the case
    // that realx is small, as you would obtain from the Taylor expansion of
    // asinh (~ real/sqrt(1 - imag^2)). The following parts of the
    // calculation result in bad catastrophic cancellation for this case, so
    // we save this intermediate value:
    const T small_x_real_return_val = realx * recip_sqrt;
    const T pos_evaluation_imag = imagx * small_x_real_return_val;

    const T sqrt_real_part = (diffx_m1 > T(0)) ? pos_evaluation_real : pos_evaluation_imag;
    const T sqrt_imag_part = (diffx_m1 > T(0)) ? pos_evaluation_imag : pos_evaluation_real;

    // For an accurate log, we calculate |(sqrt_real_part + i*sqrt_imag_part)| - 1
    // and use log1p. This can normally have bad catastrophic cancellation,
    // however we have retained enough accuracy to subtract fairly simply:
    const T m1 = extended_sqrt_hi - T(1);
    const T rem = -((m1 + T(1)) - extended_sqrt_hi);

    extended_sqrt_hi = m1;
    extended_sqrt_lo += rem;

    // Final sum before sending it to log1p, all terms needed. Add our sum via
    // three terms, adding equally sized components.
    const T sum1 = (x_abs_sq_hi + extended_sqrt_hi);
    const T sum2 = T(2) * (realx * sqrt_real_part + imagx * sqrt_imag_part);
    const T sum3 = (extended_sqrt_lo + x_abs_sq_lo);

    const T abs_sqrt_part_sq = sum1 + (sum2 + sum3);

    const T atan2_input1 = imagx + sqrt_imag_part;
    const T atan2_input2 = realx + sqrt_real_part;

    T ans_real = T(0.5) * ::asc::std::log1p(abs_sqrt_part_sq);
    const T ans_imag = ::asc::std::atan2(atan2_input1, atan2_input2);

    // The small |real| case, as mentioned above. Bounds found by testing.
    T realx_small_bound_override = T(2.220446e-16);

    if constexpr (is_same_v<T, float>) {
        realx_small_bound_override = T(6.0e-08f);
    }

    if (realx < realx_small_bound_override && imagx < T(1)) {
        ans_real = small_x_real_return_val;
    }

    ans_real += x_big_factor;

    // Copy signs back in:
    return complex<T>(::asc::std::copysign(ans_real, value.real()), ::asc::std::copysign(ans_imag, value.imag()));
}

// acosh

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> acosh(const complex<T>& value) noexcept
{
    // Uint of the same size as our fp type.
    using uint_t = __fp_storage_of_t<T>;

    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_max = __fp_exp_max_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_bias = __fp_exp_bias_v<__fp_format_of_v<T>>;

    constexpr T pi = static_cast<T>(3.141592653589793238462643383279502884L);
    constexpr T ln2 = static_cast<T>(0.693147180559945309417232121458176568L);

    T realx = ::asc::std::fabs(value.real());
    T imagx = ::asc::std::fabs(value.imag());

    // Special cases that do not pass through:
    if (!::asc::std::isfinite(realx) || !::asc::std::isfinite(imagx)) {
        // If z is (x,+inf) (for any finite x), the result is (+inf,pi/2).
        if (::asc::std::isfinite(realx) && ::asc::std::isinf(imagx)) {
            return complex<T>(numeric_limits<T>::infinity(),  // NOLINT(build/include_what_you_use)
                ::asc::std::copysign(T(0.5) * pi, value.imag()));
        }

        // If z is (-pi,y) (for any positive finite y), the result is
        // (+inf,pi). If z is (+pi,y) (for any positive finite y), the result
        // is (+inf,+0).
        if (::asc::std::isinf(realx) && ::asc::std::isfinite(imagx)) {
            const T imag_ret_value = (value.real() == numeric_limits<T>::infinity()) ? T(0.0) : pi;
            return complex<T>(realx, ::asc::std::copysign(imag_ret_value, value.imag()));
        }

        // If z is (-inf, +-inf), the result is (+inf ,+-3pi/4).
        if ((value.real() == -numeric_limits<T>::infinity()) &&  // NOLINT(build/include_what_you_use)
            ::asc::std::isinf(imagx)) {
            return complex<T>(numeric_limits<T>::infinity(),  // NOLINT(build/include_what_you_use)
                ::asc::std::copysign(T(0.75) * pi, value.imag()));
        }

        // If z is (+inf,+inf), the result is (+inf, pi/4)
        if ((value.real() == numeric_limits<T>::infinity()) &&  // NOLINT(build/include_what_you_use)
            ::asc::std::isinf(imagx)) {
            return complex<T>(numeric_limits<T>::infinity(),  // NOLINT(build/include_what_you_use)
                ::asc::std::copysign(T(0.25) * pi, value.imag()));
        }

        // If z is (NaN,+inf), the result is (+inf,NaN).
        if (::asc::std::isnan(realx) && ::asc::std::isinf(imagx)) {
            return complex<T>(numeric_limits<T>::infinity(),  // NOLINT(build/include_what_you_use)
                numeric_limits<T>::quiet_NaN());              // NOLINT(build/include_what_you_use)
        }

        // If z is (+-inf,NaN), the result is (+inf,NaN).
        if (::asc::std::isinf(realx) && ::asc::std::isnan(imagx)) {
            return complex<T>(numeric_limits<T>::infinity(), value.imag());  // NOLINT(build/include_what_you_use)
        }

        // If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and
        // FE_INVALID may be raised. Per C11 DR471, this holds for non-zero x
        // only. If z is (0,NaN), the result should be (NaN,pi/2).
        if ((realx == T(0)) && ::asc::std::isnan(imagx)) {
            return complex<T>(numeric_limits<T>::quiet_NaN(), T(0.5) * pi);  // NOLINT(build/include_what_you_use)
        }
    }

    // A case that for various reasons does not pass easily through the
    // algorithm below:
    if ((realx == T(1)) && (imagx == T(0))) {
        const T imag_ret_value = (value.real() == T(1)) ? T(0) : pi;
        return complex<T>(T(0), ::asc::std::copysign(imag_ret_value, value.imag()));
    }

    // The easiest place to account for large values appears to be here at the
    // start. Use acosh(x) ~ log(2x) for large x. Get the largest exponent
    // that passes through the algorithm without issue. This is
    // ~(max_exponent / 4), with a small bias to make sure edge cases get
    // caught: ~254 for double, ~30 for float.
    constexpr int32_t max_allowed_exponent = (exp_max / 4) - 2;
    constexpr uint_t max_allowed_val_as_uint =
        (uint_t(max_allowed_exponent + exp_bias) << mant_nbits) | __fp_explicit_bit_mask_of_v<T>;

    // Check if the largest component of x is > 2^max_allowed_exponent:
    T x_big_factor = T(0);
    const T max = ::asc::std::fmax(realx, imagx);
    const bool x_big = ::asc::std::__fp_get_storage(max) > max_allowed_val_as_uint;

    if (x_big) {
        // We need max to be <= ~(2^max_allowed_exponent), but not small
        // enough that the acosh(x) ~ log(2x) estimate does not break down. We
        // are not able to reduce this with a single simple reduction, so we
        // do a fast/inlined frexp/ldexp:
        const int32_t exp_biased = static_cast<int32_t>(::asc::std::__fp_get_storage(max) >> mant_nbits);

        // Get a factor such that (max * exp_mul_factor) <= max_allowed_exponent:
        const uint_t exp_reduce_factor =
            (uint_t((2 * exp_max) + max_allowed_exponent - exp_biased) << mant_nbits) | __fp_explicit_bit_mask_of_v<T>;
        const T exp_mul_factor = ::asc::std::__fp_from_storage<T>(exp_reduce_factor);

        // Scale down to a working range.
        realx *= exp_mul_factor;
        imagx *= exp_mul_factor;

        x_big_factor = static_cast<T>((exp_biased - exp_max) - max_allowed_exponent) * ln2;
    }

    const T diffx_m1 = (realx - T(1)) * (realx + T(1)) - imagx * imagx;

    // Get the real and imag parts of |sqrt(z^2 - 1)|^2 via pure algebra. This
    // equates to calculating:
    //     sqrt((im*im + (re + 1.0)*(re + 1.0))*(im*im + (re - 1.0)*(re - 1.0)));
    // Where we need both the term inside the sqrt in extended precision, as
    // well as evaluating the sqrt itself in extended precision.

    // Get re^2 + im^2 + 1 in extended precision. The low part of im^2 doesn't
    // seem to matter.
    const T realx_sq_hi = realx * realx;
    const T realx_sq_lo = ::asc::std::fma(realx, realx, -realx_sq_hi);

    const T x_abs_sq_hi = realx_sq_hi;
    const T x_abs_sq_lo = ::asc::std::fma(imagx, imagx, realx_sq_lo);

    // Add one:
    const T x_abs_sq_p1_hi = (x_abs_sq_hi + T(1));
    const T x_abs_sq_p1_lo = x_abs_sq_lo - ((x_abs_sq_p1_hi - T(1)) - x_abs_sq_hi);

    // Square:
    const T x_abs_sq_p1_sq_hi = x_abs_sq_p1_hi * x_abs_sq_p1_hi;
    T x_abs_sq_p1_sq_lo = ::asc::std::fma(x_abs_sq_p1_hi, x_abs_sq_p1_hi, -x_abs_sq_p1_sq_hi);

    // Add in the lower square terms, all needed:
    x_abs_sq_p1_sq_lo = ::asc::std::fma(x_abs_sq_p1_lo, (T(2) * x_abs_sq_p1_hi + x_abs_sq_p1_lo), x_abs_sq_p1_sq_lo);

    // Get x_abs_sq_p1_sq_hi/lo - 4.0*realx_sq_hi/lo:
    // Subtract high parts:
    T inner_most_term_hi = x_abs_sq_p1_sq_hi - T(4) * realx_sq_hi;
    T inner_most_term_lo = ((x_abs_sq_p1_sq_hi - inner_most_term_hi) - T(4) * realx_sq_hi);
    // lo parts, all needed:
    inner_most_term_lo += x_abs_sq_p1_sq_lo - T(4) * realx_sq_lo;

    // Differs from asinh slightly here; we can still get some cancellation
    // when real = (1.0 - eps) and imag ~ 0.0 but it's nowhere near as bad as
    // in asinh. We need a much smaller interval check than asinh in this
    // case. Bounds found experimentally.
    constexpr T realx_close_bound = (is_same_v<T, float>) ? T(0.99f) : T(0.99999);
    constexpr T imagx_small_bound = (is_same_v<T, float>) ? T(1.0e-6f) : T(1.0e-8);

    // Calculate the same thing, but in a more stable way on this interval.
    if ((imagx < imagx_small_bound) && (realx_close_bound < realx) && (realx <= T(1))) {
        // Need to get (imag^2 + (real - 1)^2) * (imag^2 + (1 + real)^2) in
        // double-double: term1 = (imag^2 + (real - 1)^2)
        const T term1_hi = (T(1) - realx) * (T(1) - realx);
        const T term1_lo = ::asc::std::fma(T(1) - realx, T(1) - realx, -term1_hi) + imagx * imagx;

        // Need (1.0 + realx)^2 with nearly full accuracy.
        const T term2_sum_hi = (T(1) + realx);
        const T term2_sum_lo = ((T(1) - term2_sum_hi) + realx);

        const T term2_sq_hi = term2_sum_hi * term2_sum_hi;
        T term2_sq_lo = ::asc::std::fma(term2_sum_hi, term2_sum_hi, -term2_sq_hi);
        term2_sq_lo += T(2) * term2_sum_hi * term2_sum_lo;

        // Multiply term1_hi/lo and term2_sq_hi/lo:
        inner_most_term_hi = term1_hi * term2_sq_hi;
        inner_most_term_lo = ::asc::std::fma(term1_hi, term2_sq_hi, -inner_most_term_hi);
        // All needed:
        inner_most_term_lo += term1_hi * term2_sq_lo + term1_lo * term2_sq_hi;
    }

    // Normalize the above (needed for calling the sqrt function below):
    const T norm_hi = inner_most_term_hi + inner_most_term_lo;
    const T norm_lo = -((norm_hi - inner_most_term_hi) - inner_most_term_lo);
    inner_most_term_hi = norm_hi;
    inner_most_term_lo = norm_lo;

    const __asc_asinh_sqrt_return_hilo<T> extended_sqrt_hilo =
        ::asc::std::__internal_double_T_sqrt_unsafe<T>(inner_most_term_hi, inner_most_term_lo);

    T extended_sqrt_hi = extended_sqrt_hilo.hi;
    T extended_sqrt_lo = extended_sqrt_hilo.lo;

    // 0.0, and some very particular values, do not survive this unsafe sqrt
    // function. This case occurs when (1 + x^2) is zero or denormal (and
    // rsqrt(x)*rsqrt(x) become inf).
    const T min_normal = ::asc::std::__fp_min<T>();

    if (inner_most_term_hi <= T(2) * min_normal) {
        extended_sqrt_hi = T(2) * imagx;
        extended_sqrt_lo = T(0);
    }

    // Get sqrt(0.5*(diffx_m1 + extended_sqrt_hi)). This can result in
    // catastrophic cancellation if diffx_m1 < 0; in this case we instead use
    // the equivalent realx*imagx/sqrt(0.5*(-diffx_m1 + extended_sqrt_hi).
    const T inside_sqrt_term = T(0.5) * (::asc::std::fabs(diffx_m1) + extended_sqrt_hi);

    // Allow for rsqrt optimization: two slightly different paths depending
    // on whether the native reciprocal sqrt is available.
    const T recip_sqrt = ::asc::std::__internal_rsqrt_inverse_hyperbloic<T>(inside_sqrt_term);
    T pos_evaluation_real;

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    pos_evaluation_real = recip_sqrt * inside_sqrt_term;
#else
    pos_evaluation_real = ::asc::std::sqrt(inside_sqrt_term);
#endif

    // Here, in a happy coincidence(?), we happen to intermediately calculate
    // an accurate return value for the real part of the answer in the case
    // that imagx is small, as you would obtain from the Taylor expansion of
    // acosh. The following parts of the calculation result in bad
    // catastrophic cancellation for this case, so we save this intermediate
    // value:
    const T small_x_imag_return_val = imagx * recip_sqrt;
    const T pos_evaluation_imag = realx * small_x_imag_return_val;

    const T sqrt_real_part = (diffx_m1 > T(0)) ? pos_evaluation_real : pos_evaluation_imag;
    const T sqrt_imag_part = (diffx_m1 > T(0)) ? pos_evaluation_imag : pos_evaluation_real;

    // For an accurate log, we calculate |(sqrt_real_part + i*sqrt_imag_part)| - 1
    // and use log1p. We need to evaluate this without any cancellations. This
    // can normally have bad catastrophic cancellation, however we have
    // retained enough accuracy to subtract fairly simply:
    const T m1 = extended_sqrt_hi - T(1);
    const T rem = -((m1 + T(1)) - extended_sqrt_hi);

    extended_sqrt_hi = m1;
    extended_sqrt_lo += rem;

    // Final sum before sending it to log1p, all terms needed. Add our sum via
    // three terms, there might be a better order.
    const T sum1 = (x_abs_sq_hi + extended_sqrt_hi);
    const T sum2 = T(2) * (imagx * sqrt_imag_part + realx * sqrt_real_part);
    const T sum3 = (extended_sqrt_lo + x_abs_sq_lo);

    const T abs_sqrt_part_sq = sum1 + (sum2 + sum3);

    // A small quirk of acosh, due to the position of the branch cut when we
    // call atan2 adding in signs helps:
    const T atan2_input1 = ::asc::std::copysign(imagx + sqrt_imag_part, value.imag());
    const T atan2_input2 = ::asc::std::copysign(realx + sqrt_real_part, value.real());

    T ans_real = T(0.5) * ::asc::std::log1p(abs_sqrt_part_sq);
    const T ans_imag = ::asc::std::atan2(atan2_input1, atan2_input2);

    // The small |real| case, as mentioned above. Bounds found by testing.
    T imagx_small_bound_override = T(1.0e-14);

    if constexpr (is_same_v<T, float>) {
        imagx_small_bound_override = T(1.0e-06f);
    }
    if (imagx < imagx_small_bound_override && realx < T(1)) {
        ans_real = small_x_imag_return_val;
    }

    ans_real += x_big_factor;

    // Copy signs back in:
    return complex<T>(ans_real, ::asc::std::copysign(ans_imag, value.imag()));
}

// atanh

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> atanh(const complex<T>& value) noexcept
{
    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_bias = __fp_exp_bias_v<__fp_format_of_v<T>>;

    constexpr T pi = static_cast<T>(3.141592653589793238462643383279502884L);
    constexpr T ln2 = static_cast<T>(0.693147180559945309417232121458176568L);

    const T realx = ::asc::std::fabs(value.real());
    const T imagx = ::asc::std::fabs(value.imag());

    if (!::asc::std::isfinite(value.real()) || !::asc::std::isfinite(value.imag())) {
        if (::asc::std::isnan(value.imag())) {
            if (::asc::std::isinf(value.real()) || value.real() == T(0)) {
                return complex<T>(::asc::std::copysign(T(0), value.real()), value.imag());
            }
            return complex<T>{value.imag(), value.imag()};
        }
        if (::asc::std::isinf(value.real()) || ::asc::std::isinf(value.imag())) {
            return complex<T>{
                ::asc::std::copysign(T(0), value.real()), ::asc::std::copysign(T(0.5) * pi, value.imag())};
        }
    }

    // A case that for various reasons does not pass easily through the
    // algorithm below:
    if ((realx == T(1)) && (imagx == T(0))) {
        return complex<T>{
            ::asc::std::copysign(numeric_limits<T>::infinity(), value.real()),  // NOLINT(build/include_what_you_use)
            value.imag()};
    }

    // The real part of atanh(x) is:
    //      0.25 * log1p(4 * real / ((1.0 - real)^2) + imag^2)
    // However there are underflow/overflow issues doing it directly. If
    // (real - 1)^2 + imag^2 overflows we can do some scalar scaling, and the
    // only time (real - 1)^2 + imag^2 underflows is if (real == 1.0) and
    // (imag^2 becomes 0). In this case we estimate (with an extra fix for
    // denormal imag) with: 0.5 * log1p(2 / imag).

    // Create const powers of 2 for over/underflow scaling:
    constexpr int32_t small_bound_exp = -(exp_bias / 2);
    const T small_bound = ::asc::std::__fp_set_exp<T>(T(1), small_bound_exp);

    const bool x_big =
        (realx * realx + imagx * imagx == numeric_limits<T>::infinity());  // NOLINT(build/include_what_you_use)
    const bool x_reduced_small = (realx == T(1)) && (imagx <= small_bound);

    const T two_m_x_large_scale_factor = T{T(0.25) * small_bound};
    T scaled_realx = realx;
    T scaled_imagx = imagx;
    if (x_big) {
        scaled_realx *= two_m_x_large_scale_factor;
        scaled_imagx *= two_m_x_large_scale_factor;
    } else {
        scaled_realx -= T(1.0);
    }

    // Separately get the top and bottom of:
    //      4.0 * real / ((1.0 - real)^2 + imag^2)
    T numerator = ::asc::std::fabs(value.real());  // Move the 4.0 factor below.
    T denominator = T(0.25) * (scaled_realx * scaled_realx + scaled_imagx * scaled_imagx);

    if (x_reduced_small) {
        // We want log1p(2.0 / imagx), however imagx can be denormal. Multiply
        // by 2^25, and account for it after log1p.
        numerator = T(1);

        // 2^25 for float, 2^54 for double.
        constexpr int32_t denormal_scale_exp = mant_nbits + 2;
        const T denormal_scale = ::asc::std::__fp_set_exp<T>(T(1), denormal_scale_exp);

        denominator = (imagx * denormal_scale);
    }

    T pre_log1p = numerator * (T(1) / denominator);

    // Correct for overflow:
    if (x_big) {
        // two_m_x_large_scale_factor^2 is denormal and causes issues, so we
        // multiply separately twice:
        pre_log1p = (pre_log1p * two_m_x_large_scale_factor) * two_m_x_large_scale_factor;
    }

    T ans_real = T(0.25) * ::asc::std::log1p(pre_log1p);

    const T atan2_input1 = value.imag();
    // 0.5 * (real^2 + imag^2 - 1)
    const T atan2_input2 =
        T(-0.5) * (::asc::std::fma(value.imag(), value.imag(), ::asc::std::fma(value.real(), value.real(), -T(1))));

    const T ans_imag = T(0.5) * ::asc::std::atan2(atan2_input1, atan2_input2);

    if (x_reduced_small) {
        // Getting (mant_bits + 3) * ln2 via templated arithmetic gives us one
        // less bit of accuracy than using a single constant alas.
        constexpr T ans_real_small_correction = T(0.5) * T{mant_nbits + 3} * ln2;
        ans_real = ::asc::std::fma(T(2), ans_real, ans_real_small_correction);
    }

    return complex<T>{::asc::std::copysign(ans_real, value.real()), ans_imag};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_INVERSE_HYPERBOLIC_FUNCTIONS_H
