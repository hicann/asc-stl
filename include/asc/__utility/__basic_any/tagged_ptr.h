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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_TAGGED_PTR_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_TAGGED_PTR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Ptr>
struct __tagged_ptr;

template <class _Tp>
struct __tagged_ptr<_Tp*> {
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __set(_Tp* __pv, bool __flag) noexcept
    {
        __ptr_ = reinterpret_cast<uintptr_t>(__pv) | uintptr_t(__flag);
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get() const noexcept -> _Tp*
    {
        return reinterpret_cast<_Tp*>(__ptr_ & ~uintptr_t(1));
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __flag() const noexcept -> bool
    {
        return static_cast<bool>(__ptr_ & uintptr_t(1));
    }

    uintptr_t __ptr_ = 0;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_TAGGED_PTR_H
