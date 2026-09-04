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

#ifndef CANN_ASC_STL_STD_DETAIL_OPTIONAL_BAD_OPTIONAL_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_OPTIONAL_BAD_OPTIONAL_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/exceptions.h>
#include <asc/std/__asc/unreachable.h>

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

#if __cpp_lib_optional >= 201606L
#include <optional>
#else  // ^^^ __cpp_lib_optional >= 201606L ^^^ / vvv __cpp_lib_optional < 201606L vvv
#include <exception>
#endif  // ^^^ __cpp_lib_optional < 201606L ^^^

#endif  // CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

#if __cpp_lib_optional >= 201606L

using ::std::bad_optional_access;

#else   // ^^^ __cpp_lib_optional >= 201606L ^^^ / vvv __cpp_lib_optional < 201606L vvv
class bad_optional_access : public ::std::exception {
public:
    const char* what() const noexcept override
    {
        return "bad access to asc::std::optional";
    }
};
#endif  // ^^^ __cpp_lib_optional < 201606L ^^^

#endif  // CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

[[noreturn]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __throw_bad_optional_access()
{
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()
    throw asc::std::bad_optional_access();
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED() ^^^ / vvv
       // !(CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()) vvv
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // Bisheng lowers __builtin_trap() to an unsupported host abort symbol on AI Core.
    trap();
    for (;;) {
    }
#else   // ^^^ CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() ^^^ / vvv !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() vvv
    __builtin_trap();
#endif  // ^^^ !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() ^^^
    CANN_ASC_STL_DETAIL_UNREACHABLE();
#endif  // ^^^ !(CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()) ^^^
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_OPTIONAL_BAD_OPTIONAL_ACCESS_H
