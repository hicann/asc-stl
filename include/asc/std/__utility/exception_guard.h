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

#ifndef CANN_ASC_STL_ASC_STD___UTILITY_EXCEPTION_GUARD_H
#define CANN_ASC_STL_ASC_STD___UTILITY_EXCEPTION_GUARD_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Rollback>
class __exception_guard {
public:
    __exception_guard() = delete;
    CANN_ASC_STL_API explicit constexpr __exception_guard(Rollback rollback) : rollback_(::asc::std::move(rollback))
    {}
    CANN_ASC_STL_API constexpr __exception_guard(__exception_guard&& other) noexcept(
        is_nothrow_move_constructible_v<Rollback>)
        : rollback_(::asc::std::move(other.rollback_)), completed_(::asc::std::exchange(other.completed_, true))
    {}
    __exception_guard(const __exception_guard&) = delete;
    __exception_guard& operator=(const __exception_guard&) = delete;
    __exception_guard& operator=(__exception_guard&&) = delete;
    CANN_ASC_STL_API constexpr void __complete() noexcept
    {
        completed_ = true;
    }
    CANN_ASC_STL_API ~__exception_guard()
    {
        if (!completed_) {
            rollback_();
        }
    }

private:
    Rollback rollback_;
    bool completed_{false};
};
template <class Rollback>
CANN_ASC_STL_API constexpr __exception_guard<Rollback> __make_exception_guard(Rollback rollback)
{
    return __exception_guard<Rollback>(::asc::std::move(rollback));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___UTILITY_EXCEPTION_GUARD_H
