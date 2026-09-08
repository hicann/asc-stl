/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef ASC_STL_TEST_B015_SEMANTICS_H
#define ASC_STL_TEST_B015_SEMANTICS_H
#include <asc/__hierarchy/query.h>
#include <asc/__memory/resources.h>
#include <asc/__runtime/launch.h>
#include <asc/execution.policy.h>
#include <asc/std/__algorithm/find.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__bit/countr.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__bit/popcount.h>
#include <asc/std/__complex/exponential_functions.h>
#include <asc/std/__complex/inverse_hyperbolic_functions.h>
#include <asc/std/__complex/inverse_trigonometric_functions.h>
#include <asc/std/__complex/logarithms.h>
#include <asc/std/__complex/roots.h>
#include <asc/std/__complex/trigonometric_functions.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__fwd/string_view.h>
#include <asc/std/__string/char_traits.h>
#include <asc/std/__string/helper_functions.h>
#include <asc/std/__tuple/ignore.h>
#include <asc/std/__type_traits/integral_constant_like.h>
#include <asc/std/__utility/exception_guard.h>
namespace asc_stl_b015_test {
CANN_ASC_STL_API int evaluate_common() noexcept
{
    int failures = 0;
    unsigned int values[] = {0U, 1U, 8U, 15U};
    failures += asc::std::find(values, values + 4, 8U) != values + 2;
    failures += asc::std::countl_zero(1U) != 31;
    failures += asc::std::countr_zero(8U) != 3;
    failures += asc::std::popcount(15U) != 4;
    failures += asc::std::bit_width(8U) != 4;
    failures += asc::std::bit_floor(11U) != 8U;
    failures += asc::std::bit_ceil(11U) != 16U;
    failures += asc::std::plus<int>{}(2, 3) != 5;
    failures += !asc::std::ranges::less{}(2, 3);
    const char text[] = {'a', 's', 'c', '\0'};
    failures += asc::std::char_traits<char>::length(text) != 3;
    int ignored = 0;
    asc::std::ignore = ignored;
    failures += asc::detail::hierarchy_zero() != 0;
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    const auto requirements =
        asc::require(asc::require(asc::determinism::run_to_run), asc::output_ordering::stable_sorted);
    failures += requirements.determinism_value() != asc::determinism::run_to_run;
    failures += requirements.output_ordering_value() != asc::output_ordering::stable_sorted;
    failures += requirements.tie_break_value() != asc::tie_break::unspecified;
    int storage = 0;
    const auto policy =
        asc::execution::device.with_temporary_storage({&storage, sizeof(storage), asc::memory_space::host})
            .require(requirements);
    failures += policy.temporary_storage().data() != &storage;
    failures += policy.requirements().determinism_value() != asc::determinism::run_to_run;
#endif
#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    const asc::std::complex<float> value(1.0F, 0.5F);
    const auto round_trip = asc::std::exp(asc::std::log(value));
    failures += __builtin_fabsf(round_trip.real() - value.real()) > 0.001F;
    failures += __builtin_fabsf(round_trip.imag() - value.imag()) > 0.001F;
    const auto square = asc::std::sqrt(value * value);
    failures += __builtin_fabsf(square.real() - value.real()) > 0.001F;
    const auto trigonometric = asc::std::sin(value);
    failures += trigonometric.real() != trigonometric.real();
    const auto inverse = asc::std::asinh(value);
    failures += inverse.real() != inverse.real();
#endif
    return failures;
}
}  // namespace asc_stl_b015_test
#endif  // ASC_STL_TEST_B015_SEMANTICS_H
