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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_ROOTS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_ROOTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/copysign.h>
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/roots.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/math.h>
#include <asc/std/__floating_point/mask.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

// The pure-SIMT math API exposes a native reciprocal sqrt; Host and
// unsupported precisions keep the mathematically equivalent 1/sqrt path.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API T __internal_rsqrt(T value) noexcept
{
    if constexpr (is_same_v<T, float>) {
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
        return ::rsqrtf(value);
#endif
    }
    return T(1) / ::asc::std::sqrt(value);
}

// sqrt

// Numerically robust complex square root: fma-accumulated |z|^2 with a
// three-interval range reduction (overflow / normal / denormal), an inlined
// hypot, and conjugate cancellation terms that avoid the catastrophic loss
// of (|z| +- re)/2 for either sign of the real part.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> sqrt(const complex<T>& value) noexcept
{
    using uint_t = __fp_storage_of_t<T>;

    constexpr int32_t max_exponent = __fp_exp_max_v<__fp_format_of_v<T>>;
    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_bias = __fp_exp_bias_v<__fp_format_of_v<T>>;

    const T re = value.real();
    const T im = value.imag();

    if (::asc::std::isinf(im)) {
        return complex<T>{numeric_limits<T>::infinity(), im};  // NOLINT(build/include_what_you_use)
    }

    if ((re == T(0)) && (im == T(0))) {
        return complex<T>{T(0), im};
    }

    // Pre-check to see if we over/underflow:
    const T x_abs_sq = ::asc::std::fma(re, re, im * im);

    // Get some bounds where re +- |x| won't overflow. Doesn't need to be too
    // exact, enough to cover extremal cases.
    // overflow bound = sqrt(MAX_FLOAT / 2)
    // underflow bound similar, but tweaked to allow for normalizing denormal
    // calculation.
    constexpr uint_t overflow_bound_exp =
        ((static_cast<uint_t>(((static_cast<uint_t>(max_exponent - 1)) >> 1) + exp_bias)) << mant_nbits) |
        __fp_explicit_bit_mask_of_v<T>;
    constexpr uint_t underflow_bound_exp =
        ((static_cast<uint_t>(((static_cast<uint_t>(-max_exponent + mant_nbits)) >> 1) + exp_bias)) << mant_nbits) |
        __fp_explicit_bit_mask_of_v<T>;

    const T overflow_bound = ::asc::std::__fp_from_storage<T>(overflow_bound_exp);
    const T underflow_bound = ::asc::std::__fp_from_storage<T>(underflow_bound_exp);

    // Prepare some range-reduction that simplifies the calculation and avoids
    // needing the full hypot function. Alas there is not a single splitting
    // point that works for all values, so we split into 3 intervals
    // (denormals are to blame).
    T ldexp_factor_1 = T(2.0);  // Power of 2 of the form 2^(2m + 1)
    T ldexp_factor_2 = T(0.5);  // 1/sqrt(2*ldexp_factor_1)
    T ldexp_combined = T(1.0);  // ldexp_factor_1*ldexp_factor_2

    if (x_abs_sq > overflow_bound) {
        // Construct some compile-time ldexp_factor_* powers of 2 for range
        // reduction. To guarantee |re|, |im| <= sqrt(MAX_FLOAT / 2) we can
        // multiply by some C with C <= 1.0 / sqrt(MAX_FLOAT / 2). We also
        // want C to be a power of 2, and for our algorithm, an odd power of
        // 2. Divide ~MAX_FLOAT by 2, sqrt. We also overshoot a little
        // (by + 2), to allow error accumulation near the boundary, so as to
        // not push us into intermediate INF territory.
        constexpr int reduction_exponent = ((max_exponent - 1) >> 1) + 2;

        // Make sure it's odd, and not bigger.
        constexpr int reduced_exponent = reduction_exponent - (1 - (reduction_exponent & 0x1));

        // Negate, add bias, and shift into the exponent mask.
        constexpr uint_t lxexp_1_uint =
            (uint_t(exp_bias - reduced_exponent) << uint_t(mant_nbits)) | __fp_explicit_bit_mask_of_v<T>;

        // ldexp_factor_2 = 1/sqrt(2*ldexp_factor_1)
        constexpr uint_t lxexp_2_uint =
            ((exp_bias + (uint_t(reduced_exponent - 1) >> 1)) << uint_t(mant_nbits)) | __fp_explicit_bit_mask_of_v<T>;

        // Set our scaling values:
        ldexp_factor_1 = ::asc::std::__fp_from_storage<T>(lxexp_1_uint);
        ldexp_factor_2 = ::asc::std::__fp_from_storage<T>(lxexp_2_uint);
        ldexp_combined = ldexp_factor_1 * ldexp_factor_2;
    }

    if (x_abs_sq < underflow_bound) {
        // Need some extra range compared to the overflow version to account
        // for denormals. Similar otherwise.
        constexpr int32_t min_denom_exponent = -max_exponent - mant_nbits;

        constexpr int reduction_exponent = ((min_denom_exponent - 1) >> 1) - 2;
        constexpr int reduced_exponent = reduction_exponent + (1 - (reduction_exponent & 0x1));

        constexpr uint_t lxexp_1_uint =
            (uint_t(exp_bias - reduced_exponent) << uint_t(mant_nbits)) | __fp_explicit_bit_mask_of_v<T>;
        constexpr uint_t lxexp_2_uint =
            ((exp_bias + (uint_t(reduced_exponent) >> 1)) << uint_t(mant_nbits)) | __fp_explicit_bit_mask_of_v<T>;

        // Set our scaling values:
        ldexp_factor_1 = ::asc::std::__fp_from_storage<T>(lxexp_1_uint);
        ldexp_factor_2 = ::asc::std::__fp_from_storage<T>(lxexp_2_uint);
        ldexp_combined = ldexp_factor_1 * ldexp_factor_2;
    }

    const T re_scaled = re * ldexp_factor_1;
    const T im_scaled = im * ldexp_factor_1;

    // An inlined hypot. Surprisingly, the final accuracy gets worse if you
    // try and make this hypot calculation more accurate for the case
    // (im >> re) by swapping the fma inputs, as the final result is not
    // symmetrical in im/re.
    T x_abs_scaled = ::asc::std::sqrt(::asc::std::fma(re_scaled, re_scaled, im_scaled * im_scaled));

    // Add in the hypot inf-nan override here to avoid a complicated inf/nan
    // check at the start.
    if (::asc::std::isinf(im) || ::asc::std::isinf(re)) {
        x_abs_scaled = numeric_limits<T>::infinity();  // NOLINT(build/include_what_you_use)
    }

    // These would be the ideal terms we want to compute, however we can get
    // catastrophic cancellation in either (depending on if re_scaled > 0 or
    // not).
    const T ans_re_sq = x_abs_scaled + re_scaled;
    const T ans_im_sq = x_abs_scaled - re_scaled;

    // Get rid of catastrophic cancellation issues by using conjugate:
    //  for x > 0:
    //  x - sqrt(x^2 + y^2) = -y^2 / (x + sqrt(x^2 + y^2))
    // Similarly for x < 0:
    //        x + sqrt(x^2 + y^2) = -y^2/(x - sqrt(x^2 + y^2))
    const bool im_part_is_hard = (re_scaled > T(0.0));
    T easy_part = im_part_is_hard ? ans_re_sq : ans_im_sq;

    const T sqrt_easy_part = ::asc::std::__internal_rsqrt<T>(easy_part);

    // (im_scaled) can have under/overflowed when scaled so we go back to
    // using (im) briefly. Multiply by (im) last to avoid over/underflow:
    const T hard_part = (im) * (ldexp_combined * sqrt_easy_part);

    easy_part = ldexp_factor_2 * ::asc::std::sqrt(easy_part);

    // Don't need fabs on the second line, but better for code generation:
    const T ans_re = im_part_is_hard ? easy_part : ::asc::std::fabs(hard_part);
    const T ans_im = im_part_is_hard ? ::asc::std::fabs(hard_part) : easy_part;

    return complex<T>{ans_re, ::asc::std::copysign(ans_im, im)};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_ROOTS_H
