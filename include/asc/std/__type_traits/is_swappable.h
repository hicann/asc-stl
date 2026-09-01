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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SWAPPABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SWAPPABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_complete.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/nat.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __detect_hidden_friend_swap {

template <class _Tp>
CANN_ASC_STL_HOST_DEVICE void swap(_Tp&, _Tp&);

struct __hidden_friend_swap_found {};

template <class _Tp>
auto __swap(_Tp& __lhs, _Tp& __rhs) -> decltype(swap(__lhs, __rhs));

auto __swap(...) -> __hidden_friend_swap_found;

template <class _Tp>
struct __has_hidden_friend_swap
    : is_same<decltype(__detect_hidden_friend_swap::__swap(::asc::std::declval<_Tp&>(), ::asc::std::declval<_Tp&>())),
          void> {};

}  // namespace __detect_hidden_friend_swap

namespace __detect_adl_swap {

template <class _Tp>
void swap(_Tp&, _Tp&) = delete;

struct __no_adl_swap_found {};

template <class _Tp>
auto __swap(_Tp& __lhs, _Tp& __rhs) -> decltype(swap(__lhs, __rhs));

auto __swap(...) -> __no_adl_swap_found;

template <class _Tp>
struct __has_no_adl_swap
    : is_same<decltype(__detect_adl_swap::__swap(::asc::std::declval<_Tp&>(), ::asc::std::declval<_Tp&>())),
          __no_adl_swap_found> {};

template <class _Tp, size_t _Np>
struct __has_no_adl_swap_array : is_same<decltype(__detect_adl_swap::__swap(
                                             ::asc::std::declval<_Tp (&)[_Np]>(), ::asc::std::declval<_Tp (&)[_Np]>())),
                                     __no_adl_swap_found> {};

template <class _Tp>
struct __can_define_swap : _Or<__has_no_adl_swap<_Tp>, __detect_hidden_friend_swap::__has_hidden_friend_swap<_Tp>> {};

}  // namespace __detect_adl_swap

template <class _Tp>
struct __is_swappable;

template <class _Tp>
struct __is_nothrow_swappable;

template <class _Tp>
using __swap_result_t = enable_if_t<__detect_adl_swap::__can_define_swap<_Tp>::value && is_move_constructible_v<_Tp> &&
    is_move_assignable_v<_Tp>>;

template <class _Tp>
CANN_ASC_STL_API constexpr __swap_result_t<_Tp> swap(_Tp& __x, type_identity_t<_Tp>& __y) noexcept(
    is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_assignable_v<_Tp>);

template <class _Tp, size_t _Np>
CANN_ASC_STL_API constexpr enable_if_t<__detect_adl_swap::__has_no_adl_swap_array<_Tp, _Np>::value &&
    __is_swappable<_Tp>::value>
    swap(_Tp (&__a)[_Np], _Tp (&__b)[_Np]) noexcept(__is_nothrow_swappable<_Tp>::value);

namespace __detail {

template <class _Tp, class _Up = _Tp, bool _NotVoid = !is_void_v<_Tp> && !is_void_v<_Up>>
struct __swappable_with {
    template <class _LHS, class _RHS>
    static decltype(swap(::asc::std::declval<_LHS>(), ::asc::std::declval<_RHS>())) __test_swap(int);

    template <class, class>
    static __nat __test_swap(long);

    using __swap1 = decltype((__test_swap<_Tp, _Up>(0)));
    using __swap2 = decltype((__test_swap<_Up, _Tp>(0)));

    static const bool value = _IsNotSame<__swap1, __nat>::value && _IsNotSame<__swap2, __nat>::value;
};

template <class _Tp, class _Up>
struct __swappable_with<_Tp, _Up, false> : false_type {};

template <class _Tp, class _Up = _Tp, bool _Swappable = __swappable_with<_Tp, _Up>::value>
struct __nothrow_swappable_with {
    static const bool value = noexcept(swap(::asc::std::declval<_Tp>(), ::asc::std::declval<_Up>())) &&
        noexcept(swap(::asc::std::declval<_Up>(), ::asc::std::declval<_Tp>()));  // NOLINT(build/include_what_you_use)
};

template <class _Tp, class _Up>
struct __nothrow_swappable_with<_Tp, _Up, false> : false_type {};

}  // namespace __detail

template <class _Tp>
struct __is_swappable : public integral_constant<bool, __detail::__swappable_with<_Tp&>::value> {};

template <class _Tp>
struct __is_nothrow_swappable : public integral_constant<bool, __detail::__nothrow_swappable_with<_Tp&>::value> {};

template <class _Tp, class _Up>
inline constexpr bool is_swappable_with_v = __detail::__swappable_with<_Tp, _Up>::value;

template <class _Tp, bool = __asc_is_referenceable<_Tp>::value>
inline constexpr bool is_swappable_v = false;

template <class _Tp>
inline constexpr bool is_swappable_v<_Tp, true> =
    is_swappable_with_v<add_lvalue_reference_t<_Tp>, add_lvalue_reference_t<_Tp>>;

template <class _Tp, class _Up>
inline constexpr bool is_nothrow_swappable_with_v = __detail::__nothrow_swappable_with<_Tp, _Up>::value;

template <class _Tp, bool = __asc_is_referenceable<_Tp>::value>
inline constexpr bool is_nothrow_swappable_v = false;

template <class _Tp>
inline constexpr bool is_nothrow_swappable_v<_Tp, true> =
    is_nothrow_swappable_with_v<add_lvalue_reference_t<_Tp>, add_lvalue_reference_t<_Tp>>;

template <class _Tp, class _Up>
struct is_swappable_with : public bool_constant<is_swappable_with_v<_Tp, _Up>> {};

template <class _Tp>
struct is_swappable : public bool_constant<is_swappable_v<_Tp>> {};

template <class _Tp, class _Up>
struct is_nothrow_swappable_with : public bool_constant<is_nothrow_swappable_with_v<_Tp, _Up>> {};

template <class _Tp>
struct is_nothrow_swappable : public bool_constant<is_nothrow_swappable_v<_Tp>> {};

template <class _Tp, bool = __is_complete_v<_Tp>>
inline constexpr bool __is_complete_and_nothrow_swappable_v = false;

template <class _Tp>
inline constexpr bool __is_complete_and_nothrow_swappable_v<_Tp, true> = is_nothrow_swappable_v<_Tp>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SWAPPABLE_H
