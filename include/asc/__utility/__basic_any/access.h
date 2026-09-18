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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ACCESS_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__type_traits/is_specialization_of.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/conversions.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_cvref.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __basic_any_access
//!
struct __basic_any_access {
    template <class _Interface>
    CANN_ASC_STL_DETAIL_NODEBUG_API static auto __make() noexcept -> __basic_any<_Interface>
    {
        return __basic_any<_Interface>{};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcCvAny, class _DstInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<_SrcCvAny, __basic_any<_DstInterface>>)
    CANN_ASC_STL_DETAIL_NODEBUG_API static auto __cast_to(_SrcCvAny&& __from,
        __basic_any<_DstInterface>& __to) noexcept(noexcept(__to.__convert_from(static_cast<_SrcCvAny&&>(__from))))
        -> void
    {
        static_assert(__is_specialization_of_v<::asc::std::remove_cvref_t<_SrcCvAny>, __basic_any>);
        __to.__convert_from(static_cast<_SrcCvAny&&>(__from));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcCvAny, class _DstInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<_SrcCvAny*, __basic_any<_DstInterface>>)
    CANN_ASC_STL_DETAIL_NODEBUG_API static auto __cast_to(_SrcCvAny* __from, __basic_any<_DstInterface>& __to) noexcept(
        noexcept(__to.__convert_from(__from))) -> void
    {
        static_assert(__is_specialization_of_v<::asc::std::remove_const_t<_SrcCvAny>, __basic_any>);
        __to.__convert_from(__from);
    }

    template <class _Interface>
    CANN_ASC_STL_DETAIL_NODEBUG_API static auto __get_vptr(
        __basic_any<_Interface> const& __self) noexcept -> __vptr_for<_Interface>
    {
        return __self.__get_vptr();
    }

    template <class _Interface>
    CANN_ASC_STL_DETAIL_NODEBUG_API static auto __get_optr(__basic_any<_Interface>& __self) noexcept -> void*
    {
        return __self.__get_optr();
    }

    template <class _Interface>
    CANN_ASC_STL_DETAIL_NODEBUG_API static auto __get_optr(
        __basic_any<_Interface> const& __self) noexcept -> void const*
    {
        return __self.__get_optr();
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ACCESS_H
