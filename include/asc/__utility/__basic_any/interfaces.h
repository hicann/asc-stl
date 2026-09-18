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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_INTERFACES_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_INTERFACES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/overrides.h>
#include <asc/__utility/inherit.h>
#include <asc/std/__algorithm/find.h>
#include <asc/std/__algorithm/max.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/type_set.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! Interface type traits
//!
template <class _Interface>
struct __remove_ireference<_Interface const> {
    using type = _Interface;
};

template <class _Interface>
struct __remove_ireference<__ireference<_Interface>> {
    using type = _Interface;
};

template <class _Interface>
struct __remove_ireference<__ireference<_Interface const>> {
    using type = _Interface;
};

template <class _Interface>
inline constexpr bool __is_value_v = ::asc::std::is_class_v<_Interface>;

template <class _Interface>
inline constexpr bool __is_value_v<__ireference<_Interface>> = false;

template <class _Interface>
inline constexpr bool __is_lvalue_reference_v = false;

template <class _Interface>
inline constexpr bool __is_lvalue_reference_v<__ireference<_Interface const>> = true;

template <class _Interface>
inline constexpr bool __is_lvalue_reference_v<_Interface&> = true;

//!
//! __bases_of: get the list of base interface for an interface, including itself
//!             and __iunknown.
//!
template <class _Interface, class _Fn>
using __bases_of =                  //
    ::asc::std::__type_call<        //
        ::asc::std::__type_concat<  //
            ::asc::std::__type_list<__iunknown, ::asc::std::remove_const_t<_Interface>>,
            typename _Interface::template __ibases<__make_type_list>>,
        _Fn>;

//!
//! interface subsumption
//!
template <class _Interface1, class _Interface2>
inline constexpr bool __subsumes = false;

template <class _Interface>
inline constexpr bool __subsumes<_Interface, _Interface> = true;

template <class... _Set>
inline constexpr bool __subsumes<__iset_<_Set...>, __iset_<_Set...>> = true;

template <class... _Subset, class... _Superset>
inline constexpr bool __subsumes<__iset_<_Subset...>, __iset_<_Superset...>> =
    ::asc::std::__type_set_contains_v<::asc::std::__make_type_set<_Superset...>, _Subset...>;

//!
//! __extension_of: Checks if one interface is an extension of another.
//!
//! An interface \c A is considered an extension of another \c B if \c B
//! can be found by recursively searching the base interfaces of \c A.
//! `__iset<As...>` is an extension of `__iset<Bs...>` if `Bs...` is a subset
//! of `As...`.
//!
//! \note An interface is considered an extension of itself.
//!
template <class _Base>
struct __has_base_fn {
    template <class... _Interfaces>
    using __call = ::asc::std::bool_constant<::asc::std::__is_included_in_v<_Base, _Interfaces...>>;
};

template <class... _Bases>
struct __has_base_fn<__iset_<_Bases...>> {
    using __bases_set = __iset_<_Bases...>;

    template <class... _Interfaces>
    using __call = ::asc::std::bool_constant<(__subsumes<__bases_set, _Interfaces> || ...)>;
};

template <class _Derived, class _Base, class = void>
inline constexpr bool __extension_of_v = false;

template <class _Derived, class _Base>
inline constexpr bool __extension_of_v<_Derived, _Base,
    ::asc::std::enable_if_t<::asc::std::is_class_v<_Derived>&& ::asc::std::is_class_v<_Base>>> =
    __bases_of<_Derived, __has_base_fn<::asc::std::remove_const_t<_Base>>>::value;

template <class _Derived, class _Base>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __extension_of = __extension_of_v<_Derived, _Base>;

//!
//! interface
//!
template <template <class...> class _Interface, class... _Bases, size_t Size, size_t Align>
struct __basic_interface<_Interface, __extends<_Bases...>, Size, Align> {
    static constexpr size_t size = (::asc::std::max)({Size, _Bases::size...});
    static constexpr size_t align = (::asc::std::max)({Align, _Bases::align...});

    template <class... _Super>
    using __rebind = _Interface<_Super...>;

    template <class _Fn>
    using __ibases = ::asc::std::__type_call<::asc::std::__type_concat<__bases_of<_Bases, __make_type_list>...>, _Fn>;

    template <class _Tp>
    using overrides = __overrides_for<_Tp>;
};

//!
//! __is_interface
//!
template <template <class...> class _Interface, class _Extends, size_t _Size, size_t _Align>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_interface_test(
    __basic_interface<_Interface, _Extends, _Size, _Align> const&) -> void;

// clang-format off
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __is_interface =
  CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp), _Tp& __value)
  (
    (::asc::__is_interface_test(__value))
  );  // NOLINT(whitespace/parens)
// clang-format on

//!
//! __unique_interfaces
//!
//! Given an interface, return a list that contains the interface and all its
//! bases, but with duplicates removed.
//!
template <class _Interface, class _Fn = __make_type_list>
using __unique_interfaces = ::asc::std::__type_apply<_Fn,
    ::asc::std::__as_type_list<__bases_of<_Interface, ::asc::std::__type_quote<::asc::std::__make_type_set>>>>;

//!
//! __index_of_base: find the index of an interface in a list of unique interfaces
//!
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr auto __find_index(
    ::asc::std::initializer_list<bool> __il) -> size_t
{
    auto __it = ::asc::std::find(__il.begin(), __il.end(), true);
    return static_cast<size_t>(__it - __il.begin());
}

template <class _Interface>
struct __find_index_of_base {
    template <class... _Interfaces>
    static constexpr size_t __index = __find_index({__subsumes<_Interface, _Interfaces>...});

    template <class... _Interfaces>
    using __call = ::asc::std::integral_constant<size_t, __index<_Interfaces...>>;
};

template <class _Interface, class _Super>
using __index_of_base = ::asc::std::__type_apply<__find_index_of_base<_Interface>, __unique_interfaces<_Super>>;

template <class...>
struct __iempty : __basic_interface<__iempty> {};

template <class _Interface>
using __vptr_for = typename __overrides_for_t<_Interface>::__vptr_t;

//!
//! interface satisfaction
//!
template <class _Tp>
struct __satisfaction_fn {
    template <class _Interface>
    using __does_not_satisfy = ::asc::std::_Not<::asc::std::_IsValidExpansion<__overrides_for_t, _Interface, _Tp>>;

    // Try to find an unsatisfied interface. If we find one, we return it (it's at
    // the front of the list returned from __type_find_if). If we don't find one
    // (that is, if the returned list is empty), we return __iempty<>.
    template <class... _Interfaces>
    using __call = ::asc::std::__type_front<  // take the front of the list
        ::asc::std::__type_push_back<         // add __iempty<> to the end of the list
            ::asc::std::__type_find_if<       // find the first unsatisfied interface if any, returns a list
                ::asc::std::__type_list<_Interfaces...>, ::asc::std::__type_quote1<__does_not_satisfy>>,
            __iempty<>>>;
};

template <class _Interface, class _Tp, class = void>
struct __unsatisfied_interface {};

template <class _Interface, class _Tp>
struct __unsatisfied_interface<_Interface, _Tp, ::asc::std::enable_if_t<::asc::std::is_class_v<_Interface>>> {
    using type = __unique_interfaces<_Interface, __satisfaction_fn<_Tp>>;
};

template <class _Interface, class _Tp>
struct __unsatisfied_interface<_Interface*, _Tp*> : __unsatisfied_interface<_Interface, _Tp> {};

template <class _Interface, class _Tp>
struct __unsatisfied_interface<_Interface const*, _Tp const*> : __unsatisfied_interface<_Interface, _Tp> {};

template <class _Interface, class _Tp>
struct __unsatisfied_interface<_Interface&, _Tp> : __unsatisfied_interface<_Interface, _Tp> {};

template <class _Tp, class _Interface>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __has_overrides =
    ::asc::std::_IsValidExpansion<__overrides_for_t, _Interface, _Tp>::value;

//! The \c __satisfies concept checks if a type \c _Tp satisfies an interface
//! \c _Interface. It does this by trying to instantiate
//! `__overrides_for_t<_X, _Tp>` for all \c _X, where \c _X is \c _Interface or
//! one of its bases. If any of the \c __overrides_for_t instantiations are ill-
//! formed, then \c _Tp does not satisfy \c _Interface.
//!
//! \c __satisfies is implemented by searching through the list of interfaces for
//! one that \c _Tp does not satisfy. If such an interface is found, the concept
//! check fails in such a way as to hopefully tell the user which interface is
//! not satisfied and why.
template <class _Tp, class _Interface,
    class UnsatisfiedInterface = ::asc::std::__type<__unsatisfied_interface<_Interface, _Tp>>>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __satisfies = __has_overrides<_Tp, UnsatisfiedInterface>;

//!
//! __interface_of
//!
template <class _Super>
struct __make_interface_fn {
    static_assert(::asc::std::is_class_v<_Super>, "expected a class type");
    template <class... _Interfaces>
    using __call = ::asc::__inherit<__rebind_interface<_Interfaces, _Super>...>;
};

// Given an interface `_I<>`, let `_Bs<>...` be the list of types consisting
// of all of `_I<>`'s unique bases. Then `__interface_of<_I<>>` is the
// type `__inherit<_I<_I<>>, _Bs<_I<>>...>`. That is, it transforms the
// unspecialized interfaces into ones specialized for `_I<>` and then
// makes a type that inherits publicly from all of them.
template <class _Interface>
using __interface_of = __unique_interfaces<_Interface, __make_interface_fn<_Interface>>;

//!
//! interface_cast
//!
//! given a `__basic_any<X<>>` object `o`, `interface_cast<Y>(o)` return a
//! reference to the (empty) sub-object of type `Y<X<>>`, from which
//! `__basic_any<X<>>` inherits, where `Y<>` is an interface that `X<>` extends.
//!
template <class _Interface>
struct __interface_cast_fn;

template <template <class...> class _Interface>
struct __interface_cast_fn<_Interface<>> {
    template <class _Super>
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto operator()(
        _Interface<_Super>&& __self) const noexcept -> _Interface<_Super>&&
    {
        return ::asc::std::move(__self);
    }

    template <class _Super>
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto operator()(
        _Interface<_Super>& __self) const noexcept -> _Interface<_Super>&
    {
        return __self;
    }

    template <class _Super>
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto operator()(
        _Interface<_Super> const& __self) noexcept -> _Interface<_Super> const&
    {
        return __self;
    }
};

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(template <class...> class _Interface, class Object)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_interface<_Interface<>>
        CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::__is_callable_v<__interface_cast_fn<_Interface<>>, Object>)
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __interface_cast(Object&& __obj) noexcept -> decltype(auto)
{
    return __interface_cast_fn<_Interface<>>{}(::asc::std::forward<Object>(__obj));
}

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Interface, class Object)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_interface<_Interface>
        CANN_ASC_STL_DETAIL_ACCL_AND ::asc::std::__is_callable_v<__interface_cast_fn<_Interface>, Object>)
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __interface_cast(Object&& __obj) noexcept -> decltype(auto)
{
    return __interface_cast_fn<_Interface>{}(::asc::std::forward<Object>(__obj));  // NOLINT(build/include_what_you_use)
}
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_INTERFACES_H
