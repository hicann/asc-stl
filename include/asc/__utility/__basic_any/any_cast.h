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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ANY_CAST_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ANY_CAST_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/access.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/typeid.h>
#include <typeinfo>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __valid_any_cast
//!
template <class _Interface, class _Tp>
inline constexpr bool __valid_any_cast = true;

template <class _Interface, class _Tp>
inline constexpr bool __valid_any_cast<_Interface*, _Tp> = false;

template <class _Interface, class _Tp>
inline constexpr bool __valid_any_cast<_Interface*, _Tp*> =
    !::asc::std::is_const_v<_Interface> || ::asc::std::is_const_v<_Tp>;

//!
//! __any_cast
//!
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Interface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__satisfies<_Tp, _Interface> || ::asc::std::is_void_v<_Tp>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __any_cast(__basic_any<_Interface>* __self) noexcept -> _Tp*
{
    static_assert(__valid_any_cast<_Interface, _Tp>);
    if (__self && (::asc::std::is_void_v<_Tp> || __self->type() == ::asc::std::__typeid<_Tp>())) {
        return static_cast<_Tp*>(__basic_any_access::__get_optr(*__self));
    }
    return nullptr;
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Interface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__satisfies<_Tp, _Interface> || ::asc::std::is_void_v<_Tp>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __any_cast(
    __basic_any<_Interface> const* __self) noexcept -> _Tp const*
{
    static_assert(__valid_any_cast<_Interface, _Tp>);
    if (__self && (::asc::std::is_void_v<_Tp> || __self->type() == ::asc::std::__typeid<_Tp>())) {
        return static_cast<_Tp const*>(__basic_any_access::__get_optr(*__self));
    }
    return nullptr;
}

// TODO: implement the same overloads as for std::__any_cast

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ANY_CAST_H
