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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_VIRTUAL_TABLES_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_VIRTUAL_TABLES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/rtti.h>
#include <asc/__utility/__basic_any/virtual_functions.h>
#include <asc/__utility/__basic_any/virtual_ptrs.h>
#include <asc/std/__exception/terminate.h>
#include <asc/std/__utility/typeid.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Interface>
using __vtable_for = typename __overrides_for_t<_Interface>::__vtable;

//!
//! __basic_vtable
//!
template <class _Interface, auto... _Mbrs>
struct __basic_vtable : __rtti_base, __virtual_fn<_Mbrs>... {
    using interface = _Interface;
    static constexpr size_t __cbases = ::asc::std::__type_list_size<__unique_interfaces<interface>>::value;

    template <class _VPtr, class _Tp, class... _OtherMembers, class... _Interfaces>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __basic_vtable(
        _VPtr __vptr, __overrides_list<_Tp, _OtherMembers...>, __tag<_Interfaces...>) noexcept
        : __rtti_base{__vtable_kind::__normal, __cbases, ::asc::std::__typeid<__basic_vtable>()},
          __virtual_fn<_Mbrs>{__override_tag<_Tp, _OtherMembers::value>{}}...,
          __vptr_map_{__base_vptr{__vptr->__query_interface(_Interfaces())}...}
    {}

    template <class _Tp, class _VPtr>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __basic_vtable(__tag<_Tp>, _VPtr __vptr) noexcept
        : __basic_vtable{__vptr, __overrides_for_t<interface, _Tp>(),
              __unique_interfaces<interface, ::asc::std::__type_quote<__tag>>()}
    {}

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __query_interface(
        interface) const noexcept -> __vptr_for<interface>
    {
        return this;
    }

    template <class... _Others>
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __query_interface(
        __iset_<_Others...>) const noexcept -> __vptr_for<__iset_<_Others...>>
    {
        using __remainder =
            ::asc::std::__type_list_size<::asc::std::__type_find<__unique_interfaces<interface>, __iset_<_Others...>>>;
        constexpr size_t __index = __cbases - __remainder::value;
        if constexpr (__index < __cbases) {
            // `_Interface` extends __iset_<_Others...> exactly. We can return an actual
            // vtable pointer.
            return static_cast<__vtable_for<__iset_<_Others...>> const*>(__vptr_map_[__index]);
        } else {
            // Otherwise, we have to return a subset vtable pointer, which does
            // dynamic interface lookup.
            return static_cast<__vptr_for<__iset_<_Others...>>>(__query_interface(__iunknown()));
        }
    }

    template <class _Other>
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __query_interface(
        _Other) const noexcept -> __vptr_for<_Other>
    {
        constexpr size_t __index = __index_of_base<_Other, interface>::value;
        static_assert(__index < __cbases);
        return static_cast<__vptr_for<_Other>>(__vptr_map_[__index]);
    }

    __base_vptr __vptr_map_[__cbases];
};

//!
//! __vtable implementation details
//!

template <class... _Interfaces>
struct __vtable_tuple : __rtti_ex<sizeof...(_Interfaces)>, __vtable_for<_Interfaces>... {
    static_assert((::asc::std::is_class_v<_Interfaces> && ...), "expected class types");

    template <class _Tp, class _Super>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __vtable_tuple(__tag<_Tp, _Super> __type) noexcept
        : __rtti_ex<sizeof...(_Interfaces)>{__type, __tag<_Interfaces...>(), this}
#if 0  // MSVC workaround not applicable
      // workaround for MSVC bug
      , __overrides_for_t<_Interfaces>::__vtable{__tag<_Tp>(), this}...
#else  // ^^^ MSVC ^^^ / vvv !MSVC vvv
          ,
          __vtable_for<_Interfaces>{__tag<_Tp>(), this}...
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_VIRTUAL_TABLES_H
    {
        static_assert(::asc::std::is_class_v<_Super>, "expected a class type");
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Interface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(::asc::std::__is_included_in_v<_Interface, _Interfaces...>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr auto __query_interface(
        _Interface) const noexcept -> __vptr_for<_Interface>
    {
        return static_cast<__vptr_for<_Interface>>(this);
    }
};

// The vtable type for type `_Interface` is a `__vtable_tuple` of `_Interface`
// and all of its base interfaces.
template <class _Interface>
using __vtable = __unique_interfaces<_Interface, ::asc::std::__type_quote<__vtable_tuple>>;

// __vtable_holder<_Interface, _Tp> holds one __vtable<_Interface> instance with
// _Tp's overrides. CCE forbids referencing an uninstantiated variable template
// from inside an aicore function, so the global variable template becomes a
// class-template static data member plus an address-of member.
template <class _Interface, class _Tp>
struct __vtable_holder {
    static constexpr __vtable<_Interface> __value{__tag<_Tp, _Interface>()};
};

template <class _Ifc, class _Up>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __vtable<_Ifc> const* __get_vtable_ptr_for() noexcept
{
    return &__vtable_holder<_Ifc, _Up>::__value;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_VIRTUAL_TABLES_H
