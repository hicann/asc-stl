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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_SEMIREGULAR_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_SEMIREGULAR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/access.h>
#include <asc/__utility/__basic_any/basic_any_base.h>
#include <asc/__utility/__basic_any/basic_any_from.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/conversions.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/storage.h>
#include <asc/__utility/__basic_any/virtcall.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__new/device_new.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/typeid.h>
#include <asc/std/__utility/unreachable.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! semi-regular overrides
//!

//! @note We use `::asc::std::enable_if_t` here instead of requires-clauses
//! to avoid ABI differences between C++17 and C++20 modes.
template <class _Tp>
CANN_ASC_STL_API auto __move_fn(_Tp& __src, void* __dst) noexcept -> void
{
    static_assert(::asc::std::movable<_Tp>, "type must be movable");
    ::new (__dst) _Tp(static_cast<_Tp&&>(__src));
}
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API auto __try_move_fn(_Tp& __src, void* __dst, size_t __size, size_t __align) -> bool
{
    static_assert(::asc::std::movable<_Tp>, "type must be movable");
    if (::asc::__is_small<_Tp>(__size, __align)) {
        ::new (__dst) _Tp(static_cast<_Tp&&>(__src));
        return true;
    } else {
        ::new (__dst)::asc::std::type_identity_t<_Tp*>(new _Tp(static_cast<_Tp&&>(__src)));
        return false;
    }
}
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API auto __copy_fn(_Tp const& __src, void* __dst, size_t __size, size_t __align) -> bool
{
    static_assert(::asc::std::copyable<_Tp>, "type must be copyable");
    if (::asc::__is_small<_Tp>(__size, __align)) {
        ::new (__dst) _Tp(__src);
        return true;
    } else {
        ::new (__dst)::asc::std::type_identity_t<_Tp*>(new _Tp(__src));
        return false;
    }
}
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API auto __equal_fn(_Tp const& __self, ::asc::std::__type_info_ref __type,
    void const* __other) -> ::asc::std::enable_if_t<::asc::std::equality_comparable<_Tp>, bool>
{
    if (::asc::std::__typeid<_Tp>() == __type) {
        return __self == *static_cast<_Tp const*>(__other);
    }
    return false;
}
template <class _From, class _To>
[[nodiscard]] CANN_ASC_STL_API auto __conversion_fn(
    ::asc::std::type_identity_t<_From> __self) -> ::asc::std::enable_if_t<::asc::std::convertible_to<_From, _To>, _To>
{
    return static_cast<_To>(static_cast<_From&&>(__self));
}

//!
//! semi-regular interfaces
//!
template <class...>
struct __imovable : __basic_interface<__imovable> {
    template <class _Tp>
    using overrides = __overrides_for<_Tp, &::asc::__try_move_fn<_Tp>, &::asc::__move_fn<_Tp>>;

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __move_to(void* __pv) noexcept -> void
    {
        return ::asc::__virtcall<&::asc::__move_fn<__imovable>>(this, __pv);
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __move_to(void* __pv, size_t __size, size_t __align) -> bool
    {
        return ::asc::__virtcall<&::asc::__try_move_fn<__imovable>>(this, __pv, __size, __align);
    }
};

template <class...>
struct __icopyable : __basic_interface<__icopyable, __extends<__imovable<>>> {
    template <class _Tp>
    using overrides = __overrides_for<_Tp, &::asc::__copy_fn<_Tp>>;

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __copy_to(
        void* __pv, size_t __size, size_t __align) const -> bool
    {
        return ::asc::__virtcall<&::asc::__copy_fn<__icopyable>>(this, __pv, __size, __align);
    }
};

template <class _Object>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __non_polymorphic = (!__is_basic_any<_Object>) && (!__is_interface<_Object>);

template <class... _Super>
struct __iequality_comparable;

struct iequality_comparable_base : __basic_interface<__iequality_comparable> {
    // These overloads are only necessary so that __iequality_comparable<> itself
    // satisfies the std::equality_comparable constraint that is used by the
    // `__iequality_comparable<>::overloads` alias template below.
    [[noreturn]] friend CANN_ASC_STL_DETAIL_NODEBUG_API auto operator==(
        __iequality_comparable<> const&, __iequality_comparable<> const&) noexcept -> bool
    {
        ::asc::std::unreachable();
    }

    [[noreturn]] friend CANN_ASC_STL_DETAIL_NODEBUG_API auto operator!=(
        __iequality_comparable<> const&, __iequality_comparable<> const&) noexcept -> bool
    {
        ::asc::std::unreachable();
    }

    // These are the overloads that get used when testing two `__basic_any` objects
    // for equality.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _ILeft, class _IRight)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_ILeft> const&, __basic_any<_IRight> const&> ||
        __any_convertible_to<__basic_any<_IRight> const&, __basic_any<_ILeft> const&>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API friend auto operator==(
        __iequality_comparable<_ILeft> const& __lhs, __iequality_comparable<_IRight> const& __rhs) noexcept -> bool
    {
        auto const& __other = ::asc::__basic_any_from(__rhs);
        constexpr auto __eq = &::asc::__equal_fn<__iequality_comparable<_ILeft>>;
        return ::asc::__virtcall<__eq>(&__lhs, __other.type(), __basic_any_access::__get_optr(__other));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _ILeft, class _IRight)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__any_convertible_to<__basic_any<_ILeft> const&, __basic_any<_IRight> const&> ||
        __any_convertible_to<__basic_any<_IRight> const&, __basic_any<_ILeft> const&>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API friend auto operator!=(
        __iequality_comparable<_ILeft> const& __lhs, __iequality_comparable<_IRight> const& __rhs) noexcept -> bool
    {
        return !(__lhs == __rhs);
    }

    // These are the overloads that get used when testing a `__basic_any` object
    // against a non-type-erased object.
    //
    // Q: Why require that the __basic_any wrapper is not convertible to _Object?
    //
    // A: If there is a user-defined conversion from the __basic_any type to _Object
    // such that we can use _Object's symmetric equality comparison operator, that
    // should be preferred. _Object may be another kind of wrapper object, in which
    // case using the address of the **wrapper** object for the comparison (as
    // opposed to the address of the wrapped object) is probably wrong.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(
        class _Interface, class _Object, class _Self = __basic_any_from_t<__iequality_comparable<_Interface>>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__non_polymorphic<_Object> CANN_ASC_STL_DETAIL_ACCL_AND(
        !::asc::std::convertible_to<_Self, _Object>) CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Object, _Interface>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API friend auto operator==(
        __iequality_comparable<_Interface> const& __lhs, _Object const& __rhs) -> bool
    {
        constexpr auto __eq = &::asc::__equal_fn<__iequality_comparable<_Interface>>;
        return ::asc::__virtcall<__eq>(&__lhs, ::asc::std::__typeid<_Object>(), ::asc::std::addressof(__rhs));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(
        class _Interface, class _Object, class _Self = __basic_any_from_t<__iequality_comparable<_Interface>>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__non_polymorphic<_Object> CANN_ASC_STL_DETAIL_ACCL_AND(
        !::asc::std::convertible_to<_Self, _Object>) CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Object, _Interface>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API friend auto operator==(
        _Object const& __lhs, __iequality_comparable<_Interface> const& __rhs) noexcept -> bool
    {
        constexpr auto __eq = &::asc::__equal_fn<__iequality_comparable<_Interface>>;
        return ::asc::__virtcall<__eq>(&__rhs, ::asc::std::__typeid<_Object>(), ::asc::std::addressof(__lhs));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(
        class _Interface, class _Object, class _Self = __basic_any_from_t<__iequality_comparable<_Interface>>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__non_polymorphic<_Object> CANN_ASC_STL_DETAIL_ACCL_AND(
        !::asc::std::convertible_to<_Self, _Object>) CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Object, _Interface>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API friend auto operator!=(
        __iequality_comparable<_Interface> const& __lhs, _Object const& __rhs) noexcept -> bool
    {
        return !(__lhs == __rhs);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(
        class _Interface, class _Object, class _Self = __basic_any_from_t<__iequality_comparable<_Interface>>)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__non_polymorphic<_Object> CANN_ASC_STL_DETAIL_ACCL_AND(
        !::asc::std::convertible_to<_Self, _Object>) CANN_ASC_STL_DETAIL_ACCL_AND __satisfies<_Object, _Interface>)
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API friend auto operator!=(
        _Object const& __lhs, __iequality_comparable<_Interface> const& __rhs) noexcept -> bool
    {
        return !(__lhs == __rhs);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(::asc::std::equality_comparable<_Tp>)
    using overrides = __overrides_for<_Tp, &::asc::__equal_fn<_Tp>>;
};

template <class... _Super>
struct __iequality_comparable : iequality_comparable_base {};

struct __self;  // a nice placeholder type

template <class _CvSelf, class _To>
struct __iconvertible_to_ {
    static_assert(::asc::std::is_same_v<::asc::std::decay_t<_CvSelf>, __self>,
        "The first template parameter to __iconvertible_to must be the placeholder type "
        "__self, possibly with cv- and/or ref-qualifiers");
};

template <class _To>
struct __iconvertible_to_<__self&&, _To> {
    static_assert(::asc::std::__always_false_v<_To>, "rvalue-qualified conversion operations are not yet supported");
};

template <class _To>
struct __iconvertible_to_<__self, _To> {
    template <class...>
    struct __interface_ : __basic_interface<__interface_> {
        [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API operator _To()
        {
            return ::asc::__virtcall<::asc::__conversion_fn<__interface_, _To>>(this);
        }

        template <class _From>
        using overrides = __overrides_for<_From, &::asc::__conversion_fn<_From, _To>>;
    };
};

template <class _To>
struct __iconvertible_to_<__self&, _To> {
    template <class...>
    struct __interface_ : __basic_interface<__interface_> {
        [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API operator _To() &
        {
            return ::asc::__virtcall<&::asc::__conversion_fn<__interface_&, _To>>(this);
        }

        template <class _From>
        using overrides = __overrides_for<_From, &::asc::__conversion_fn<_From&, _To>>;
    };
};

template <class _To>
struct __iconvertible_to_<__self const&, _To> {
    template <class...>
    struct __interface_ : __basic_interface<__interface_> {
        [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API operator _To() const&
        {
            return ::asc::__virtcall<&::asc::__conversion_fn<__interface_ const&, _To>>(this);
        }

        template <class _From>
        using overrides = __overrides_for<_From, &::asc::__conversion_fn<_From const&, _To>>;
    };
};

template <class _From, class _To>
using __iconvertible_to = typename __iconvertible_to_<_From, _To>::template __interface_<>;
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_SEMIREGULAR_H
