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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_REF_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_REF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_base.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/conversions.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/iset.h>
#include <asc/__utility/__basic_any/rtti.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/typeid.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! \c __ireference<_Interface>
//!
//! For an interface `I`, `__ireference<I>` represents a reference to an object
//! that satisfies the given interface. When you dereference a `__basic_any<I*>`,
//! you get a `__basic_any<__ireference<I>>`. Also, `__basic_any<I&>` is implemented
//! in terms of `__basic_any<__ireference<I>>`.
//!
//! Note: a `__basic_any<__ireference<_Interface>> &&` is an rvalue reference,
//! whereas a `__basic_any<_Interface &> &&` is an lvalue reference.
template <class _Interface>
struct __ireference : ::asc::std::remove_const_t<_Interface> {
    static_assert(::asc::std::is_class_v<_Interface>, "expected a class type");
    static constexpr size_t __size_ = sizeof(void*);
    static constexpr size_t __align_ = alignof(void*);
    static constexpr bool __is_const_ref = ::asc::std::is_const_v<_Interface>;

    using interface = ::asc::std::remove_const_t<_Interface>;
};

//!
//! A base class for __basic_any<__ireference<_Interface>> that provides a
//! conversion to __basic_any<__ireference<_Interface const>>. Only used
//! when concepts are not available.
//!
template <class _Interface>
struct __basic_any_reference_conversion_base {
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API operator __basic_any<__ireference<_Interface const>>()
        const noexcept
    {
        return __basic_any<__ireference<_Interface const>>(
            static_cast<__basic_any<__ireference<_Interface>> const&>(*this));
    }
};

template <class _Interface>
struct __basic_any_reference_conversion_base<_Interface const> {};

CANN_ASC_STL_DETAIL_DIAG_PUSH
// "operator __basic_any<...> will not be called for implicit or explicit conversions"
// "operator __basic_any<...> will not be called for implicit or explicit conversions"

//!
//! \c __basic_any<__ireference<_Interface>>
//!
//! A `__basic_any<__ireference<_Interface>>` is a reference to an object that
//! satisfies the given interface. It is used as the result of dereferencing
//! a `__basic_any<_Interface*>` and as the implementation of
//! `__basic_any<_Interface&>`.
//!
//! `__basic_any<__ireference<_Interface>>` is neither copyable nor movable. It is
//! not an end-user type.
template <class _Interface>
struct __basic_any<__ireference<_Interface>> : __interface_of<__ireference<_Interface>>,
                                               __basic_any_reference_conversion_base<_Interface> {
    static_assert(::asc::std::is_class_v<_Interface>, "expecting a class type");
    using interface_type = ::asc::std::remove_const_t<_Interface>;
    static constexpr bool __is_const_ref = ::asc::std::is_const_v<_Interface>;

    __basic_any(__basic_any&&) = delete;
    __basic_any(__basic_any const&) = delete;

    auto operator=(__basic_any&&) -> __basic_any& = delete;
    auto operator=(__basic_any const&) -> __basic_any& = delete;

    //! \brief Returns a const reference to the type_info for the decayed type
    //! of the type-erased object.
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto type() const noexcept -> ::asc::std::__type_info_ref
    {
        return *__get_rtti()->__object_info_->__object_typeid_;
    }

    //! \brief Returns a const reference to the type_info for the decayed type
    //! of the type-erased object.
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto interface() const noexcept -> ::asc::std::__type_info_ref
    {
        return *__get_rtti()->__interface_typeid_;
    }

    //! \brief Returns a reference to a type_info object representing the type of
    //! the dynamic interface.
    //!
    //! The dynamic interface is the interface that was used to construct the
    //! object, which may be different from the current object's interface if
    //! there was a conversion.
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API static constexpr auto has_value() noexcept -> bool
    {
        return true;
    }

#if !defined(CANN_ASC_STL_DETAIL_DOXYGEN_INVOKED)  // Do not document
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API static constexpr auto __in_situ() noexcept -> bool
    {
        return true;
    }
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_REF_H

private:
    template <class>
    friend struct __basic_any;
    friend struct __basic_any_access;

    __basic_any() = default;

    //! \brief Constructs a \c __basic_any<__ireference<_Interface>> from an lvalue
    //! reference to a \c __basic_any<_Interface>.
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit __basic_any(
        ::asc::std::__maybe_const<__is_const_ref, __basic_any<interface_type>>& __other) noexcept
    {
        this->__set_ref(__other.__get_vptr(), __other.__get_optr());
    }

    //! \brief Constructs a \c __basic_any<__ireference<_Interface>> from a
    //! vtable pointer and an object pointer.
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API
    __basic_any(__vptr_for<interface_type> __vptr, ::asc::std::__maybe_const<__is_const_ref, void>* __optr) noexcept
        : __vptr_(__vptr), __optr_(__optr)
    {}

    //! \brief No-op.
    CANN_ASC_STL_DETAIL_NODEBUG_API void reset() noexcept
    {}

    //! \brief No-op.
    CANN_ASC_STL_DETAIL_NODEBUG_API void __release_() noexcept
    {}

    //! \brief Rebinds the reference with a vtable pointer and object pointer.
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __set_ref(
        __vptr_for<interface_type> __vptr, ::asc::std::__maybe_const<__is_const_ref, void>* __obj) noexcept
    {
        __vptr_ = __vptr;
        __optr_ = __vptr_ ? __obj : nullptr;
    }

    //! \brief Rebinds the reference with a vtable pointer for a different
    //! interface and object pointer. The vtable pointer is cast to the correct
    //! type. If the cast fails, the reference is set to null.
    template <class _VTable>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __set_ref(
        _VTable const* __other, ::asc::std::__maybe_const<__is_const_ref, void>* __obj) noexcept
    {
        using _OtherInterface = typename _VTable::interface;
        __vptr_ = __try_vptr_cast<_OtherInterface, interface_type>(__other);
        __optr_ = __vptr_ ? __obj : nullptr;
    }

    //! \brief Rebinds the reference with a pointer to an __iset vtable, which
    //! is cast to a pointer to the vtable for `_Interface`. If \c _Interface
    //! is a specialization `__iset_<Is...>`, the cast succeeds if the
    //! \c Is... is a subset of `Interfaces...`. Otherwise, the cast succeeds
    //! if the \c _Interface is a base of one of `Interfaces...`.
    template <class... _Interfaces>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __set_ref(
        __iset_vptr<_Interfaces...> __other, ::asc::std::__maybe_const<__is_const_ref, void>* __obj) noexcept
    {
        using _OtherInterface = __iset_<_Interfaces...>;
        __vptr_ = __try_vptr_cast<_OtherInterface, interface_type>(__other);
        __optr_ = __vptr_ ? __obj : nullptr;
    }

    template <class _SrcCvAny>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __convert_from(_SrcCvAny&& __from)
    {
        using __src_interface_t = typename ::asc::std::remove_reference_t<_SrcCvAny>::interface_type;
        if (!__from.has_value()) {
            __throw_bad_any_cast();
        }
        auto __to_vptr = __vptr_cast<__src_interface_t, interface_type>(__from.__get_vptr());
        __set_ref(__to_vptr, __from.__get_optr());
    }

    CANN_ASC_STL_DETAIL_NODEBUG_API auto __get_optr() const noexcept -> ::asc::std::__maybe_const<__is_const_ref, void>*
    {
        return __optr_;
    }

    CANN_ASC_STL_DETAIL_NODEBUG_API auto __get_vptr() const noexcept -> __vptr_for<interface_type>
    {
        return __vptr_;
    }

    CANN_ASC_STL_DETAIL_NODEBUG_API auto __get_rtti() const noexcept -> __rtti const*
    {
        return __vptr_->__query_interface(__iunknown());
    }

    __vptr_for<interface_type> __vptr_{};
    ::asc::std::__maybe_const<__is_const_ref, void>* __optr_{};
};

CANN_ASC_STL_DETAIL_DIAG_POP

//!
//! __basic_any<_Interface&>
//!
template <class _Interface>
struct __basic_any<_Interface&> : __basic_any<__ireference<_Interface>> {
    static_assert(::asc::std::is_class_v<_Interface>, "expecting a class type");
    using typename __basic_any<__ireference<_Interface>>::interface_type;
    using __basic_any<__ireference<_Interface>>::__is_const_ref;

    CANN_ASC_STL_DETAIL_NODEBUG_API __basic_any(__basic_any&& __other) noexcept
        : __basic_any(const_cast<__basic_any const&>(__other))
    {}

    CANN_ASC_STL_DETAIL_NODEBUG_API __basic_any(__basic_any& __other) noexcept
        : __basic_any(const_cast<__basic_any const&>(__other))
    {}

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any const& __other) noexcept
        : __basic_any<__ireference<_Interface>>()
    {
        this->__set_ref(__other.__get_vptr(), __other.__get_optr());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::remove_const_t<_Tp>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_basic_any<_Up>)CANN_ASC_STL_DETAIL_ACCL_AND(
        __is_const_ref || !::asc::std::is_const_v<_Tp>) CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Up, interface_type>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(_Tp& __obj) noexcept : __basic_any<__ireference<_Interface>>()
    {
        __vptr_for<interface_type> const __vptr = ::asc::__get_vtable_ptr_for<interface_type, _Up>();
        this->__set_ref(__vptr, &__obj);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_SrcInterface, _Interface&>)CANN_ASC_STL_DETAIL_ACCL_AND  //
        (!__is_value_v<_SrcInterface>) CANN_ASC_STL_DETAIL_ACCL_AND                                                   //
            __any_convertible_to<__basic_any<_SrcInterface>, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_SrcInterface>&& __src) noexcept
        : __basic_any<__ireference<_Interface>>()
    {
        this->__set_ref(__src.__get_vptr(), __src.__get_optr());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_SrcInterface, _Interface&>)CANN_ASC_STL_DETAIL_ACCL_AND  //
            __any_convertible_to<__basic_any<_SrcInterface>&, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_SrcInterface>& __src) noexcept
        : __basic_any<__ireference<_Interface>>()
    {
        this->__set_ref(__src.__get_vptr(), __src.__get_optr());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_SrcInterface, _Interface&>)CANN_ASC_STL_DETAIL_ACCL_AND  //
            __any_convertible_to<__basic_any<_SrcInterface> const&, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_SrcInterface> const& __src) noexcept
        : __basic_any<__ireference<_Interface>>()
    {
        this->__set_ref(__src.__get_vptr(), __src.__get_optr());
    }

    auto operator=(__basic_any&&) -> __basic_any& = delete;
    auto operator=(__basic_any const&) -> __basic_any& = delete;

    CANN_ASC_STL_DETAIL_NODEBUG_API auto move() & noexcept -> __basic_any<__ireference<_Interface>>&&
    {
        return ::asc::std::move(*this);  // NOLINT(build/include_what_you_use)
    }

private:
    template <class>
    friend struct __basic_any;
    friend struct __basic_any_access;

    __basic_any() = default;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_REF_H
