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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VALUE_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VALUE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_base.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/basic_any_ref.h>
#include <asc/__utility/__basic_any/conversions.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/rtti.h>
#include <asc/__utility/__basic_any/semiregular.h>
#include <asc/__utility/__basic_any/storage.h>
#include <asc/__utility/__basic_any/virtual_tables.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__new/device_new.h>
#include <asc/std/__new/launder.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/__utility/typeid.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __basic_any
//!
template <class _Interface>
struct __basic_any : __basic_any_base<_Interface> {
private:
    static_assert(::asc::std::is_class_v<_Interface>,
        "__basic_any requires an interface type, or a pointer or reference to an interface "
        "type.");
    static_assert(!::asc::std::is_const_v<_Interface>, "__basic_any does not support const-qualified interfaces.");

    static constexpr bool __movable = __extension_of<_Interface, __imovable<>>;
    static constexpr bool __copyable = __extension_of<_Interface, __icopyable<>>;

    using __basic_any_base<_Interface>::__size_;
    using __basic_any_base<_Interface>::__align_;
    using __basic_any_base<_Interface>::__vptr_;
    using __basic_any_base<_Interface>::__buffer_;

public:
    using interface_type = _Interface;

    //! @brief Constructs an empty `__basic_any` object.
    //! @post `has_value() == false`
    __basic_any() = default;

    //! @brief Constructs a `__basic_any` object that contains a copy of `__value`.
    //! @pre `__value` must be move constructible. `_Tp` must satisfy the
    //! requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::decay_t<_Tp>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_basic_any<_Up>)
        // The following constraint seems to trip up a lot of compilers, so leave it out.
        // CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::constructible_from<_Up, _Tp>
        CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Up, _Interface>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(_Tp&& __value) noexcept(
        __is_small<_Up, __movable>(__size_, __align_) && ::asc::std::is_nothrow_constructible_v<_Up, _Tp>)
    {
        __emplace<_Up>(static_cast<_Tp&&>(__value));
    }

    //! @brief Constructs a `__basic_any` object that contains a new object of type `_Tp`
    //! constructed as `_Tp(__args...)`, or as `_Tp{__args...}` if `_Tp(__args...)` is
    //! ill-formed.
    //! @pre `_Tp` must satisfy the requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::decay_t<_Tp>, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __initializable_from<_Up, _Args...> CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Up, _Interface>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit __basic_any(
        ::asc::std::in_place_type_t<_Tp>, _Args&&... __args) noexcept(__is_small<_Up, __movable>(__size_, __align_) &&
        __nothrow_initializable_from<_Up, _Args...>)
    {
        __emplace<_Up>(static_cast<_Args&&>(__args)...);
    }

    //! @brief Constructs a `__basic_any` object that contains a new object of type `_Tp`
    //! constructed as `_Tp(__il, __args...)`, or as `_Tp{__il, __args...}` if
    //! `_Tp(__il, __args...)` is ill-formed.
    //! @pre `_Tp` must satisfy the requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up, class _Vp = ::asc::std::decay_t<_Tp>, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __initializable_from<_Vp, ::asc::std::initializer_list<_Up>&, _Args...> CANN_ASC_STL_DETAIL_ACCL_AND
            __satisfies<_Up, _Interface>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit __basic_any(::asc::std::in_place_type_t<_Tp>,
        ::asc::std::initializer_list<_Up> __il,
        _Args&&... __args) noexcept(__is_small<_Vp, __movable>(__size_, __align_) &&
        __nothrow_initializable_from<_Vp, ::asc::std::initializer_list<_Up>&, _Args...>)
    {
        __emplace<_Vp>(__il, static_cast<_Args&&>(__args)...);
    }

    //! @brief Constructs a `__basic_any` object that contains a new object of type `_Tp`
    //! constructed as `_Tp(__fn(__args...))`.
    //! @pre `_Tp` must satisfy the requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::decay_t<_Tp>, class _Fn, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __emplaceable_from<_Up, _Fn, _Args...> CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Up, _Interface>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API explicit __basic_any(::asc::in_place_from_type_t<_Tp>, _Fn&& __fn,
        _Args&&... __args) noexcept(__is_small<_Up, __movable>(__size_, __align_) &&
        __nothrow_emplaceable_from<_Up, _Fn, _Args...>)
    {
        __emplace_from<_Up>(static_cast<_Fn&&>(__fn), static_cast<_Args&&>(__args)...);
    }

    // We use base classes to implement movability and copyability. All we need here is to
    // accept the default implementations.
    __basic_any(__basic_any&& __other) = default;
    __basic_any(__basic_any const& __other) = default;

    //! @brief Converting constructor that move constructs from a compatible
    //! `__basic_any` object.
    //! @pre Let `I` be the decayed type of `_OtherInterface`. `I` must extend
    //! `_Interface`. If `_OtherInterface` is a reference type, then `I` must
    //! extend `__icopyable<>`. Otherwise, `I` must extend `__imovable<>`.
    //! @post `__other.has_value() == false` and `has_value()` is `true` if and
    //! only if `__other.has_value()` was `true`.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_OtherInterface&, _Interface&>)
            CANN_ASC_STL_DETAIL_ACCL_AND __any_convertible_to<__basic_any<_OtherInterface>, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface>&& __other)
    {
        __convert_from(::asc::std::move(__other));
    }

    //! @brief Converting constructor that copy constructs from a compatible
    //! `__basic_any` object.
    //! @pre The decayed type of `_OtherInterface` must extend `_Interface` and
    //! `__icopyable<>`.
    //! @post `has_value() == __other.has_value()`.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_OtherInterface&, _Interface&>)
            CANN_ASC_STL_DETAIL_ACCL_AND __any_convertible_to<__basic_any<_OtherInterface> const&, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface> const& __other)
    {
        __convert_from(__other);
    }

    //! @brief Non-template converting constructors from the corresponding
    //! reference type `__basic_any<_Interface&>`. These enable implicit
    //! conversion from proxy types (e.g. Cython's __Pyx_FakeReference)
    //! that wrap a `__basic_any<_Interface&>` and provide
    //! `operator __basic_any<_Interface&>&()`, since non-template parameters
    //! participate in implicit conversion sequences.
    //! @pre `_Interface` must extend `__icopyable<>` (converting a ref to
    //! a value requires copying the referenced object).
    template <bool _Copyable = __copyable, ::asc::std::enable_if_t<_Copyable, int> = 0>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_Interface&> const& __other)
    {
        __convert_from(__other);
    }

    template <bool _Copyable = __copyable, ::asc::std::enable_if_t<_Copyable, int> = 0>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_Interface&>&& __other)
    {
        __convert_from(__other);
    }

#if 0  // legacy-compiler workaround not applicable
  // Older versions of clang and gcc need help disambiguating between
  // __basic_any<__ireference<I>> and __basic_any<I&>.
  CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
  CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_OtherInterface&>, __basic_any>)
  CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface&>&& __other)
  {
    __convert_from(__other);
  }

  CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
  CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_OtherInterface&>, __basic_any>)
  CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any(__basic_any<_OtherInterface&> const& __other)
  {
    __convert_from(__other);
  }
#endif

    //! @brief Destroys the contained value, if any.
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API ~__basic_any()
    {
        reset();
    }

    // We use base classes to implement movability and copyability. All we need here is to
    // accept the default implementations.
    auto operator=(__basic_any&& __other) -> __basic_any& = default;
    auto operator=(__basic_any const& __other) -> __basic_any& = default;

#if 1
    //! @brief Converting move assignment operator from a compatible `__basic_any`
    //! object.
    //!
    //! Equivalent to:
    //!
    //! @code{.cpp}
    //! __basic_any(asc::std::move(__other)).swap(*this);
    //! return *this;
    //! @endcode
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_OtherInterface, _Interface>)
            CANN_ASC_STL_DETAIL_ACCL_AND __any_convertible_to<__basic_any<_OtherInterface>, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any<_OtherInterface>&& __other) -> __basic_any&
    {
        return __assign_from(::asc::std::move(__other));
    }

    //! @brief Converting copy assignment operator from a compatible `__basic_any`
    //! object.
    //!
    //! Equivalent to:
    //!
    //! @code{.cpp}
    //! __basic_any(__other).swap(*this);
    //! return *this;
    //! @endcode
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!::asc::std::same_as<_OtherInterface, _Interface>)
            CANN_ASC_STL_DETAIL_ACCL_AND __any_convertible_to<__basic_any<_OtherInterface> const&, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any<_OtherInterface> const& __other) -> __basic_any&
    {
        return __assign_from(__other);
    }
#else
    // Some host compiler concepts implementations substitute too early here and hard-
    // error, so SFINAE is used to work around it.
    template <class _OtherInterface,
        ::asc::std::enable_if_t<!::asc::std::same_as<_OtherInterface, _Interface>, int> = 0,
        ::asc::std::enable_if_t<__any_convertible_to<__basic_any<_OtherInterface>, __basic_any>, int> = 0>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any<_OtherInterface>&& __other) -> __basic_any&
    {
        return __assign_from(::asc::std::move(__other));
    }

    template <class _OtherInterface,
        ::asc::std::enable_if_t<!::asc::std::same_as<_OtherInterface, _Interface>, int> = 0,
        ::asc::std::enable_if_t<__any_convertible_to<__basic_any<_OtherInterface> const&, __basic_any>, int> = 0>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any<_OtherInterface> const& __other) -> __basic_any&
    {
        return __assign_from(__other);
    }
#endif

#if 0  // legacy-compiler workaround not applicable
  // Older versions of clang and gcc need help disambiguating between
  // __basic_any<__ireference<I>> and __basic_any<I&>.
  CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherInterface)
  CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_OtherInterface&>, __basic_any>)
  CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any<_OtherInterface&> __other) -> __basic_any&
  {
    return __assign_from(__other);
  }
#endif

    //! @brief Implicitly convert to a `__basic_any` non-const reference type:
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API operator __basic_any<__ireference<_Interface>>() & noexcept
    {
        return __basic_any<__ireference<_Interface>>(*this);
    }

    //! @brief Implicitly convert to a `__basic_any` const reference type:
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API operator __basic_any<__ireference<_Interface const>>()
        const& noexcept
    {
        return __basic_any<__ireference<_Interface const>>(*this);
    }

    //! @brief Exchanges the values of two `__basic_any` objects.
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void swap(__basic_any& __other) noexcept
    {
        //! if both objects refer to heap-allocated object, we can just
        //! swap the pointers. otherwise, do it the slow(er) way.
        if (!__in_situ() && !__other.__in_situ()) {
            ::asc::std::swap(__vptr_, __other.__vptr_);
            __swap_ptr_ptr(__buffer_, __other.__buffer_);
        }

        __basic_any __tmp;
        __tmp.__convert_from(::asc::std::move(*this));
        (*this).__convert_from(::asc::std::move(__other));
        __other.__convert_from(::asc::std::move(__tmp));  // NOLINT(build/include_what_you_use)
    }

    //! @brief Exchanges the values of two `__basic_any` objects.
    friend CANN_ASC_STL_DETAIL_NODEBUG_API void swap(
        __basic_any& __lhs, __basic_any& __rhs) noexcept  // NOLINT(build/include_what_you_use)
    {
        __lhs.swap(__rhs);
    }

    //! @brief Emplaces a new object of type `_Tp` constructed as `_Tp(__args...)`, or as
    //! `_Tp{__args...}` if `_Tp(__args...)` is ill-formed.
    //! @pre `_Tp` must satisfy the requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::decay_t<_Tp>, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__initializable_from<_Up, _Args...>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto emplace(_Args&&... __args) noexcept(
        __is_small<_Up, __movable>(__size_, __align_) && __nothrow_initializable_from<_Up, _Args...>) -> _Up&
    {
        reset();
        return __emplace<_Up>(static_cast<_Args&&>(__args)...);
    }

    //! @brief Emplaces a new object of type `_Tp` constructed as `_Tp(__il, __args...)`, or
    //! as `_Tp{__il, __args...}` if `_Tp(__il, __args...)` is ill-formed.
    //! @pre `_Tp` must satisfy the requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up, class _Vp = ::asc::std::decay_t<_Tp>, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__initializable_from<_Vp, ::asc::std::initializer_list<_Up>&, _Args...>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto emplace(::asc::std::initializer_list<_Up> __il,
        _Args&&... __args) noexcept(__is_small<_Vp, __movable>(__size_, __align_) &&
        __nothrow_initializable_from<_Vp, ::asc::std::initializer_list<_Up>&, _Args...>) -> _Vp&
    {
        reset();
        return __emplace<_Vp>(__il, static_cast<_Args&&>(__args)...);
    }

    //! @brief Emplaces a new object of type `_Tp` constructed as
    //! `_Tp{__args...}`.
    //! @pre `_Tp` must satisfy the requirements of `_Interface`.
    //! @post `has_value() == true`
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up = ::asc::std::decay_t<_Tp>, class _Fn, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__emplaceable_from<_Up, _Fn, _Args...>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto emplace_from(_Fn&& __fn, _Args&&... __args) noexcept(
        __is_small<_Up, __movable>(__size_, __align_) && __nothrow_emplaceable_from<_Up, _Fn, _Args...>) -> _Up&
    {
        reset();
        return __emplace_from<_Up>(static_cast<_Fn&&>(__fn), static_cast<_Args&&>(__args)...);
    }

    //! @brief Tests whether the `__basic_any` object contains a value.
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto has_value() const noexcept -> bool
    {
        return __get_vptr() != nullptr;
    }

    //! @brief Resets the `__basic_any` object to an empty state.
    //! @post `has_value() == false`
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void reset() noexcept
    {
        if (auto __vptr = __get_vptr()) {
            CANN_ASC_STL_DETAIL_ASSERT(__vptr->__query_interface(__iunknown())->__cookie_ == 0xDEADBEEF,
                "query_interface returned a bad pointer to the __iunknown vtable");
            __vptr->__query_interface(__iunknown())->__dtor_(__buffer_, __in_situ());
            __release_();
        }
    }

    //! @brief Returns a reference to a type_info object representing the type of
    //! the contained object.
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto type() const noexcept -> ::asc::std::__type_info_ref
    {
        if (auto __vptr = __get_vptr()) {
            CANN_ASC_STL_DETAIL_ASSERT(__vptr->__query_interface(__iunknown())->__cookie_ == 0xDEADBEEF,
                "query_interface returned a bad pointer to the __iunknown vtable");
            return *__vptr->__query_interface(__iunknown())->__object_info_->__object_typeid_;
        }
        return ::asc::std::__typeid<void>();
    }

    //! @brief Returns a reference to a type_info object representing the type of
    //! the dynamic interface.
    //!
    //! The dynamic interface is the interface that was used to construct the
    //! object, which may be different from the current object's interface if
    //! there was a conversion.
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto interface() const noexcept -> ::asc::std::__type_info_ref
    {
        if (auto __vptr = __get_vptr()) {
            CANN_ASC_STL_DETAIL_ASSERT(__vptr->__query_interface(__iunknown())->__cookie_ == 0xDEADBEEF,
                "query_interface returned a bad pointer to the __iunknown vtable");
            return *__vptr->__query_interface(__iunknown())->__interface_typeid_;
        }
        return ::asc::std::__typeid<_Interface>();
    }

#if 1  // Do not document
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __in_situ() const noexcept -> bool
    {
        return __vptr_.__flag();
    }
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VALUE_H

private:
    template <class>
    friend struct __basic_any;
    friend struct __basic_any_access;
    template <class, int>
    friend struct __basic_any_base;

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __release_()
    {
        __vptr_for<_Interface> __vptr = nullptr;
        __vptr_.__set(__vptr, false);
    }
    template <class _Tp, class... _Args>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __emplace(_Args&&... __args) noexcept(
        __is_small<_Tp, __movable>(__size_, __align_) && __nothrow_initializable_from<_Tp, _Args...>) -> _Tp&
    {
        using __pointer_t = _Tp*;
        if constexpr (__is_small<_Tp, __movable>(__size_, __align_)) {
            // in-place construction
            if constexpr (::asc::std::constructible_from<_Tp, _Args...>) {
                // Prefer direct non-list initialization if possible.
                ::new (__buffer_) _Tp(static_cast<_Args&&>(__args)...);
            } else {
                // Otherwise, fall back to direct list initialization.
                ::new (__buffer_) _Tp{static_cast<_Args&&>(__args)...};
            }
        } else {
            // heap allocation
            if constexpr (::asc::std::constructible_from<_Tp, _Args...>) {
                // Prefer direct non-list initialization if possible.
                ::new (__buffer_) __pointer_t{new _Tp(static_cast<_Args&&>(__args)...)};
            } else {
                // Otherwise, fall back to direct list initialization.
                ::new (__buffer_) __pointer_t{new _Tp{static_cast<_Args&&>(__args)...}};
            }
        }

        __vptr_for<_Interface> __vptr = ::asc::__get_vtable_ptr_for<_Interface, _Tp>();
        __vptr_.__set(__vptr, __is_small<_Tp, __movable>(__size_, __align_));
        return *::asc::std::launder(static_cast<_Tp*>(__get_optr()));
    }
    template <class _Tp, class _Fn, class... _Args>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __emplace_from(_Fn&& __fn, _Args&&... __args) noexcept(
        __is_small<_Tp, __movable>(__size_, __align_) && __nothrow_emplaceable_from<_Tp, _Fn, _Args...>) -> _Tp&
    {
        using __pointer_t = _Tp*;
        if constexpr (__is_small<_Tp, __movable>(__size_, __align_)) {
            // in-place construction
            ::new (__buffer_) _Tp(static_cast<_Fn&&>(__fn)(static_cast<_Args&&>(__args)...));
        } else {
            // heap allocation
            ::new (__buffer_) __pointer_t{new _Tp(static_cast<_Fn&&>(__fn)(static_cast<_Args&&>(__args)...))};
        }

        __vptr_for<_Interface> __vptr = ::asc::__get_vtable_ptr_for<_Interface, _Tp>();
        __vptr_.__set(__vptr, __is_small<_Tp, __movable>(__size_, __align_));
        return *::asc::std::launder(static_cast<_Tp*>(__get_optr()));
    }

    // this overload handles moving from __basic_any<_SrcInterface> and
    // __basic_any<__ireference<_SrcInterface>> (but not
    // __basic_any<__ireference<_SrcInterface const>>).
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface>, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __convert_from(__basic_any<_SrcInterface>&& __from) noexcept(
        ::asc::std::same_as<_SrcInterface, _Interface>)
    {
        CANN_ASC_STL_DETAIL_ASSERT(!has_value(), "forgot to clear the destination object first");
        using __src_interface_t = __remove_ireference_t<_SrcInterface>;
        // if the source is an lvalue reference, we need to copy from it.
        if constexpr (__is_lvalue_reference_v<_SrcInterface>) {
            __convert_from(__from);  // will copy from the source
        } else if (auto __to_vptr = __vptr_cast<__src_interface_t, _Interface>(__from.__get_vptr())) {
            if (!__from.__in_situ()) {
                using __void_ptr_t = void*;
                ::new (__buffer_) __void_ptr_t(__from.__get_optr());
                __vptr_.__set(__to_vptr, false);
                __from.__release_();
            } else if constexpr (::asc::std::same_as<_SrcInterface, _Interface>) {
                __from.__move_to(__buffer_);
                __vptr_.__set(__from.__get_vptr(), true);
                __from.reset();
            } else {
                bool const __small = __from.__move_to(__buffer_, __size_, __align_);
                __vptr_.__set(__to_vptr, __small);
                __from.reset();
            }
        }
    }

    // this overload handles copying from __basic_any<_Interface>,
    // __basic_any<__ireference<_Interface>>, and __basic_any<_Interface&>.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcInterface)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<__basic_any<_SrcInterface> const&, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __convert_from(__basic_any<_SrcInterface> const& __from)
    {
        CANN_ASC_STL_DETAIL_ASSERT(!has_value(), "forgot to clear the destination object first");
        using __src_interface_t = __remove_ireference_t<::asc::std::remove_reference_t<_SrcInterface>>;
        if (auto __to_vptr = __vptr_cast<__src_interface_t, _Interface>(__from.__get_vptr())) {
            bool const __small = __from.__copy_to(__buffer_, __size_, __align_);
            __vptr_.__set(__to_vptr, __small);
        }
    }

    // Assignment from a compatible __basic_any object handled here:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _SrcCvAny)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_castable_to<_SrcCvAny, __basic_any>)
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __assign_from(_SrcCvAny&& __src) -> __basic_any&
    {
        if (!__ptr_eq(this, &__src)) {
            reset();
            __convert_from(static_cast<_SrcCvAny&&>(__src));
        }
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_vptr() const noexcept -> __vptr_for<_Interface>
    {
        return __vptr_.__get();
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_optr() noexcept -> void*
    {
        void* __pv = __buffer_;
        return __in_situ() ? __pv : *static_cast<void**>(__pv);
    }

    CANN_ASC_STL_DETAIL_DIAG_PUSH
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4702)  // warning C4702: unreachable code (srsly where, msvc?)
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_optr() const noexcept -> void const*
    {
        void const* __pv = __buffer_;
        return __in_situ() ? __pv : *static_cast<void const* const*>(__pv);
    }
    CANN_ASC_STL_DETAIL_DIAG_POP

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_rtti() const noexcept -> __rtti const*
    {
        return __get_vptr()->__query_interface(__iunknown());
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_VALUE_H
