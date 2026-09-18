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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_FROM_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_FROM_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <template <class...> class _Interface, class _Super>
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __basic_any_from(
    _Interface<_Super>&& __self) noexcept -> __basic_any<_Super>&&
{
    return static_cast<__basic_any<_Super>&&>(__self);
}

template <template <class...> class _Interface, class _Super>
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __basic_any_from(
    _Interface<_Super>& __self) noexcept -> __basic_any<_Super>&
{
    return static_cast<__basic_any<_Super>&>(__self);
}

template <template <class...> class _Interface, class _Super>
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __basic_any_from(
    _Interface<_Super> const& __self) noexcept -> __basic_any<_Super> const&
{
    return static_cast<__basic_any<_Super> const&>(__self);
}

template <template <class...> class _Interface>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __basic_any_from(
    _Interface<> const&) noexcept -> __basic_any<_Interface<>> const&
{
    CANN_ASC_STL_DETAIL_UNREACHABLE();
}

template <template <class...> class _Interface, class _Super>
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __basic_any_from(
    _Interface<_Super>* __self) noexcept -> __basic_any<_Super>*
{
    return static_cast<__basic_any<_Super>*>(__self);
}

template <template <class...> class _Interface, class _Super>
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __basic_any_from(
    _Interface<_Super> const* __self) noexcept -> __basic_any<_Super> const*
{
    return static_cast<__basic_any<_Super> const*>(__self);
}

template <template <class...> class _Interface>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __basic_any_from(
    _Interface<> const*) noexcept -> __basic_any<_Interface<>> const*
{
    CANN_ASC_STL_DETAIL_UNREACHABLE();
}

template <class _CvInterface>
using __cvref_basic_any_from_t = decltype(::asc::__basic_any_from(::asc::std::declval<_CvInterface>()));

template <class _CvInterface>
using __basic_any_from_t = ::asc::std::decay_t<__cvref_basic_any_from_t<_CvInterface>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_FROM_H
