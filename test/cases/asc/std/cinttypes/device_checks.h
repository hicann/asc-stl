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

#include <asc/std/cinttypes>

namespace asc_stl_test_cinttypes {

CANN_ASC_STL_API int check()
{
    static_assert(sizeof(asc::std::intmax_t) == sizeof(asc::std::uintmax_t));
    static_assert(asc::std::imaxabs(-41) == 41 && asc::std::imaxabs(0) == 0);
    for (int n = -19; n <= 19; ++n) {
        for (int d = -5; d <= 5; ++d) {
            if (d == 0)
                continue;
            asc::std::imaxdiv_t result = asc::std::imaxdiv(n, d);
            if (result.quot != n / d || result.rem != n % d || result.quot * d + result.rem != n)
                return 1;
        }
    }
    return 0;
}

}  // namespace asc_stl_test_cinttypes
