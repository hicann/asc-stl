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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_EXPONENTIAL_FUNCTIONS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_EXPONENTIAL_FUNCTIONS_H

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
#include <asc/std/__cmath/copysign.h>
#include <asc/std/__cmath/fma.h>
#include <asc/std/__cmath/isfinite.h>
#include <asc/std/__cmath/isinf.h>
#include <asc/std/__cmath/isnan.h>
#include <asc/std/__cmath/sincos.h>
#include <asc/std/__cmath/trigonometric_functions.h>
#include <asc/std/__complex/complex.h>
#include <asc/std/__complex/logarithms.h>
#include <asc/std/__complex/vector_support.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/cstdint>
#include <asc/std/limits>
#include <asc/std/numbers>

CANN_ASC_STL_BEGIN_NAMESPACE

// exp

// C99 special-value filtering: zero imaginary part keeps the sign of the
// zero, and -inf/+inf real parts propagate with NaN fixes for non-finite
// imaginary components.
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> exp(const complex<T>& value) noexcept
{
    T i = value.imag();
    if (i == T(0)) {
        return complex<T>(::asc::std::exp(value.real()), ::asc::std::copysign(T(0), value.imag()));
    }
    if (::asc::std::isinf(value.real())) {
        if (value.real() < T(0)) {
            if (!::asc::std::isfinite(i)) {
                i = T(1);
            }
        } else if (i == T(0) || !::asc::std::isfinite(i)) {
            if (::asc::std::isinf(i)) {
                i = numeric_limits<T>::quiet_NaN();  // NOLINT(build/include_what_you_use)
            }
            return complex<T>(value.real(), i);
        }
    }
    const T e = ::asc::std::exp(value.real());
    const auto [i_sin, i_cos] = ::asc::std::__sincos(i);
    return complex<T>(e * i_cos, e * i_sin);
}

// A real exp that doesn't combine the final polynomial estimate with the
// ldexp factor. Useful in cases where an extended-range exp is needed for
// intermediate calculations.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API float __internal_unsafe_exp_with_reduction(
    float r, float* ldexp_factor) noexcept
{
    // A slightly more efficient way of doing
    //    j = round(r * L2E)
    constexpr float round_shift = 12582912.0f;  // 1.5 * 2^23
    const float log2_e = ::asc::std::numbers::log2e_v<float>;
    float j = ::asc::std::fma(r, log2_e, round_shift);
    j = j - round_shift;

    // exp() range reduction. Constants taken from:
    // https://arxiv.org/PS_cache/arxiv/pdf/0708/0708.3722v1.pdf
    float r_reduced;
    r_reduced = ::asc::std::fma(-j, 0.693147182464599609375f, r);
    r_reduced = ::asc::std::fma(-j, -1.904652435769094154e-9f, r_reduced);

    // r_reduced is in [log(sqrt(0.5)), log(sqrt(2))].
    float exp_mant = 1.95693559362553060054779052734375e-4f;
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.39354146085679531097412109375e-3f);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 8.333896286785602569580078125e-3f);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 4.16664592921733856201171875e-2f);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 0.16666664183139801025390625f);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 0.5f);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.0f);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.0f);

    *ldexp_factor = j;
    return exp_mant;
}

// fp64 is a host-only math path.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API double __internal_unsafe_exp_with_reduction(
    double r, double* ldexp_factor) noexcept
{
    // A slightly more efficient way of doing
    //    j = round(r * L2E)
    constexpr double round_shift = 6.755399441055744e15;  // 1.5 * 2^52
    const double log2_e = ::asc::std::numbers::log2e;
    double j = ::asc::std::fma(r, log2_e, round_shift);
    j = j - round_shift;

    // exp() range reduction. Constants taken from:
    // https://arxiv.org/PS_cache/arxiv/pdf/0708/0708.3722v1.pdf
    double r_reduced;
    r_reduced = ::asc::std::fma(-j, 0.6931471805599453972491, r);
    r_reduced = ::asc::std::fma(-j, -8.78318343240526554e-17, r_reduced);

    // r_reduced is in [log(sqrt(0.5)), log(sqrt(2))].
    double exp_mant = 2.5022322536502990e-8;
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 2.7630903488173108e-7);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 2.7557514545882439e-6);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 2.4801491039099165e-5);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.9841269589115497e-4);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.3888888945916380e-3);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 8.3333333334550432e-3);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 4.1666666666519754e-2);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.6666666666666477e-1);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 5.0000000000000122e-1);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.0);
    exp_mant = ::asc::std::fma(exp_mant, r_reduced, 1.0);

    *ldexp_factor = j;
    return exp_mant;
}
#endif  // Host fp64 polynomial

// exp fp32 specialization: the reduced mantissa estimate is recombined with
// the power-of-two factor through a four-way exponent split, so intermediate
// denormal sin/cos products keep their bits and guaranteed over/underflow is
// clamped instead of branching.
template <>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<float> exp(const complex<float>& value) noexcept
{
    const float r = value.real();
    const float i = value.imag();

    // Some Inf/NaN special cases that don't filter through:
    if (!::asc::std::isfinite(r)) {
        if (::asc::std::isinf(r) && !::asc::std::isfinite(i)) {
            // r == +-INF
            return ::asc::std::signbit(r) ?
                complex<float>{} :
                complex<float>{numeric_limits<float>::infinity(),  // NOLINT(build/include_what_you_use)
                    numeric_limits<float>::quiet_NaN()};           // NOLINT(build/include_what_you_use)
        }
        // r NaN:
        if (::asc::std::isnan(r) && (i == 0.0f)) {
            return value;
        }
    }

    // exp(r), but without the range-reduced re-combination:
    float exp_r_ldexp_factor;
    float exp_r_reduced = ::asc::std::__internal_unsafe_exp_with_reduction(r, &exp_r_ldexp_factor);

    // Get some close bounds when the answer is fully guaranteed to
    // under/overflow. Sometime close to but >= log(max_flt / min_denom_float):
    if (::asc::std::fabsf(r) >= 194.0f) {
        // real/imag return value must always underflow or overflow. Clamp to
        // a low value that still under/overflows. This helps avoid multiple
        // other branches earlier/later.
        exp_r_reduced = (r < 0.0f) ? 0.0f : 1e3f;
    }

    const auto [sin_i, cos_i] = ::asc::std::__sincos(i);

    // Our answer now is: (ldexp(exp_r_reduced * sin_i, j_int),
    // ldexp(exp_r_reduced * cos_i, j_int)). However we don't need a full ldexp
    // here, and if exp_r_reduced*sin_r is denormal we can lose bits. Instead,
    // do an inlined/simplified ldexp.

    // With fabs(sin or cos) <= 1, the unbiased exponent of sin or cos is in
    // [-149, 0]. So for an inlined ldexp, we can clamp j to [-151, 277]. (Go
    // as low as -151 for underflow to 0 denormal rounding.) This allows to do
    // an ldexp via some faster integer ops.

    // j converted to int32, clamped so nothing bad happens. Will not change
    // any results. 151 = 127 + 24, 277 = 23 + 2*127 + 1.
    if (exp_r_ldexp_factor > 278.0f) {
        exp_r_ldexp_factor = 278.0f;
    }
    // Catch NaN's here to avoid UB.
    if (!(exp_r_ldexp_factor >= -151.0f)) {
        exp_r_ldexp_factor = -151.0f;
    }

    const int32_t ans_ldexp_factor = static_cast<int32_t>(exp_r_ldexp_factor);

    // Split this j up into four parts to fit it into four float exponents.
    // (Splitting j in 4 better than in 3).
    uint32_t ans_ldexp_factor_quarter = (static_cast<uint32_t>(ans_ldexp_factor) / 4);
    uint32_t ans_ldexp_factor_remainder = static_cast<uint32_t>(ans_ldexp_factor) - (3 * ans_ldexp_factor_quarter);

    // Pack these into exponents:
    ans_ldexp_factor_quarter = (ans_ldexp_factor_quarter + 127) << 23;
    ans_ldexp_factor_remainder = (ans_ldexp_factor_remainder + 127) << 23;

    const float ldexp_factor_1 = ::asc::std::bit_cast<float>(ans_ldexp_factor_quarter);
    const float ldexp_factor_2 = ::asc::std::bit_cast<float>(ans_ldexp_factor_remainder);

    // Need to order our multiplications to avoid intermediate under/overflow,
    // including when sin_r is denormal. Experiment suggests this is (one of)
    // the better ways to do it, there's not that many combinations that work
    // for all inputs:
    const float ans_r =
        (((cos_i * ldexp_factor_1) * ldexp_factor_1) * ldexp_factor_1) * (exp_r_reduced * ldexp_factor_2);
    const float ans_i =
        (((sin_i * ldexp_factor_1) * ldexp_factor_1) * ldexp_factor_1) * (exp_r_reduced * ldexp_factor_2);

    return complex<float>(ans_r, ans_i);
}

// pow

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> pow(
    const complex<T>& base, const complex<T>& exponent) noexcept
{
    return ::asc::std::exp(exponent * ::asc::std::log(base));
}

// Mixed-type pow through the common value type. The scalar overloads below
// constrain their scalar operand through the return type so that a complex
// right/left operand resolves here instead of producing an ambiguity.
template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<common_type_t<T, U>> pow(
    const complex<T>& base, const complex<U>& exponent) noexcept
{
    using result_type = complex<common_type_t<T, U>>;
    return ::asc::std::pow(result_type(base), result_type(exponent));
}

template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API enable_if_t<!__is_asc_std_complex_v<U>, complex<common_type_t<T, U>>>
pow(const complex<T>& base, const U& exponent) noexcept
{
    using result_type = complex<common_type_t<T, U>>;
    return ::asc::std::pow(result_type(base), result_type(static_cast<common_type_t<T, U>>(exponent)));
}

template <class T, class U>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API enable_if_t<!__is_asc_std_complex_v<T>, complex<common_type_t<T, U>>>
pow(const T& base, const complex<U>& exponent) noexcept
{
    using result_type = complex<common_type_t<T, U>>;
    return ::asc::std::pow(result_type(static_cast<common_type_t<T, U>>(base), 0), result_type(exponent));
}

// __sqr, computes pow(x, 2)

template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_SIMT_API complex<T> __sqr(const complex<T>& value) noexcept
{
    return complex<T>(
        (value.real() - value.imag()) * (value.real() + value.imag()), T(2) * value.real() * value.imag());
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_EXPONENTIAL_FUNCTIONS_H
