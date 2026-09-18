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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __variant_detail::__access {
struct __union {
    template <class _Vp>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto&& __get_alt(_Vp&& __v, in_place_index_t<0>) noexcept
    {
        return ::asc::std::forward<_Vp>(__v).__head_;
    }

    template <class _Vp, size_t _Ip>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto&& __get_alt(_Vp&& __v, in_place_index_t<_Ip>) noexcept
    {
        return __get_alt(::asc::std::forward<_Vp>(__v).__tail_, in_place_index<_Ip - 1>);
    }
};

struct __base {
    template <size_t _Ip, class _Vp>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto&& __get_alt(_Vp&& __v) noexcept
    {
        return __union::__get_alt(::asc::std::forward<_Vp>(__v).__data_, in_place_index<_Ip>);
    }
};

struct __variant {
    template <size_t _Ip, class _Vp>
    [[nodiscard]] CANN_ASC_STL_API static constexpr auto&& __get_alt(_Vp&& __v) noexcept
    {
        return __base::__get_alt<_Ip>(::asc::std::forward<_Vp>(__v).__impl_);  // NOLINT(build/include_what_you_use)
    }
};
}  // namespace __variant_detail::__access

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_ACCESS_H
