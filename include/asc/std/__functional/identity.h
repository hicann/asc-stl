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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_IDENTITY_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_IDENTITY_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
inline constexpr bool __is_identity_v = false;

struct identity {
    template <class _Tp>
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp&& operator()(_Tp&& __t) const noexcept
    {
        return ::asc::std::forward<_Tp>(__t);  // NOLINT(build/include_what_you_use)
    }

    using is_transparent = void;
};

template <>
inline constexpr bool __is_identity_v<identity> = true;
template <>
inline constexpr bool __is_identity_v<reference_wrapper<identity>> = true;
template <>
inline constexpr bool __is_identity_v<reference_wrapper<const identity>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_IDENTITY_H
