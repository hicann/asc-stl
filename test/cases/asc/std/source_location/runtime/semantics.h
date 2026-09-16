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

#ifndef ASC_STL_TEST_ASC_STD_SOURCE_LOCATION_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_STD_SOURCE_LOCATION_RUNTIME_SEMANTICS_H

#include <asc/std/cstdint>
#include <asc/std/source_location>

namespace asc_stl_source_location_runtime {

CANN_ASC_STL_API void evaluate(asc::std::uint32_t* output)
{
    output[0] = 0x13579BDFU;
#line 321 "asc_stl_source_location_device.asc"
    const auto captured = asc::std::source_location::current();
#line 31 "semantics.h"
    const auto explicit_location = asc::std::source_location::current(nullptr, nullptr, 654, 23);
    output[1] = captured.line();
    output[2] = captured.column();
    output[3] = explicit_location.line();
    output[4] = explicit_location.column();
    output[5] = static_cast<asc::std::uint32_t>(sizeof(asc::std::source_location));
    output[6] = 0x2468ACE0U;
    output[7] = 0x55AA55AAU;
}

}  // namespace asc_stl_source_location_runtime

#endif  // ASC_STL_TEST_ASC_STD_SOURCE_LOCATION_RUNTIME_SEMANTICS_H
