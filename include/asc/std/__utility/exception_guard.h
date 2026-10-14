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

// <asc/__config> does not define the following macros; provide minimal
// equivalents here, #ifndef-guarded against future definitions.
#ifndef CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#if __cplusplus >= 202002L
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20

#ifndef CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS
#if defined(ASC_DISABLE_EXCEPTIONS)
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()  // device compilation has no exceptions
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#elif defined(__EXCEPTIONS)  // disabled with -fno-exceptions
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS

#ifndef CANN_ASC_STL_DETAIL_ASSERT
// The device side has no assertion mechanism, so this is always a no-op; on
// the host it checks only when ASC_ENABLE_HOST_ASSERTIONS is explicitly enabled.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Rollback>
struct __exception_guard_exceptions {
    __exception_guard_exceptions() = delete;
    CANN_ASC_STL_API explicit constexpr __exception_guard_exceptions(Rollback rollback)
        : rollback_(::asc::std::move(rollback)), completed_(false)
    {}
    CANN_ASC_STL_API constexpr __exception_guard_exceptions(__exception_guard_exceptions&& other) noexcept(
        is_nothrow_move_constructible_v<Rollback>)
        : rollback_(::asc::std::move(other.rollback_)), completed_(other.completed_)
    {
        other.completed_ = true;
    }
    __exception_guard_exceptions(const __exception_guard_exceptions&) = delete;
    __exception_guard_exceptions& operator=(const __exception_guard_exceptions&) = delete;
    __exception_guard_exceptions& operator=(__exception_guard_exceptions&&) = delete;
    CANN_ASC_STL_API constexpr void __complete() noexcept
    {
        completed_ = true;
    }
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__exception_guard_exceptions()
    {
        if (!completed_) {
            rollback_();
        }
    }

private:
    Rollback rollback_;
    bool completed_;
};

template <class Rollback>
__exception_guard_exceptions(Rollback) -> __exception_guard_exceptions<Rollback>;

template <class Rollback>
struct __exception_guard_noexceptions {
    __exception_guard_noexceptions() = delete;
    CANN_ASC_STL_API explicit constexpr __exception_guard_noexceptions(Rollback)
    {}
    CANN_ASC_STL_API constexpr __exception_guard_noexceptions(__exception_guard_noexceptions&& other) noexcept(
        is_nothrow_move_constructible_v<Rollback>)
        : completed_(other.completed_)
    {
        other.completed_ = true;
    }
    __exception_guard_noexceptions(const __exception_guard_noexceptions&) = delete;
    __exception_guard_noexceptions& operator=(const __exception_guard_noexceptions&) = delete;
    __exception_guard_noexceptions& operator=(__exception_guard_noexceptions&&) = delete;
    CANN_ASC_STL_API constexpr void __complete() noexcept
    {
        completed_ = true;
    }
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__exception_guard_noexceptions()
    {
        CANN_ASC_STL_DETAIL_ASSERT(completed_, "__exception_guard not completed with exceptions disabled");
    }

private:
    bool completed_ = false;
};

template <class Rollback>
__exception_guard_noexceptions(Rollback) -> __exception_guard_noexceptions<Rollback>;

#if !CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
template <class Rollback>
using __exception_guard = __exception_guard_noexceptions<Rollback>;
#else
template <class Rollback>
using __exception_guard = __exception_guard_exceptions<Rollback>;
#endif

template <class Rollback>
CANN_ASC_STL_API constexpr __exception_guard<Rollback> __make_exception_guard(Rollback rollback)
{
    return __exception_guard<Rollback>(::asc::std::move(rollback));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___UTILITY_EXCEPTION_GUARD_H
