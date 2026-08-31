/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_SYSTEM_ERROR_ERRC_H
#define CANN_ASC_STL_STD_DETAIL_SYSTEM_ERROR_ERRC_H

#include <asc/std/detail/__config>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <system_error>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HOSTED()
using ::std::errc;
#else  // ^^^ CANN_ASC_STL_DETAIL_HOSTED() ^^^ / vvv CANN_ASC_STL_DETAIL_FREESTANDING() vvv
enum class errc {
    invalid_argument = 22,
    result_out_of_range = 34,
#if CANN_ASC_STL_DETAIL_OS(WINDOWS)
    value_too_large = 132,
#else   // ^^^ CANN_ASC_STL_DETAIL_OS(WINDOWS) ^^^ / vvv !CANN_ASC_STL_DETAIL_OS(WINDOWS) vvv
    value_too_large = 75,
#endif  // ^^^ !CANN_ASC_STL_DETAIL_OS(WINDOWS) ^^^
};
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_SYSTEM_ERROR_ERRC_H
