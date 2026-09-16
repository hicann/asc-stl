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

#include <asc/std/__bit/integral.h>
#include <asc/std/__complex/exponential_functions.h>
#include <asc/std/__complex/inverse_hyperbolic_functions.h>
#include <asc/std/__complex/inverse_trigonometric_functions.h>
#include <asc/std/__complex/roots.h>
#include <asc/std/__complex/trigonometric_functions.h>

namespace asc_stl_b015_runtime {
CANN_ASC_STL_API void evaluate(__INT32_TYPE__* output)
{
    int failures = asc::std::bit_ceil(11U) != 16U;
#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    const asc::std::complex<float> value(1.0F, 0.5F);
    const auto round_trip = asc::std::exp(asc::std::log(value));
    failures += __builtin_fabsf(round_trip.real() - value.real()) > 0.001F;
    failures += __builtin_fabsf(round_trip.imag() - value.imag()) > 0.001F;
    const auto square = asc::std::sqrt(value * value);
    failures += __builtin_fabsf(square.real() - value.real()) > 0.001F;
    failures += asc::std::sin(value).real() != asc::std::sin(value).real();
    failures += asc::std::asinh(value).real() != asc::std::asinh(value).real();
    failures += asc::std::asin(value).real() != asc::std::asin(value).real();
#endif
    output[0] = failures;
}
}  // namespace asc_stl_b015_runtime
