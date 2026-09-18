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

#ifndef CANN_ASC_STL_STD_DETAIL_EXPECTED_BAD_EXPECTED_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_EXPECTED_BAD_EXPECTED_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/exceptions.h>
#include <asc/std/__asc/unreachable.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()
#if __cpp_lib_expected >= 202202L
#include <expected>
#else  // ^^^ __cpp_lib_expected >= 202202L ^^^ / vvv __cpp_lib_expected < 202202L vvv
#include <exception>
#endif  // ^^^ __cpp_lib_expected < 202202L ^^^
#endif  // CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

#if __cpp_lib_expected >= 202202L

using ::std::bad_expected_access;

#else  // ^^^ __cpp_lib_expected >= 202202L ^^^ / vvv __cpp_lib_expected < 202202L vvv

template <class _Err>
class bad_expected_access;

template <>
class bad_expected_access<void> : public ::std::exception {
public:
    const char* what() const noexcept override
    {
        return "bad access to asc::std::expected";
    }
};

template <class _Err>
class bad_expected_access : public bad_expected_access<void> {
public:
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit bad_expected_access(_Err __e) : __unex_(::asc::std::move(__e))
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~bad_expected_access() noexcept override = default;

    CANN_ASC_STL_API _Err& error() & noexcept
    {
        return __unex_;
    }

    CANN_ASC_STL_API const _Err& error() const& noexcept
    {
        return __unex_;
    }

    CANN_ASC_STL_API _Err&& error() && noexcept
    {
        return ::asc::std::move(__unex_);
    }

    CANN_ASC_STL_API const _Err&& error() const&& noexcept
    {
        return ::asc::std::move(__unex_);
    }

private:
    _Err __unex_;
};

#endif  // ^^^ __cpp_lib_expected < 202202L ^^^

#endif  // CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Err, class _Arg>
[[noreturn]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __throw_bad_expected_access([[maybe_unused]] _Arg&& __arg)
{
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()
    throw ::asc::std::bad_expected_access<_Err>(
        ::asc::std::forward<_Arg>(__arg));  // NOLINT(build/include_what_you_use)
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED() ^^^ / vvv
       // !(CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOSTED()) vvv
    (void)__arg;
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
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

#endif  // CANN_ASC_STL_STD_DETAIL_EXPECTED_BAD_EXPECTED_ACCESS_H
