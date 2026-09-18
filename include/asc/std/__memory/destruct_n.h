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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_DESTRUCT_N_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_DESTRUCT_N_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct __destruct_n {
private:
    size_t __size_;

    template <class _Tp>
    CANN_ASC_STL_API void __process(_Tp* __p, false_type) noexcept
    {
        for (size_t __i = 0; __i < __size_; ++__i, ++__p) {
            __p->~_Tp();
        }
    }

    template <class _Tp>
    CANN_ASC_STL_API void __process(_Tp*, true_type) noexcept
    {}

    CANN_ASC_STL_API void __incr(false_type) noexcept
    {
        ++__size_;
    }
    CANN_ASC_STL_API void __incr(true_type) noexcept
    {}

    CANN_ASC_STL_API void __set(size_t __s, false_type) noexcept
    {
        __size_ = __s;
    }
    CANN_ASC_STL_API void __set(size_t, true_type) noexcept
    {}

public:
    CANN_ASC_STL_API explicit __destruct_n(size_t __s) noexcept : __size_(__s)
    {}

    template <class _Tp>
    CANN_ASC_STL_API void __incr() noexcept
    {
        __incr(integral_constant<bool, is_trivially_destructible_v<_Tp>>());
    }

    template <class _Tp>
    CANN_ASC_STL_API void __set(size_t __s, _Tp*) noexcept
    {
        __set(__s, integral_constant<bool, is_trivially_destructible_v<_Tp>>());
    }

    template <class _Tp>
    CANN_ASC_STL_API void operator()(_Tp* __p) noexcept
    {
        __process(__p, integral_constant<bool, is_trivially_destructible_v<_Tp>>());
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_DESTRUCT_N_H
