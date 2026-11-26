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

#include <asc/std/cmath>

#include <cmath>
#include <cstdio>
#include <limits>
#include <type_traits>

#include "device_checks.h"

template <class A, class B>
bool equal_value(A observed, B expected)
{
    if constexpr (std::is_floating_point_v<A> || std::is_floating_point_v<B>) {
        if (std::isnan(expected))
            return std::isnan(observed);
        if (std::isinf(expected) || expected == 0)
            return observed == expected && std::signbit(observed) == std::signbit(expected);
    }
    return observed == expected;
}

#define CHECK_VALUE(name, observed, expected)                                \
    do {                                                                     \
        if (!equal_value((observed), (expected))) {                          \
            std::fprintf(stderr, "%s differs at line %d\n", name, __LINE__); \
            return false;                                                    \
        }                                                                    \
    } while (false)

#define CHECK_MATH(name, ...) CHECK_VALUE(#name, asc::std::name(__VA_ARGS__), std::name(__VA_ARGS__))
#define CHECK_C_ALIAS(name, ...) CHECK_VALUE(#name, asc::std::name(__VA_ARGS__), ::name(__VA_ARGS__))

template <class T>
bool scalar_overloads(T x)
{
    CHECK_MATH(fabs, x);
    CHECK_MATH(erf, x);
    CHECK_MATH(erfc, x);
    CHECK_MATH(exp, x);
    CHECK_MATH(exp2, x);
    CHECK_MATH(expm1, x);
    CHECK_MATH(tgamma, x);
    CHECK_MATH(lgamma, x);
    CHECK_MATH(sinh, x);
    CHECK_MATH(cosh, x);
    CHECK_MATH(tanh, x);
    CHECK_MATH(asinh, x);
    CHECK_MATH(acosh, x);
    CHECK_MATH(atanh, x);
    CHECK_MATH(asin, x);
    CHECK_MATH(acos, x);
    CHECK_MATH(atan, x);
    CHECK_MATH(sin, x);
    CHECK_MATH(cos, x);
    CHECK_MATH(tan, x);
    CHECK_MATH(sqrt, x);
    CHECK_MATH(cbrt, x);
    CHECK_MATH(log, x);
    CHECK_MATH(log10, x);
    CHECK_MATH(log2, x);
    CHECK_MATH(log1p, x);
    CHECK_MATH(logb, x);
    CHECK_MATH(ceil, x);
    CHECK_MATH(floor, x);
    CHECK_MATH(trunc, x);
    CHECK_MATH(round, x);
    CHECK_MATH(rint, x);
    CHECK_MATH(nearbyint, x);
    CHECK_MATH(fdim, x, T(2));
    CHECK_MATH(pow, x, T(2));
    CHECK_MATH(hypot, x, T(2));
    CHECK_MATH(atan2, x, T(2));
    CHECK_MATH(fmax, x, T(2));
    CHECK_MATH(fmin, x, T(2));
    CHECK_MATH(fmod, x, T(2));
    CHECK_MATH(remainder, x, T(2));
    CHECK_MATH(copysign, x, T(2));
    CHECK_MATH(nextafter, x, T(2));
    CHECK_MATH(fma, x, T(3), T(-2));
    CHECK_MATH(scalbn, x, -7);
    CHECK_MATH(scalbln, x, 4L);
    CHECK_MATH(ldexp, x, 5);
    CHECK_MATH(isnan, x);
    CHECK_MATH(isinf, x);
    CHECK_MATH(isfinite, x);
    CHECK_MATH(isnormal, x);
    CHECK_MATH(fpclassify, x);
    CHECK_MATH(signbit, x);
    if (std::isfinite(x) && x != 0) {
        CHECK_MATH(ilogb, x);
        CHECK_MATH(lround, x);
        CHECK_MATH(llround, x);
        CHECK_MATH(lrint, x);
        CHECK_MATH(llrint, x);
        int exponent = 0, reference = 0;
        const auto fraction = asc::std::frexp(x, &exponent);
        const auto expected = std::frexp(x, &reference);
        CHECK_VALUE("frexp fraction", fraction, expected);
        CHECK_VALUE("frexp exponent", exponent, reference);
    }
    return true;
}

// Exercise the C99 suffixed spellings independently of the primary overloads.
bool suffixed_functions(float f, long double l)
{
    CHECK_C_ALIAS(fabsf, f);
    CHECK_C_ALIAS(fabsl, l);
    CHECK_C_ALIAS(erff, f);
    CHECK_C_ALIAS(erfl, l);
    CHECK_C_ALIAS(erfcf, f);
    CHECK_C_ALIAS(erfcl, l);
    CHECK_C_ALIAS(expf, f);
    CHECK_C_ALIAS(expl, l);
    CHECK_C_ALIAS(exp2f, f);
    CHECK_C_ALIAS(exp2l, l);
    CHECK_C_ALIAS(expm1f, f);
    CHECK_C_ALIAS(expm1l, l);
    CHECK_C_ALIAS(tgammaf, f);
    CHECK_C_ALIAS(tgammal, l);
    CHECK_C_ALIAS(lgammaf, f);
    CHECK_C_ALIAS(lgammal, l);
    CHECK_C_ALIAS(sinhf, f);
    CHECK_C_ALIAS(sinhl, l);
    CHECK_C_ALIAS(coshf, f);
    CHECK_C_ALIAS(coshl, l);
    CHECK_C_ALIAS(tanhf, f);
    CHECK_C_ALIAS(tanhl, l);
    CHECK_C_ALIAS(asinhf, f);
    CHECK_C_ALIAS(asinhl, l);
    CHECK_C_ALIAS(acoshf, f);
    CHECK_C_ALIAS(acoshl, l);
    CHECK_C_ALIAS(atanhf, f);
    CHECK_C_ALIAS(atanhl, l);
    CHECK_C_ALIAS(asinf, f);
    CHECK_C_ALIAS(asinl, l);
    CHECK_C_ALIAS(acosf, f);
    CHECK_C_ALIAS(acosl, l);
    CHECK_C_ALIAS(atanf, f);
    CHECK_C_ALIAS(atanl, l);
    CHECK_C_ALIAS(sinf, f);
    CHECK_C_ALIAS(sinl, l);
    CHECK_C_ALIAS(cosf, f);
    CHECK_C_ALIAS(cosl, l);
    CHECK_C_ALIAS(tanf, f);
    CHECK_C_ALIAS(tanl, l);
    CHECK_C_ALIAS(sqrtf, f);
    CHECK_C_ALIAS(sqrtl, l);
    CHECK_C_ALIAS(cbrtf, f);
    CHECK_C_ALIAS(cbrtl, l);
    CHECK_C_ALIAS(logf, f);
    CHECK_C_ALIAS(logl, l);
    CHECK_C_ALIAS(log10f, f);
    CHECK_C_ALIAS(log10l, l);
    CHECK_C_ALIAS(log2f, f);
    CHECK_C_ALIAS(log2l, l);
    CHECK_C_ALIAS(log1pf, f);
    CHECK_C_ALIAS(log1pl, l);
    CHECK_C_ALIAS(logbf, f);
    CHECK_C_ALIAS(logbl, l);
    CHECK_C_ALIAS(ceilf, f);
    CHECK_C_ALIAS(ceill, l);
    CHECK_C_ALIAS(floorf, f);
    CHECK_C_ALIAS(floorl, l);
    CHECK_C_ALIAS(truncf, f);
    CHECK_C_ALIAS(truncl, l);
    CHECK_C_ALIAS(roundf, f);
    CHECK_C_ALIAS(roundl, l);
    CHECK_C_ALIAS(rintf, f);
    CHECK_C_ALIAS(rintl, l);
    CHECK_C_ALIAS(nearbyintf, f);
    CHECK_C_ALIAS(nearbyintl, l);
    CHECK_C_ALIAS(fdimf, f, 2.0F);
    CHECK_C_ALIAS(fdiml, l, 2.0L);
    CHECK_C_ALIAS(powf, f, 2.0F);
    CHECK_C_ALIAS(powl, l, 2.0L);
    CHECK_C_ALIAS(hypotf, f, 2.0F);
    CHECK_C_ALIAS(hypotl, l, 2.0L);
    CHECK_C_ALIAS(atan2f, f, 2.0F);
    CHECK_C_ALIAS(atan2l, l, 2.0L);
    CHECK_C_ALIAS(fmaxf, f, 2.0F);
    CHECK_C_ALIAS(fmaxl, l, 2.0L);
    CHECK_C_ALIAS(fminf, f, 2.0F);
    CHECK_C_ALIAS(fminl, l, 2.0L);
    CHECK_C_ALIAS(fmodf, f, 2.0F);
    CHECK_C_ALIAS(fmodl, l, 2.0L);
    CHECK_C_ALIAS(remainderf, f, 2.0F);
    CHECK_C_ALIAS(remainderl, l, 2.0L);
    CHECK_C_ALIAS(copysignf, f, 2.0F);
    CHECK_C_ALIAS(copysignl, l, 2.0L);
    CHECK_C_ALIAS(nextafterf, f, 2.0F);
    CHECK_C_ALIAS(nextafterl, l, 2.0L);
    CHECK_C_ALIAS(fmaf, f, f, f);
    CHECK_C_ALIAS(fmal, l, l, l);
    CHECK_C_ALIAS(scalbnf, f, -3);
    CHECK_C_ALIAS(scalbnl, l, -3);
    CHECK_C_ALIAS(scalblnf, f, -3L);
    CHECK_C_ALIAS(scalblnl, l, -3L);
    CHECK_C_ALIAS(ldexpf, f, -3);
    CHECK_C_ALIAS(ldexpl, l, -3);
    CHECK_C_ALIAS(ilogbf, f);
    CHECK_C_ALIAS(ilogbl, l);
    CHECK_C_ALIAS(lroundf, f);
    CHECK_C_ALIAS(lroundl, l);
    CHECK_C_ALIAS(llroundf, f);
    CHECK_C_ALIAS(llroundl, l);
    CHECK_C_ALIAS(lrintf, f);
    CHECK_C_ALIAS(lrintl, l);
    CHECK_C_ALIAS(llrintf, f);
    CHECK_C_ALIAS(llrintl, l);
    int a = 0, b = 0;
    CHECK_VALUE("frexpf", asc::std::frexpf(f, &a), ::frexpf(f, &b));
    CHECK_VALUE("frexpf exponent", a, b);
    CHECK_VALUE("frexpl", asc::std::frexpl(l, &a), ::frexpl(l, &b));
    CHECK_VALUE("frexpl exponent", a, b);
    CHECK_C_ALIAS(nexttowardf, f, -0.125L);
    CHECK_C_ALIAS(nexttowardl, l, -0.125L);
    return true;
}

bool special_functions()
{
    const float nan = std::numeric_limits<float>::quiet_NaN();
    if (!std::isnan(asc::std::nanf("")))
        return false;
    CHECK_MATH(isunordered, nan, 1.0F);
    CHECK_MATH(islessgreater, nan, 1.0F);
    CHECK_MATH(isgreater, 2.0F, 1.0F);
    CHECK_MATH(isgreaterequal, -0.0F, 0.0F);
    CHECK_MATH(isless, -2.0F, -1.0F);
    CHECK_MATH(islessequal, 0.0F, -0.0F);
    CHECK_MATH(fma, 1, -0.75L, 2.25);
    CHECK_MATH(pow, -2, 4.0);
    CHECK_MATH(hypot, 3, 4.0);
    CHECK_MATH(fdim, -1, 2.0);
    CHECK_MATH(fmax, -1.5F, 2.0);
    CHECK_MATH(fmin, 3.0, -0.25L);
    CHECK_MATH(atan2, -2, 4.0);
    CHECK_MATH(fmod, 7, 2.0);
    CHECK_MATH(remainder, 7, 2.0);
    CHECK_MATH(nextafter, -1, 2.0);
    CHECK_MATH(abs, -0.0F);
    CHECK_MATH(abs, -0.25);
    CHECK_MATH(abs, -0.25L);
    CHECK_MATH(nexttoward, 0.0F, -0.0L);
    CHECK_MATH(nexttoward, 1.0, 2.0L);
    CHECK_MATH(nexttoward, 1.0L, 0.0L);
    CHECK_VALUE("lerp", asc::std::lerp(-4.0F, 4.0F, 0.25F), -2.0F);
    CHECK_VALUE("fused cancellation", asc::std::fma(0x1.000002p0F, 0x1.fffffep-1F, -1.F), 0x1.fffffcp-25F);
    CHECK_VALUE("hypot3", asc::std::hypot(2, 3.0, 6.F), 7.0);
    CHECK_VALUE("hypot3f", asc::std::hypotf(2.F, 3.F, 6.F), 7.F);
    CHECK_VALUE("hypot3l", asc::std::hypotl(2.L, 3.L, 6.L), 7.L);
    float integer = 0;
    CHECK_VALUE("modf", asc::std::modf(-2.5F, &integer), -0.5F);
    CHECK_VALUE("modf integer", integer, -2.0F);
    CHECK_VALUE("modff", asc::std::modff(3.25F, &integer), 0.25F);
    CHECK_VALUE("modff integer", integer, 3.0F);
    int quotient = 0;
    CHECK_VALUE("remquo", asc::std::remquo(7.0F, 2.0F, &quotient), -1.0F);
    CHECK_VALUE("remquo quotient", quotient & 7, 4);
    CHECK_VALUE("remquof", asc::std::remquof(-7.0F, 2.0F, &quotient), 1.0F);
    CHECK_VALUE("remquof quotient", quotient < 0 && ((-quotient & 7) == 4), true);
    return true;
}

bool remquo_differential()
{
    unsigned state = 0x07e156a7U;
    const auto next = [&]() {
        state = state * 1664525U + 1013904223U;
        return asc::std::bit_cast<float>(state);
    };
    for (unsigned i = 0; i < 65536; ++i) {
        const float x = next();
        const float y = next();
        int expected_quotient = 0, quotient = 0;
        const float expected = std::remquo(x, y, &expected_quotient);
        const float actual = asc::std::__cmath_backend::__remquo_binary32(x, y, &quotient);
        if (std::isnan(expected)) {
            if (!std::isnan(actual))
                return false;
        } else {
            if (asc::std::bit_cast<unsigned>(actual) != asc::std::bit_cast<unsigned>(expected) ||
                quotient != expected_quotient % 8)
                return false;
        }
    }
    return true;
}

template <class T>
bool test_inputs()
{
    const T values[] = {T(-3.25), T(-1), T(-0.0), T(0), T(0.25), T(1), T(1.5), std::numeric_limits<T>::infinity(),
        std::numeric_limits<T>::quiet_NaN()};
    for (T value : values) {
        if (!scalar_overloads(value))
            return false;
    }
    return true;
}

int main()
{
    asc_stl_test_cmath::math_outputs workspace{};
    return test_inputs<float>() && test_inputs<double>() && test_inputs<long double>() && scalar_overloads(1) &&
            suffixed_functions(-0.5F, 0.75L) && special_functions() && remquo_differential() &&
            asc_stl_test_cmath::check(7, &workspace) == 0 ?
        0 :
        1;
}
