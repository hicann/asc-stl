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

#include <asc/std/ctime>
#include "time_fields.h"

namespace asc_stl_b021_runtime {
template <class OutputPointer>
CANN_ASC_STL_API void evaluate(OutputPointer output)
{
    const auto before = asc::std::clock();
    const auto after = asc::std::clock();
    asc_stl_time_fields_test::write_fields(output, before);
    output[0] = (before == static_cast<asc::std::clock_t>(-1) ? 1 : 0) | (after < before ? 2 : 0) |
        (CLOCKS_PER_SEC != 1000000000L ? 4 : 0);
}
}  // namespace asc_stl_b021_runtime
