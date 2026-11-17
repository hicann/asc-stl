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

#include <asc/std/__complex/complex.h>

#include <cmath>
#include <complex>
#include <limits>

#include "support/b012_semantics.h"

// A frequency-response estimate divides each measured spectrum bin Y[k]
// by its nonzero excitation X[k]. Widen inputs before computing the oracle:
// float intermediate overflow must not invalidate a representable quotient.
int evaluate_frequency_response()
{
    using C = asc::std::complex<float>;
    struct Bin {
        float yr, yi, xr, xi;
    };
    const float large = std::numeric_limits<float>::max();
    const float tiny = std::numeric_limits<float>::min();
    const Bin bins[] = {
        {1, 2, 2, 1},
        {large, large, 1, 1},
        {large, -large, 1, 1},
        {large, large, 0.5f, 0.5f},
        {large, -large, 0.5f, 0.5f},
        {large, large, 0.5f, 1},
        {large, large, 1, 0.5f},
        {large, large, large, large},
        {1, 1, large, large},
        {tiny, tiny, tiny, tiny},
        {1, 0, tiny, 0},
        {0, 1, tiny, 0},
        {large, 0, tiny, 0},
        {0, large, 0, tiny},
    };
    const auto close = [](float actual, double expected_wide) {
        const float expected = static_cast<float>(expected_wide);
        return actual == expected ||
            (std::isfinite(actual) && std::isfinite(expected) &&
                std::abs(actual - expected) <=
                    2e-6f * std::abs(expected) + 2 * std::numeric_limits<float>::denorm_min());
    };
    for (const Bin& bin : bins) {
        const C divisor(bin.xr, bin.xi);
        const C quotient = C(bin.yr, bin.yi) / divisor;
        C assigned(bin.yr, bin.yi);
        assigned /= divisor;
        const auto expected = std::complex<double>(bin.yr, bin.yi) / std::complex<double>(bin.xr, bin.xi);
        const auto scalar_expected = static_cast<double>(bin.yr) / std::complex<double>(bin.xr, bin.xi);
        const C scalar_quotient = bin.yr / divisor;
        if (!close(quotient.real(), expected.real()) || !close(quotient.imag(), expected.imag()) ||
            !close(assigned.real(), expected.real()) || !close(assigned.imag(), expected.imag()) ||
            !close(scalar_quotient.real(), scalar_expected.real()) ||
            !close(scalar_quotient.imag(), scalar_expected.imag())) {
            return 5;
        }
    }
    const float infinity = std::numeric_limits<float>::infinity();
    const C by_infinity = C(1, 2) / C(infinity, 0);
    const C by_zero = C(1, 2) / C(0, 0);
    const C with_nan = C(std::numeric_limits<float>::quiet_NaN(), 2) / C(1, 1);
    if (by_infinity.real() != 0 || by_infinity.imag() != 0 || !std::isinf(by_zero.real()) ||
        !std::isinf(by_zero.imag()) || !std::isnan(with_nan.real()) || !std::isnan(with_nan.imag())) {
        return 6;
    }
    return 0;
}

constexpr auto finite_quotient = asc::std::complex<float>(2, 4) / asc::std::complex<float>(2, 0);
static_assert(finite_quotient.real() == 1 && finite_quotient.imag() == 2);

int main()
{
    const int basic = asc_stl_b012_test::evaluate_runtime();
    return basic != 0 ? basic : evaluate_frequency_response();
}
