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

#ifndef ASC_STL_TEST_B014_SEMANTICS_H
#define ASC_STL_TEST_B014_SEMANTICS_H

#include <asc/__execution/policy.h>
#include <asc/__execution/requirements.h>
#include <asc/__warp/operations.h>
#include <asc/std/__algorithm/fill.h>
#include <asc/std/__algorithm/max.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__complex/arg.h>
#include <asc/std/__complex/hyperbolic_functions.h>
#include <asc/std/__complex/literals.h>
#include <asc/std/__complex/math.h>
#include <asc/std/tuple>
#include <asc/std/__functional/hash.h>
#include <asc/std/__tuple/apply.h>
#include <asc/std/__tuple/get.h>
#include <asc/std/__tuple/tie.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_cat.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__variant/get.h>
#include <asc/std/__variant/hash.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/cstdlib>
#include <asc/std/variant>

namespace asc_stl_b014_test {

CANN_ASC_STL_API constexpr int add(int left, int right) noexcept
{
    return left + right;
}

enum class hash_enum : unsigned int { value = 7 };

CANN_ASC_STL_API int evaluate_common() noexcept
{
    int failures = 0;
    int values[3] = {};
    asc::std::fill(values, values + 3, 4);
    failures += values[0] != 4 || values[2] != 4;
    failures += asc::std::min(3, 2) != 2 ||  // NOLINT(build/include_what_you_use)
        asc::std::max(3, 2) != 3;            // NOLINT(build/include_what_you_use)
    failures += asc::std::cmp_less(-1, 1U) == false;
    failures += asc::std::in_range<unsigned char>(255) == false;

    auto tuple = asc::std::make_tuple(1, 2);
    failures += asc::std::get<0>(tuple) != 1 || asc::std::get<int>(tuple) != 1;
    failures += asc::std::apply(add, tuple) != 3;
    auto combined = asc::std::tuple_cat(tuple, asc::std::make_tuple(3));
    failures += asc::std::get<2>(combined) != 3;
    int tied = 0;
    asc::std::tie(tied) = asc::std::make_tuple(9);
    failures += tied != 9;

    asc::std::variant<int, long> variant(7);
    failures += !asc::std::holds_alternative<int>(variant);
    const int* first_alternative = asc::std::get_if<0>(&variant);
    failures += first_alternative == nullptr || *first_alternative != 7 || asc::std::get_if<long>(&variant) != nullptr;
    variant.emplace<1>(9L);
    const long* second_alternative = asc::std::get_if<long>(&variant);
    failures += second_alternative == nullptr || *second_alternative != 9L;
    failures += asc::std::hash<decltype(variant)>{}(variant) == 0;
    failures += asc::std::hash<int>{}(7) != asc::std::hash<int>{}(7);
    failures += asc::std::hash<hash_enum>{}(hash_enum::value) != asc::std::hash<unsigned int>{}(7U);
    failures += asc::std::hash<int*>{}(values) != asc::std::hash<int*>{}(values);

    asc::std::complex<float> complex_value(3.0F, 4.0F);
    failures += asc::std::real(complex_value) != 3.0F || asc::std::imag(complex_value) != 4.0F;
#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
    failures += asc::std::abs(complex_value) != 5.0F;
#endif
    failures += asc::std::get<0>(complex_value) != 3.0F || asc::std::get<1>(complex_value) != 4.0F;

    failures += asc::std::abs(-7) != 7 || asc::std::div(17, 5).quot != 3;
    failures += !asc::detail::warp_lane_is_active(4, 2);
    failures += !asc::detail::has_requirement(
        asc::detail::execution_requirement::host | asc::detail::execution_requirement::device,
        asc::detail::execution_requirement::device);
    asc::detail::execution_policy_state policy{};
    failures += policy.kind != asc::detail::execution_policy_kind::inline_host;
    return failures;
}

}  // namespace asc_stl_b014_test

#endif  // ASC_STL_TEST_B014_SEMANTICS_H
