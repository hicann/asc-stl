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

#include <asc/std/system_error>

namespace asc_stl_test_system_error {

enum class application_error { unavailable };

CANN_ASC_STL_API int check(int seed = 7)
{
    using asc::std::errc;
    static_assert(asc::std::is_error_condition_enum<errc>{}());
    static_assert(!asc::std::is_error_code_enum<errc>{}());
    static_assert(!asc::std::is_error_condition_enum<application_error>::value);
    static_assert(!asc::std::is_error_code_enum<application_error>::value);
    return static_cast<errc>(seed + 15) != errc::invalid_argument ||
        static_cast<errc>(seed + 27) != errc::result_out_of_range ||
        static_cast<errc>(seed + 68) != errc::value_too_large || static_cast<errc>(seed - 7) != errc{};
}

}  // namespace asc_stl_test_system_error
