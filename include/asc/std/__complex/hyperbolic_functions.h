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
#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_HYPERBOLIC_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_HYPERBOLIC_FUNCTIONS_H

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
#include <asc/std/__cmath/exponential_functions.h>
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/hyperbolic_functions.h>
#include <asc/std/__cmath/isfinite.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/sincos.h>
#include <asc/std/__cmath/signbit.h>
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__floating_point/fp.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

// sinh

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> sinh(const complex<T>& value) noexcept
{
    // Need to distinguish +-0.0, use signbit rather than >
    const bool x_neg = ::asc::std::signbit(value.real());

    const T imag_x = x_neg ? -value.imag() : value.imag();
    T real_x_abs = ::asc::std::fabs(value.real());

    // Purge some special cases that don't pass through correctly:
    if ((!::asc::std::isfinite(imag_x)) && ((real_x_abs == T(0)) || (real_x_abs == numeric_limits<T>::infinity()))) {
        return complex<T>{value.real(), numeric_limits<T>::quiet_NaN()};  // NOLINT(build/include_what_you_use)
    }
    if (::asc::std::isnan(real_x_abs) && (imag_x == T(0))) {
        return value;
    }

    const auto [sin_imag, cos_imag] = ::asc::std::__sincos(imag_x);

    // Using ans = {sinh(re) * cos(im), cosh(re) * sin(im)} results in
    // intermediate overflows where eg cosh(re) overflows, but
    // cosh(re) * sin(im) does not. We scale our inputs to avoid this.
    // Rather than examining exponents, we save computation by pre-selecting
    // 2 separate intervals that cover our problematic overflow interval.
    // Use sinh(x) ~= cosh(x) ~= exp(x)/2 for large x. Need two intervals to
    // ensure the reduced values do not break the sinh(x) ~= cosh(x) ~=
    // exp(x)/2 estimate.

    // We need eg cosh(x) * sin(y) to not have intermediate overflow. We find
    // bounds where the final result will overflow no matter the (non-zero)
    // value of y. sin(y) can attain the smallest denormal value, we calculate
    // the largest value of x where cosh(x) * sin(y) is still finite. This is
    // attained at acosh(x) * MIN_DENORMAL_FLOAT = MAX_FLOAT, aka
    // x ~= (MAX_FLOAT_EXPONENT - MIN_DENORMAL_FLOAT_EXPONENT + 1) * log(2),
    // aka x ~= (1024 + 1074 + 1) * log(2) in double for example:
    // ~= 1454.916... for double, ~= 192.695.... for float. We also find where
    // sinh(x) ~= cosh(x) ~= exp(x)/2 overflows normally, at exp(x)/2 =
    // MAX_FLOAT, aka x ~= (MAX_FLOAT_EXPONENT + 1) * log(2): ~= (1024 + 1) *
    // log(2) ~= 710.475... for double, ~= (128 + 1) * log(2) ~= 89.416... for
    // float.

    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_max = __fp_exp_max_v<__fp_format_of_v<T>>;

    // Massage these values a little to cover the edges. These values are
    // small enough we can cast to int and back as a poor mans constexpr
    // floor. (We want ans_always_overflow_bound to be slightly larger than
    // the real value, we add 1.) ln2 is spelled directly: the
    // mathematical-constant accessor family is float-specialized in this tree.
    constexpr T ln2 = static_cast<T>(0.693147180559945309417232121458176568L);

    // These values are small enough we can cast to int and back as a poor
    // mans constexpr floor.
    constexpr T sinh_cosh_overflow_bound = T{static_cast<int>(T{exp_max + 2} * ln2)};
    constexpr T ans_always_overflow_bound =
        T{static_cast<int>(T{(exp_max + 1) + (exp_max + mant_nbits - 1)} * ln2) + 1};

    // We split the above interval into two. Get the midpoint. Our values look
    // like this for double/float:
    // double: sinh_cosh_overflow_bound 710.000000,
    //         ans_always_overflow_bound 1455.000000, midpoint 1082.500000
    // float:  sinh_cosh_overflow_bound 89.000000,
    //         ans_always_overflow_bound 193.000000, midpoint 141.000000
    constexpr T overflow_interval_midpoint = (sinh_cosh_overflow_bound + ans_always_overflow_bound) * T{0.5};

    T in_scale = T{0};
    T out_scale = T{1};

    if (real_x_abs >= sinh_cosh_overflow_bound) {
        // Here sinh and cosh will overflow, but the final result may not. Get
        // scale factors for the first half of the interval. What we really
        // want is an accurate constexpr exp(in_scale). Calling exp loses too
        // much accuracy (as well as relying on it being evaluated at compile
        // time), so the value is set manually:
        in_scale = overflow_interval_midpoint - sinh_cosh_overflow_bound;
        out_scale = is_same_v<T, double> ? static_cast<T>(7.715201168634011507e80) : static_cast<T>(1.95729609e11f);

        // Other half of the interval:
        if (real_x_abs > overflow_interval_midpoint) {
            in_scale = ans_always_overflow_bound - sinh_cosh_overflow_bound;
            // Same as above, set the value manually for the moment:
            out_scale = is_same_v<T, double> ? static_cast<T>(5.952432907249161686e161) : static_cast<T>(3.831008e22f);
        }

        if (real_x_abs > ans_always_overflow_bound) {
            // Here the final answer will overflow, with one exception: if
            // (imag == 0.0), we would end up later multiplying inf * 0.0 to
            // get NaN, while the correct answer is 0.0. This seems to be the
            // best place to correct this for (as opposed to an early return).
            // We clamp the value to a value that still always overflows the
            // final answer, while the intermediate calculation with our
            // scaling will not. (real == inf) has already been purged.
            real_x_abs = ans_always_overflow_bound;
        }
    }

    const T cosh_re_scaled = ::asc::std::cosh(real_x_abs - in_scale);
    const T sinh_re_scaled = ::asc::std::sinh(real_x_abs - in_scale);

    // Order of multiplication matters for under/overflow:
    const T ans_re = (sinh_re_scaled * (cos_imag * out_scale)) * out_scale;
    const T ans_im = (cosh_re_scaled * (sin_imag * out_scale)) * out_scale;

    const complex<T> ans_abs{ans_re, ans_im};
    return x_neg ? -ans_abs : ans_abs;
}

// cosh

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> cosh(const complex<T>& value) noexcept
{
    // Need to distinguish +-0.0, use signbit rather than >
    const bool x_neg = ::asc::std::signbit(value.real());

    const T imag_x = x_neg ? -value.imag() : value.imag();
    T real_x_abs = ::asc::std::fabs(value.real());

    // Special cases that don't fall through the rest of the algo:
    if (::asc::std::isnan(real_x_abs) || !(::asc::std::isfinite(imag_x))) {
        if (!(::asc::std::isfinite(imag_x)) && (real_x_abs == numeric_limits<T>::infinity())) {
            return complex<T>{numeric_limits<T>::infinity(),  // NOLINT(build/include_what_you_use)
                numeric_limits<T>::quiet_NaN()};              // NOLINT(build/include_what_you_use)
        }

        if (!(::asc::std::isfinite(imag_x)) && (real_x_abs == T(0))) {
            // Real part sign is unspecified
            return complex<T>{numeric_limits<T>::quiet_NaN(), T(0)};  // NOLINT(build/include_what_you_use)
        }

        if (::asc::std::isnan(real_x_abs) && (imag_x == T(0))) {
            // Real part sign is unspecified
            return complex<T>{numeric_limits<T>::quiet_NaN(), T(0)};  // NOLINT(build/include_what_you_use)
        }
    }

    const auto [sin_imag, cos_imag] = ::asc::std::__sincos(imag_x);

    // Using ans = {cosh(re) * cos(im), sinh(re) * sin(im)} results in
    // intermediate overflows where eg sinh(re) overflows, but
    // sinh(re) * sin(im) does not. We scale our inputs to avoid this; see the
    // sinh commentary above for the interval derivation.

    constexpr int32_t mant_nbits = __fp_mant_nbits_v<__fp_format_of_v<T>>;
    constexpr int32_t exp_max = __fp_exp_max_v<__fp_format_of_v<T>>;

    constexpr T ln2 = static_cast<T>(0.693147180559945309417232121458176568L);

    // These values are small enough we can cast to int and back as a poor
    // mans constexpr floor.
    constexpr T sinh_cosh_overflow_bound = T{static_cast<int>(T{exp_max + 2} * ln2)};
    constexpr T ans_always_overflow_bound =
        T{static_cast<int>(T{(exp_max + 1) + (exp_max + mant_nbits - 1)} * ln2) + 1};

    constexpr T overflow_interval_midpoint = (sinh_cosh_overflow_bound + ans_always_overflow_bound) * T{0.5};

    T in_scale = T{0};
    T out_scale = T{1};

    if (real_x_abs >= sinh_cosh_overflow_bound) {
        // Here sinh and cosh will overflow, but the final result may not. Get
        // scale factors for the first half of the interval:
        in_scale = overflow_interval_midpoint - sinh_cosh_overflow_bound;
        // What we really want is an accurate constexpr exp(in_scale), set
        // manually:
        out_scale = is_same_v<T, double> ? static_cast<T>(7.715201168634011507e80) : static_cast<T>(1.95729609e11f);

        // Other half of the interval:
        if (real_x_abs > overflow_interval_midpoint) {
            in_scale = ans_always_overflow_bound - sinh_cosh_overflow_bound;
            // Same as above, set the value manually for the moment:
            out_scale = is_same_v<T, double> ? static_cast<T>(5.952432907249161686e161) : static_cast<T>(3.831008e22f);
        }

        if (real_x_abs > ans_always_overflow_bound) {
            // Here the final answer will overflow, with one exception: if
            // (imag == 0.0), we would end up later multiplying inf * 0.0 to
            // get NaN, while the correct answer is 0.0. (real == inf) has
            // already been purged.
            real_x_abs = ans_always_overflow_bound;
        }
    }

    const T cosh_re_scaled = ::asc::std::cosh(real_x_abs - in_scale);
    const T sinh_re_scaled = ::asc::std::sinh(real_x_abs - in_scale);

    // Order of multiplication matters for under/overflow:
    const T ans_re = (cosh_re_scaled * (cos_imag * out_scale)) * out_scale;
    const T ans_im = (sinh_re_scaled * (sin_imag * out_scale)) * out_scale;

    return complex<T>{ans_re, ans_im};
}

// tanh

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> tanh(const complex<T>& value) noexcept
{
    const T real_x_abs = ::asc::std::fabs(value.real());
    T imag_x = value.imag();

    // real_x_abs == inf overrides imag_x == nan:
    if (real_x_abs == numeric_limits<T>::infinity()) {  // NOLINT(build/include_what_you_use)
        imag_x = ::asc::std::copysign(T(0), imag_x);
    }

    // A somewhat strange special-within-special case (C11 DR471):
    if ((real_x_abs == T(0)) && !::asc::std::isfinite(imag_x)) {
        return complex<T>{::asc::std::copysign(T(0), value.real()),
            numeric_limits<T>::quiet_NaN()};  // NOLINT(build/include_what_you_use)
    }

    const auto [sin_imag, cos_imag] = ::asc::std::__sincos(imag_x);

    // We can avoid under/overflow issues by scaling large real values
    // appropriately and correcting afterwards. floor(log(MAX_FLOAT) / 4):
    constexpr T reduction_needed_bound = is_same_v<T, double> ? T{177.0} : T{22.0f};

    T real_x_reduced = real_x_abs;
    T imag_x_mul_factor = T{1};

    if (real_x_reduced >= reduction_needed_bound) {
        // Set some very specific values to help with range reduction. This
        // value was originally 648.0, but quite unluckily this resulted in
        // different values of expm1() below on different compilers, and large
        // inputs which should have ans.real() == 1 were off by a bit. This
        // tweak fixes it.
        constexpr T clamp_huge_values_bound = is_same_v<T, double> ? T{647.99999} : T{58.0f};

        // Use two intervals to reduce values. Some values will be reduced
        // twice.
        constexpr T large_interval_bound = is_same_v<T, double> ? T{334.0} : T{34.0f};

        // Has very low ulp error for c-r exp(large_interval_subtract_factor):
        constexpr T large_interval_subtract_factor =
            is_same_v<T, double> ? static_cast<T>(-6.2800006538698050917e2) : T{-48.795158386f};

        // exp(large_interval_subtract_factor):
        constexpr T large_interval_mul_factor =
            is_same_v<T, double> ? static_cast<T>(1.83247039732913163759e-273) : T{6.4347543e-22f};

        // Has very low ulp error for c-r exp(small_interval_subtract_factor).
        // We also require (large_interval_mul_factor *
        // small_interval_mul_factor) to round well:
        constexpr T small_interval_subtract_factor =
            is_same_v<T, double> ? static_cast<T>(-3.1400000790995977695e2) : T{-24.34370422f};

        // exp(small_interval_subtract_factor):
        constexpr T small_interval_mul_factor =
            is_same_v<T, double> ? static_cast<T>(4.2808424752052536879e-137) : T{2.6770937897e-11f};

        // Clamp huge values, doesn't change result.
        if (real_x_reduced > clamp_huge_values_bound) {
            real_x_reduced = clamp_huge_values_bound;
        }

        if (real_x_reduced >= large_interval_bound) {
            imag_x_mul_factor = large_interval_mul_factor;
            real_x_reduced = real_x_reduced + (large_interval_subtract_factor * T{0.5});
        }

        if (real_x_reduced > reduction_needed_bound) {
            imag_x_mul_factor *= small_interval_mul_factor;
            real_x_reduced = real_x_reduced + (small_interval_subtract_factor * T{0.5});
        }
    }

    const T expm1_2x = ::asc::std::expm1(T{2} * real_x_reduced);
    const T cos_sq_4 = T{4} * cos_imag * cos_imag;
    const T denom = ::asc::std::fma(expm1_2x, expm1_2x, ::asc::std::fma(cos_sq_4, expm1_2x, cos_sq_4));
    const T numer_real = ::asc::std::fma(expm1_2x, expm1_2x, T{2} * expm1_2x);

    // Save doing two full divides:
    const T denom_recip = T{1} / denom;

    // For the imaginary part of the answer care is needed to avoid
    // intermediate under/overflow. Here is one possibility:
    T ans_imag =
        ((::asc::std::fma(sin_imag, expm1_2x, sin_imag) * denom_recip) * (T{4} * cos_imag)) * imag_x_mul_factor;

    // Overwrite imag == 0.0 for real inf/nan inputs.
    if (imag_x == T(0)) {
        ans_imag = imag_x;
    }

    const T ans_real = numer_real * denom_recip;
    return complex<T>{::asc::std::copysign(ans_real, value.real()), ans_imag};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_HYPERBOLIC_FUNCTIONS_H
