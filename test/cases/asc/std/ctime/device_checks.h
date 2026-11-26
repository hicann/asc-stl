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

#ifndef ASC_STL_TEST_CTIME_DEVICE_CHECKS_H
#define ASC_STL_TEST_CTIME_DEVICE_CHECKS_H

#include <asc/std/ctime>
#include <asc/std/bit>
#include <asc/std/limits>

namespace asc_stl_test_ctime {

CANN_ASC_STL_API int check(int seed = 7)
{
    using T = asc::std::time_t;
    const T high = asc::std::numeric_limits<T>::max();
    const T low = asc::std::numeric_limits<T>::lowest();
    const auto offset = static_cast<T>(seed & 1);
    const auto nearby = asc::std::difftime(high - offset, high - offset - 1);
    if (asc::std::bit_cast<__UINT64_TYPE__>(nearby) != 0x3ff0000000000000ULL ||
        asc::std::bit_cast<__UINT64_TYPE__>(asc::std::difftime(low + offset, low + offset)) != 0) {
        return 1;
    }
    if constexpr (sizeof(T) == 8 && asc::std::numeric_limits<T>::is_signed) {
        const auto forward = asc::std::difftime(high - offset, low);
        const auto backward = asc::std::difftime(low, high - offset);
        if (asc::std::bit_cast<__UINT64_TYPE__>(forward) != 0x43f0000000000000ULL ||
            asc::std::bit_cast<__UINT64_TYPE__>(backward) != 0xc3f0000000000000ULL) {
            return 2;
        }
        const T base = static_cast<T>(0x20000000000000LL);
        const auto even = asc::std::difftime(base + 1 + offset, offset);
        const auto odd = asc::std::difftime(offset, base + 3 + offset);
        return asc::std::bit_cast<__UINT64_TYPE__>(even) != 0x4340000000000000ULL ||
            asc::std::bit_cast<__UINT64_TYPE__>(odd) != 0xc340000000000002ULL;
    }
    return 0;
}

}  // namespace asc_stl_test_ctime

#endif  // ASC_STL_TEST_CTIME_DEVICE_CHECKS_H
