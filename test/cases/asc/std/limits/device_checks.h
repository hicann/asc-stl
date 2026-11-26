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

#ifndef ASC_STL_TEST_LIMITS_DEVICE_CHECKS_H
#define ASC_STL_TEST_LIMITS_DEVICE_CHECKS_H

#include "extended_checks.h"

namespace asc_stl_test_limits {

CANN_ASC_STL_API int check(int seed = 7)
{
    using integer = asc::std::numeric_limits<int>;
    using floating = asc::std::numeric_limits<float>;
    static_assert(integer::is_signed && integer::is_integer && integer::digits >= 15);
    static_assert(floating::is_specialized && floating::radix == 2 && floating::digits == 24);
    const int bounded = seed & 7;
    const float value = static_cast<float>(bounded + 1);
    if (integer::max() - bounded <= integer::lowest() ||
        !(floating::min() < value && value < floating::max() && floating::lowest() < -value) ||
        !(floating::epsilon() > 0.0F && floating::epsilon() < 1.0F))
        return 1;
    return extended_limits(seed);
}

}  // namespace asc_stl_test_limits

#endif  // ASC_STL_TEST_LIMITS_DEVICE_CHECKS_H
