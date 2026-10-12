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

#ifndef CANN_ASC_STL_TEST_SUPPORT_B012_SEMANTICS_H
#define CANN_ASC_STL_TEST_SUPPORT_B012_SEMANTICS_H

#include <asc/devices>
#include <asc/std/__complex/complex.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/cmath>
#include <asc/std/__type_traits/is_same.h>

namespace asc_stl_b012_test {

static_assert(asc::std::is_same_v<decltype(asc::std::sin(1)), float>);
static_assert(asc::std::is_same_v<decltype(asc::std::sqrt(4.0F)), float>);
static_assert(asc::std::is_same_v<decltype(asc::std::hypot(3.0F, 4.0F)), float>);
static_assert(asc::device_ref(2).ordinal() == 2);
static_assert(asc::device_ref(2) == asc::device_ref(2));
static_assert(asc::device_ref(2) != asc::device_ref(3));
static_assert(static_cast<asc::std::uint32_t>(asc::npu_arch::ascend_3510) == 3510);
static_assert(asc::std::complex<float>(1.0F, 2.0F) + asc::std::complex<float>(3.0F, 4.0F) ==
    asc::std::complex<float>(4.0F, 6.0F));

inline int evaluate_runtime()
{
    if (asc::std::abs(-2.0F) != 2.0F || asc::std::hypot(3.0F, 4.0F) != 5.0F) {
        return 1;
    }
    if (!asc::std::isfinite(1.0F) || !asc::std::isnan(NAN) || !asc::std::signbit(-0.0F)) {
        return 2;
    }
    if (asc::std::lerp(2.0F, 6.0F, 0.5F) != 4.0F) {
        return 3;
    }
    return 0;
}

}  // namespace asc_stl_b012_test

#endif  // CANN_ASC_STL_TEST_SUPPORT_B012_SEMANTICS_H
