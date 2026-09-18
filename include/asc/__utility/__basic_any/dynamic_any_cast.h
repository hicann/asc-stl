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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_DYNAMIC_ANY_CAST_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_DYNAMIC_ANY_CAST_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/access.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/conversions.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//! \brief Casts one __basic_any reference type to another __basic_any type using
//! runtime information to determine the validity of the conversion.
//!
//! \throws __bad_any_cast when \c __src cannot be dynamically cast to a
//! \c __basic_any<_DstInterface>.
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcInterface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface>, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __dynamic_any_cast(
    __basic_any<_SrcInterface>&& __src) -> __basic_any<_DstInterface>
{
    auto __dst = __basic_any_access::__make<_DstInterface>();
    __basic_any_access::__cast_to(::asc::std::move(__src), __dst);  // NOLINT(build/include_what_you_use)
    return __dst;
}

//! \overload
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcInterface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface>&, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __dynamic_any_cast(
    __basic_any<_SrcInterface>& __src) -> __basic_any<_DstInterface>
{
    auto __dst = __basic_any_access::__make<_DstInterface>();
    __basic_any_access::__cast_to(__src, __dst);
    return __dst;
}

//! \overload
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcInterface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface> const&, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __dynamic_any_cast(
    __basic_any<_SrcInterface> const& __src) -> __basic_any<_DstInterface>
{
    auto __dst = __basic_any_access::__make<_DstInterface>();
    __basic_any_access::__cast_to(__src, __dst);
    return __dst;
}

//! \brief Casts a `__basic_any<_SrcInterface>*` into a `__basic_any<_DstInterface>`
//! using runtime information to determine the validity of the conversion.
//!
//! \pre \c _DstInterface must be a pointer type.
//!
//! \returns \c nullptr when \c __src cannot be dynamically cast to a
//! \c __basic_any<_DstInterface>.
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcInterface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface>*, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __dynamic_any_cast(
    __basic_any<_SrcInterface>* __src) -> __basic_any<_DstInterface>
{
    static_assert(::asc::std::is_pointer_v<_DstInterface>,
        "when __dynamic_any_cast-ing from a pointer to a __basic_any, the destination type must be a pointer to an "
        "interface type.");
    auto __dst = __basic_any_access::__make<_DstInterface>();
    __basic_any_access::__cast_to(__src, __dst);
    return __dst;
}

//! \overload
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcInterface)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface> const*, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __dynamic_any_cast(
    __basic_any<_SrcInterface> const* __src) -> __basic_any<_DstInterface>
{
    static_assert(::asc::std::is_pointer_v<_DstInterface>,
        "when __dynamic_any_cast-ing from a pointer to a __basic_any, the destination type must be a pointer to an "
        "interface type.");
    auto __dst = __basic_any_access::__make<_DstInterface>();
    __basic_any_access::__cast_to(__src, __dst);
    return __dst;
}

#if 0  // GCC<11 workaround not applicable
// Older versions of GCC have trouble deducing __basic_any<T&> from a type derived from
// it, because __basic_any<T&> itself inherits from __basic_any<__ireference<T>>. GCC
// cannot choose between the two base classes when deducing from a derived class.
CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcAny)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<typename _SrcAny::__basic_any, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_TRIVIAL_API auto __dynamic_any_cast(_SrcAny&& __src) -> __basic_any<_DstInterface>
{
  return ::asc::__dynamic_any_cast<_DstInterface>(static_cast<typename _SrcAny::__basic_any&&>(__src));
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcAny)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<typename _SrcAny::__basic_any&, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_TRIVIAL_API auto __dynamic_any_cast(_SrcAny& __src) -> __basic_any<_DstInterface>
{
  return ::asc::__dynamic_any_cast<_DstInterface>(static_cast<typename _SrcAny::__basic_any&>(__src));
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcAny)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<typename _SrcAny::__basic_any const&, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_TRIVIAL_API auto __dynamic_any_cast(_SrcAny const& __src)
    -> __basic_any<_DstInterface>
{
  return ::asc::__dynamic_any_cast<_DstInterface>(static_cast<typename _SrcAny::__basic_any const&>(__src));
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcAny)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<typename _SrcAny::__basic_any*, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_TRIVIAL_API auto __dynamic_any_cast(_SrcAny* __src) -> __basic_any<_DstInterface>
{
  return ::asc::__dynamic_any_cast<_DstInterface>(static_cast<typename _SrcAny::__basic_any*>(__src));
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _DstInterface, class _SrcAny)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<typename _SrcAny::__basic_any const*, __basic_any<_DstInterface>>)
[[nodiscard]] CANN_ASC_STL_DETAIL_TRIVIAL_API auto __dynamic_any_cast(_SrcAny const* __src)
    -> __basic_any<_DstInterface>
{
  return ::asc::__dynamic_any_cast<_DstInterface>(static_cast<typename _SrcAny::__basic_any const*>(__src));
}
#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_DYNAMIC_ANY_CAST_H
