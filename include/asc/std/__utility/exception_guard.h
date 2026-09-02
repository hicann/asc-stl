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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_EXCEPTION_GUARD_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_EXCEPTION_GUARD_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Rollback>
struct __exception_guard_exceptions {
    __exception_guard_exceptions() = delete;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit __exception_guard_exceptions(_Rollback __rollback)
        : __rollback_(::asc::std::move(__rollback)), __completed_(false)
    {}

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __exception_guard_exceptions(
        __exception_guard_exceptions&& __other) noexcept(is_nothrow_move_constructible_v<_Rollback>)
        : __rollback_(::asc::std::move(__other.__rollback_)), __completed_(__other.__completed_)
    {
        __other.__completed_ = true;
    }

    __exception_guard_exceptions(const __exception_guard_exceptions&) = delete;
    __exception_guard_exceptions& operator=(const __exception_guard_exceptions&) = delete;
    __exception_guard_exceptions& operator=(__exception_guard_exceptions&&) = delete;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __complete() noexcept
    {
        __completed_ = true;
    }

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__exception_guard_exceptions()
    {
        if (!__completed_) {
            __rollback_();
        }
    }

private:
    _Rollback __rollback_;
    bool __completed_;
};

template <class _Rollback>
__exception_guard_exceptions(_Rollback) -> __exception_guard_exceptions<_Rollback>;

template <class _Rollback>
struct __exception_guard_noexceptions {
    __exception_guard_noexceptions() = delete;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit __exception_guard_noexceptions(_Rollback)
    {}

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __exception_guard_noexceptions(
        __exception_guard_noexceptions&& __other) noexcept(is_nothrow_move_constructible_v<_Rollback>)
        : __completed_(__other.__completed_)
    {
        __other.__completed_ = true;
    }

    __exception_guard_noexceptions(const __exception_guard_noexceptions&) = delete;
    __exception_guard_noexceptions& operator=(const __exception_guard_noexceptions&) = delete;
    __exception_guard_noexceptions& operator=(__exception_guard_noexceptions&&) = delete;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __complete() noexcept
    {
        __completed_ = true;
    }

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__exception_guard_noexceptions()
    {
        CANN_ASC_STL_DETAIL_ASSERT(__completed_, "__exception_guard not completed with exceptions disabled");
    }

private:
    bool __completed_ = false;
};

template <class _Rollback>
__exception_guard_noexceptions(_Rollback) -> __exception_guard_noexceptions<_Rollback>;

#if !CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
template <class _Rollback>
using __exception_guard = __exception_guard_noexceptions<_Rollback>;
#else
template <class _Rollback>
using __exception_guard = __exception_guard_exceptions<_Rollback>;
#endif

template <class _Rollback>
CANN_ASC_STL_API constexpr __exception_guard<_Rollback> __make_exception_guard(_Rollback __rollback)
{
    return __exception_guard<_Rollback>(::asc::std::move(__rollback));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_EXCEPTION_GUARD_H
