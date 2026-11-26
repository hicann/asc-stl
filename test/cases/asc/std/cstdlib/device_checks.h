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

#include <asc/std/cstdlib>

namespace asc_stl_test_cstdlib {

template <class T>
CANN_ASC_STL_API bool signed_arithmetic(T value)
{
    const auto negative = asc::std::div(-value, T{3});
    const auto opposite = asc::std::div(value, T{-3});
    const auto both = asc::std::div(-value, T{-3});
    const auto zero = asc::std::div(T{0}, value);
    return negative.quot == -2 && negative.rem == -1 && opposite.quot == -2 && opposite.rem == 1 && both.quot == 2 &&
        both.rem == -1 && zero.quot == 0 && zero.rem == 0 && asc::std::abs(-value) == value && asc::std::abs(T{0}) == 0;
}

CANN_ASC_STL_API int check(int seed = 7)
{
    if (!signed_arithmetic(seed) || !signed_arithmetic(static_cast<long>(seed)) ||
        !signed_arithmetic(static_cast<long long>(seed)))
        return 1;
    const long long large = (1LL << 42) + seed;
    const auto long_result = asc::std::ldiv(-static_cast<long>(seed), 3L);
    const auto wide_result = asc::std::lldiv(-large, 4LL);
    return asc::std::labs(-static_cast<long>(seed)) != 7L || asc::std::llabs(-large) != large ||
        long_result.quot != -2 || long_result.rem != -1 || wide_result.quot != -((1LL << 40) + 1) ||
        wide_result.rem != -3;
}

}  // namespace asc_stl_test_cstdlib
