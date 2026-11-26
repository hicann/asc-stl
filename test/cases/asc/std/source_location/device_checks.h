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

#ifndef ASC_STL_TEST_SOURCE_LOCATION_DEVICE_CHECKS_H
#define ASC_STL_TEST_SOURCE_LOCATION_DEVICE_CHECKS_H

#include <asc/std/source_location>

namespace asc_stl_test_source_location {

CANN_ASC_STL_API int check()
{
    using location = asc::std::source_location;
    constexpr auto explicit_site = location::current(nullptr, nullptr, 65535U, 23U);
    static_assert(explicit_site.line() == 65535U && explicit_site.column() == 23U);
    constexpr unsigned line = __LINE__ + 1;
    constexpr auto captured = location::current();
    if (captured.line() != line || explicit_site.file_name() != nullptr || explicit_site.function_name() != nullptr)
        return 1;
    const auto copy = captured;
    return copy.line() == captured.line() && copy.column() == captured.column() ? 0 : 2;
}

}  // namespace asc_stl_test_source_location

#endif  // ASC_STL_TEST_SOURCE_LOCATION_DEVICE_CHECKS_H
