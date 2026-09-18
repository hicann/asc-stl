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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VIRTUAL_PTRS_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VIRTUAL_PTRS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/std/__exception/terminate.h>
#include <asc/std/__utility/typeid.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

struct __base_vptr {
    __base_vptr() = default;

    CANN_ASC_STL_DETAIL_NODEBUG_API constexpr __base_vptr(__rtti_base const* __vptr) noexcept : __vptr_(__vptr)
    {}

    template <class _VTable>
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API explicit constexpr operator _VTable const*() const noexcept
    {
        auto const* __vptr = static_cast<_VTable const*>(__vptr_);
        CANN_ASC_STL_DETAIL_ASSERT(::asc::std::__typeid<_VTable>() == *__vptr->__typeid_, "bad vtable cast detected");
        return __vptr;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API explicit constexpr operator bool() const noexcept
    {
        return __vptr_ != nullptr;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API constexpr auto operator->() const noexcept -> __rtti_base const*
    {
        return __vptr_;
    }

#if !defined(CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON)
    bool operator==(__base_vptr const& __other) const noexcept = default;
#else   // ^^^ !CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON ^^^ / vvv CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON vvv
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API friend constexpr auto operator==(
        __base_vptr __lhs, __base_vptr __rhs) noexcept -> bool
    {
        return __lhs.__vptr_ == __rhs.__vptr_;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API friend constexpr auto operator!=(
        __base_vptr __lhs, __base_vptr __rhs) noexcept -> bool
    {
        return !(__lhs == __rhs);
    }
#endif  // CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON

    __rtti_base const* __vptr_{};
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VIRTUAL_PTRS_H
