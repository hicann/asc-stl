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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_PTR_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_PTR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_base.h>
#include <asc/__utility/__basic_any/basic_any_from.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/basic_any_ref.h>
#include <asc/__utility/__basic_any/conversions.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/rtti.h>
#include <asc/__utility/__basic_any/virtual_tables.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__utility/typeid.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __basic_any<_Interface*>
//!
template <class _Interface>
struct __basic_any<_Interface*> {
    using interface_type = ::asc::std::remove_const_t<_Interface>;
    static constexpr bool __is_const_ptr = ::asc::std::is_const_v<_Interface>;

    //!
    //! Constructors
    //!
    __basic_any() = default;

    CANN_ASC_STL_DETAIL_NODEBUG_API __basic_any(::asc::std::nullptr_t)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::remove_const_t<_Tp>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!__is_basic_any<_Tp>)CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Up, interface_type>
            CANN_ASC_STL_DETAIL_ACCL_AND(__is_const_ptr || !::asc::std::is_const_v<_Tp>))
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(_Tp* __obj) noexcept
    {
        operator=(__obj);
    }

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any const& __other) noexcept
    {
        __convert_from(__other);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_OtherInterface, _Interface>)
            CANN_ASC_STL_DETAIL_ACCL_AND __any_convertible_to<__basic_any<_OtherInterface*>, __basic_any<_Interface*>>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface*> const& __other) noexcept
    {
        __convert_from(__other);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_OtherInterface>&, __basic_any<_Interface&>>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface>* __other) noexcept
    {
        __convert_from(__other);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __any_convertible_to<__basic_any<_OtherInterface> const&, __basic_any<_Interface&>>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface> const* __other) noexcept
    {
        __convert_from(__other);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(template <class...> class _OtherInterface, class _Super)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_interface<_OtherInterface<_Super>>
            CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::derived_from<__basic_any<_Super>, _OtherInterface<_Super>>
                CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::same_as<__normalized_interface_of<__basic_any<_Super>*>,
                    _Interface*>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit __basic_any(_OtherInterface<_Super>* __self) noexcept
    {
        __convert_from(__basic_any_from(__self));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(template <class...> class _OtherInterface, class _Super)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_interface<_OtherInterface<_Super>>
            CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::derived_from<__basic_any<_Super>, _OtherInterface<_Super>>
                CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::same_as<__normalized_interface_of<__basic_any<_Super> const*>,
                    _Interface*>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit __basic_any(_OtherInterface<_Super> const* __self) noexcept
    {
        __convert_from(__basic_any_from(__self));
    }

    //!
    //! Assignment operators
    //!
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(::asc::std::nullptr_t) noexcept -> __basic_any&
    {
        reset();
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::remove_const_t<_Tp>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_basic_any<_Tp>)CANN_ASC_STL_DETAIL_ACCL_AND  //
            __satisfies<_Up, interface_type>
                CANN_ASC_STL_DETAIL_ACCL_AND  //
        (__is_const_ptr || !::asc::std::is_const_v<_Tp>))
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(_Tp* __obj) noexcept -> __basic_any&
    {
        __vptr_for<interface_type> __vptr = ::asc::__get_vtable_ptr_for<interface_type, _Up>();
        __ref_.__set_ref(__obj ? __vptr : nullptr, __obj);
        return *this;
    }

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any const& __other) noexcept -> __basic_any&
    {
        __convert_from(__other);
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_OtherInterface, _Interface>)
            CANN_ASC_STL_DETAIL_ACCL_AND __any_convertible_to<__basic_any<_OtherInterface*>, __basic_any<_Interface*>>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(
        __basic_any<_OtherInterface*> const& __other) noexcept -> __basic_any&
    {
        __convert_from(__other);
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_OtherInterface>&, __basic_any<_Interface&>>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any<_OtherInterface>* __other) noexcept -> __basic_any&
    {
        __convert_from(__other);
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __any_convertible_to<__basic_any<_OtherInterface> const&, __basic_any<_Interface&>>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(
        __basic_any<_OtherInterface> const* __other) noexcept -> __basic_any&
    {
        __convert_from(__other);
        return *this;
    }

    //!
    //! emplace
    //!
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(
        class _Tp, class _Up = ::asc::std::remove_pointer_t<_Tp>, class _Vp = ::asc::std::remove_const_t<_Up>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __satisfies<_Vp, _Interface> CANN_ASC_STL_DETAIL_ACCL_AND(__is_const_ptr || !::asc::std::is_const_v<_Up>))
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto emplace(
        ::asc::std::type_identity_t<_Up>* __obj) noexcept -> ::asc::std::__maybe_const<__is_const_ptr, _Vp>*&
    {
        __vptr_for<interface_type> __vptr = ::asc::__get_vtable_ptr_for<interface_type, _Vp>();
        __ref_.__set_ref(__obj ? __vptr : nullptr, __obj);
        return *static_cast<::asc::std::__maybe_const<__is_const_ptr, _Vp>**>(static_cast<void*>(&__ref_.__optr_));
    }

#if !defined(CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON)
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator==(__basic_any const& __other) const noexcept -> bool
    {
        using __void_ptr_t = ::asc::std::__maybe_const<__is_const_ptr, void>* const*;
        return *static_cast<__void_ptr_t>(__get_optr()) == *static_cast<__void_ptr_t>(__other.__get_optr());
    }
#else   // ^^^ !CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON ^^^ / vvv CANN_ASC_STL_DETAIL_NO_THREE_WAY_COMPARISON vvv
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API friend auto operator==(
        __basic_any const& __lhs, __basic_any const& __rhs) noexcept -> bool
    {
        using __void_ptr_t = ::asc::std::__maybe_const<__is_const_ptr, void>* const*;
        return *static_cast<__void_ptr_t>(__lhs.__get_optr()) == *static_cast<__void_ptr_t>(__rhs.__get_optr());
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API friend auto operator!=(
        __basic_any const& __lhs, __basic_any const& __rhs) noexcept -> bool
    {
        return !(__lhs == __rhs);
    }
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_PTR_H

    using __any_ref_t = ::asc::std::__maybe_const<__is_const_ptr, __basic_any<__ireference<_Interface>>>;

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto operator->() const noexcept -> __any_ref_t*
    {
        return &__ref_;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto operator*() const noexcept -> __any_ref_t&
    {
        return __ref_;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto type() const noexcept -> ::asc::std::__type_info_ref
    {
        return __ref_.__vptr_ != nullptr ? (__is_const_ptr ? *__get_rtti()->__object_info_->__const_pointer_typeid_ :
                                                             *__get_rtti()->__object_info_->__pointer_typeid_) :
                                           ::asc::std::__typeid<void>();
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto interface() const noexcept -> ::asc::std::__type_info_ref
    {
        return __ref_.__vptr_ != nullptr ? *__get_rtti()->__interface_typeid_ : ::asc::std::__typeid<interface_type>();
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto has_value() const noexcept -> bool
    {
        return __ref_.__vptr_ != nullptr;
    }

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void reset() noexcept
    {
        __vptr_for<interface_type> __vptr = nullptr;
        __ref_.__set_ref(__vptr, nullptr);
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit operator bool() const noexcept
    {
        return __ref_.__vptr_ != nullptr;
    }

#if !defined(CANN_ASC_STL_DETAIL_DOXYGEN_INVOKED)  // Do not document
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API static constexpr auto __in_situ() noexcept -> bool
    {
        return true;
    }
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_PTR_H

private:
    template <class>
    friend struct __basic_any;
    friend struct __basic_any_access;

    template <class _SrcCvAny>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __convert_from(_SrcCvAny* __other) noexcept
    {
        __other ? __ref_.__set_ref(__other->__get_vptr(), __other->__get_optr()) : reset();
    }

    template <class _OtherInterface>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __convert_from(__basic_any<_OtherInterface*> const& __other) noexcept
    {
        using __other_interface_t = ::asc::std::remove_const_t<_OtherInterface>;
        auto __to_vptr = __try_vptr_cast<__other_interface_t, interface_type>(__other.__get_vptr());
        auto __to_optr = __to_vptr ? *__other.__get_optr() : nullptr;
        __ref_.__set_ref(__to_vptr, __to_optr);
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_optr() noexcept
        -> ::asc::std::__maybe_const<__is_const_ptr, void>**
    {
        return &__ref_.__optr_;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_optr() const noexcept
        -> ::asc::std::__maybe_const<__is_const_ptr, void>* const*
    {
        return &__ref_.__optr_;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_vptr() const noexcept -> __vptr_for<interface_type>
    {
        return __ref_.__vptr_;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_rtti() const noexcept -> __rtti const*
    {
        return __ref_.__vptr_ ? __ref_.__vptr_->__query_interface(__iunknown()) : nullptr;
    }

    mutable __basic_any<__ireference<_Interface>> __ref_;
};

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(template <class...> class _Interface, class _Super)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_interface<_Interface<_Super>>)
__basic_any(_Interface<_Super>*)  //
    ->__basic_any<__normalized_interface_of<__basic_any<_Super>*>>;

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(template <class...> class _Interface, class _Super)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_interface<_Interface<_Super>>)
__basic_any(_Interface<_Super> const*)  //
    ->__basic_any<__normalized_interface_of<__basic_any<_Super> const*>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_PTR_H
