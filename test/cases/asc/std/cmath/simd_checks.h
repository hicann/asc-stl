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

#pragma once

#include <asc/std/bit>
#include <asc/std/cmath>

#include "binary64_checks.h"

namespace asc_stl_test_cmath {

CANN_ASC_STL_API int check(int seed = 7)
{
    const unsigned fraction = static_cast<unsigned>(seed);
    const auto nan = asc::std::bit_cast<float>(0xffc00000U | fraction);
    const auto tiny = asc::std::bit_cast<float>(0x80000000U | fraction);
    const auto negative_zero = asc::std::bit_cast<float>(0x80000000U);
    const auto infinity = asc::std::bit_cast<float>(0xff800000U);
    const auto wide = asc::std::bit_cast<double>(0xfff8000000000000ULL | fraction);
    return !check_binary64(seed) || asc::std::bit_cast<unsigned>(asc::std::fabs(nan)) != (0x7fc00000U | fraction) ||
        asc::std::bit_cast<unsigned>(asc::std::abs(tiny)) != fraction ||
        asc::std::bit_cast<unsigned>(asc::std::fabsf(negative_zero)) != 0 ||
        asc::std::bit_cast<unsigned>(asc::std::fabsf(infinity)) != 0x7f800000U ||
        asc::std::bit_cast<__UINT64_TYPE__>(asc::std::fabs(wide)) != (0x7ff8000000000000ULL | fraction);
}

}  // namespace asc_stl_test_cmath
