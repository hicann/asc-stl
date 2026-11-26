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

#ifndef ASC_STL_TEST_CMATH_BINARY64_CHECKS_H
#define ASC_STL_TEST_CMATH_BINARY64_CHECKS_H

#include <asc/std/bit>
#include <asc/std/cmath>

namespace asc_stl_test_cmath {

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE bool binary64_category(__UINT64_TYPE__ bits, int category, bool negative)
{
    namespace s = ::asc::std;
    const double value = s::bit_cast<double>(bits);
    return s::fpclassify(value) == category && s::isnan(value) == (category == FP_NAN) &&
        s::isinf(value) == (category == FP_INFINITE) &&
        s::isfinite(value) == (category != FP_INFINITE && category != FP_NAN) &&
        s::isnormal(value) == (category == FP_NORMAL) && s::signbit(value) == negative;
}

CANN_ASC_STL_API bool check_binary64(int seed)
{
    const auto payload = static_cast<unsigned>(seed);
    return binary64_category(0U, FP_ZERO, false) && binary64_category(0x8000000000000000ULL, FP_ZERO, true) &&
        binary64_category(1U, FP_SUBNORMAL, false) && binary64_category(0x800fffffffffffffULL, FP_SUBNORMAL, true) &&
        binary64_category(0x0010000000000000ULL, FP_NORMAL, false) &&
        binary64_category(0xffefffffffffffffULL, FP_NORMAL, true) &&
        binary64_category(0x7ff0000000000000ULL, FP_INFINITE, false) &&
        binary64_category(0xfff0000000000000ULL, FP_INFINITE, true) &&
        binary64_category(0x7ff0000000000000ULL | payload, FP_NAN, false) &&
        binary64_category(0xfff8000000000000ULL | payload, FP_NAN, true);
}

}  // namespace asc_stl_test_cmath

#endif  // ASC_STL_TEST_CMATH_BINARY64_CHECKS_H
