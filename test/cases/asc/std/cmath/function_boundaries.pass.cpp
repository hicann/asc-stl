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

#if !defined(FP_INFINITE) || !defined(FP_NAN) || !defined(FP_NORMAL) || !defined(FP_SUBNORMAL) || !defined(FP_ZERO)
#error "<asc/std/cmath> must expose the floating-point classifications"
#endif

#include <cmath>
#include <limits>
#include <type_traits>

namespace {

namespace ast = asc::std;

template <class T>
bool agrees(T actual, T expected)
{
    if (std::isnan(expected)) {
        return std::isnan(actual);
    }
    if (!std::isfinite(expected) || expected == T{0}) {
        return actual == expected;
    }
    const auto tolerance = T{16} * std::numeric_limits<T>::epsilon() * std::fabs(expected);
    return std::fabs(actual - expected) <= tolerance;
}

static_assert(std::is_same_v<ast::float_t, ::float_t>);
static_assert(std::is_same_v<ast::double_t, ::double_t>);
static_assert(FP_LLOGB0 == std::numeric_limits<long>::min() || FP_LLOGB0 == std::numeric_limits<long>::max());
static_assert(FP_LLOGBNAN == std::numeric_limits<long>::min() || FP_LLOGBNAN == std::numeric_limits<long>::max());

bool check_classification()
{
    const float infinity = INFINITY;
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float values[] = {
        -infinity, -2.5F, -0.0F, 0.0F, std::numeric_limits<float>::denorm_min(), 1.25F, infinity, nan};
    const int classes[] = {FP_INFINITE, FP_NORMAL, FP_ZERO, FP_ZERO, FP_SUBNORMAL, FP_NORMAL, FP_INFINITE, FP_NAN};
    for (unsigned i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        const auto x = values[i];
        if (ast::fpclassify(x) != classes[i] || std::fpclassify(x) != classes[i] || ast::isinf(x) != std::isinf(x)) {
            return false;
        }
        for (auto y : values) {
            if (ast::isgreater(x, y) != std::isgreater(x, y) ||
                ast::isgreaterequal(x, y) != std::isgreaterequal(x, y) || ast::isless(x, y) != std::isless(x, y) ||
                ast::islessequal(x, y) != std::islessequal(x, y) ||
                ast::islessgreater(x, y) != std::islessgreater(x, y) ||
                ast::isunordered(x, y) != std::isunordered(x, y)) {
                return false;
            }
        }
    }
    return std::isnan(ast::nanf("")) && std::isnan(ast::nanf("19")) && ast::ilogb(0.0) == FP_ILOGB0 &&
        ast::ilogbf(std::numeric_limits<float>::quiet_NaN()) == FP_ILOGBNAN;
}

bool check_exponents()
{
    const double values[] = {-10.0, -0.25, -0.0, 0.0, 0.0000001, 0.5, 2.0, 20.0};
    const int shifts[] = {-20, -1, 0, 1, 20};
    for (double value : values) {
        const auto x = static_cast<float>(value);
        int asc_exponent = 42;
        int host_exponent = 42;
        if (ast::frexp(value, &asc_exponent) != std::frexp(value, &host_exponent) || asc_exponent != host_exponent) {
            return false;
        }
        if (ast::frexpf(x, &asc_exponent) != std::frexp(x, &host_exponent) || asc_exponent != host_exponent) {
            return false;
        }
        float asc_integral = 3;
        float host_integral = 7;
        if (ast::modf(x, &asc_integral) != std::modf(x, &host_integral) || asc_integral != host_integral) {
            return false;
        }
        float asc_integral_f = 3;
        float host_integral_f = 7;
        if (ast::modff(x, &asc_integral_f) != std::modf(x, &host_integral_f) || asc_integral_f != host_integral_f) {
            return false;
        }
        if (ast::ilogb(value) != std::ilogb(value) || ast::ilogbf(x) != std::ilogb(x) ||
            ast::logb(value) != std::logb(value) || ast::logbf(x) != std::logb(x)) {
            return false;
        }
        for (int k : shifts) {
            if (ast::ldexp(value, k) != std::ldexp(value, k) || ast::ldexpf(x, k) != std::ldexp(x, k) ||
                ast::scalbn(value, k) != std::scalbn(value, k) || ast::scalbnf(x, k) != std::scalbn(x, k) ||
                ast::scalbln(value, k) != std::scalbln(value, k) || ast::scalblnf(x, k) != std::scalbln(x, k)) {
                return false;
            }
        }
    }
    return true;
}

bool check_transcendentals()
{
    const double values[] = {-8.0, -1.25, -0.0, 0.0, 1e-10, 0.25, 1.0, 3.0, 64.0};
    for (double value : values) {
        const auto x = static_cast<float>(value);
        if (!agrees(ast::erf(value), std::erf(value)) || !agrees(ast::erff(x), std::erf(x)) ||
            !agrees(ast::erfc(value), std::erfc(value)) || !agrees(ast::erfcf(x), std::erfc(x)) ||
            !agrees(ast::exp(value), std::exp(value)) || !agrees(ast::expf(x), std::exp(x)) ||
            !agrees(ast::exp2(value), std::exp2(value)) || !agrees(ast::exp2f(x), std::exp2(x)) ||
            !agrees(ast::expm1(value), std::expm1(value)) || !agrees(ast::expm1f(x), std::expm1(x)) ||
            !agrees(ast::log(value), std::log(value)) || !agrees(ast::logf(x), std::log(x)) ||
            !agrees(ast::log10(value), std::log10(value)) || !agrees(ast::log10f(x), std::log10(x)) ||
            !agrees(ast::log1p(value), std::log1p(value)) || !agrees(ast::log1pf(x), std::log1p(x)) ||
            !agrees(ast::log2(value), std::log2(value)) || !agrees(ast::log2f(x), std::log2(x))) {
            return false;
        }
    }
    return agrees(ast::acos(-1.0), std::acos(-1.0)) && agrees(ast::acos(0), std::acos(0)) &&
        agrees(ast::acos(1.0), 0.0) && std::isnan(ast::acos(2.0));
}

bool check_binary_functions()
{
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float values[] = {-7.5F, -0.0F, 0.0F, 0.25F, 16.0F, nan};
    for (float x : values) {
        if (!agrees(ast::fabsf(x), std::fabs(x))) {
            return false;
        }
        for (float y : values) {
            const auto dx = static_cast<double>(x);
            const auto dy = static_cast<double>(y);
            if (!agrees(ast::fdim(dx, dy), std::fdim(dx, dy)) || !agrees(ast::fdimf(x, y), std::fdim(x, y)) ||
                !agrees(ast::fmax(dx, dy), std::fmax(dx, dy)) || !agrees(ast::fmaxf(x, y), std::fmax(x, y)) ||
                !agrees(ast::fmin(dx, dy), std::fmin(dx, dy)) || !agrees(ast::fminf(x, y), std::fmin(x, y)) ||
                !agrees(ast::fmodf(x, y), std::fmod(x, y)) || !agrees(ast::hypotf(x, y), std::hypot(x, y)) ||
                !agrees(ast::powf(x, y), std::pow(x, y)) || !agrees(ast::copysignf(x, y), std::copysign(x, y)) ||
                std::signbit(ast::copysignf(x, y)) != std::signbit(y)) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace

int main()
{
    if (!check_classification()) {
        return 1;
    }
    if (!check_exponents()) {
        return 2;
    }
    if (!check_transcendentals()) {
        return 3;
    }
    return check_binary_functions() ? 0 : 4;
}
