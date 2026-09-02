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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__TYPE_TRAITS_IS_SWAPPABLE_H
#define CANN_ASC_STL_ASC_STDDETAIL__TYPE_TRAITS_IS_SWAPPABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __is_swappable;
template <class T>
struct __is_nothrow_swappable;
template <class T>
using __swap_result_t = enable_if_t<is_move_constructible_v<T> && is_move_assignable_v<T>>;
template <class T>
CANN_ASC_STL_API constexpr __swap_result_t<T> swap(T& left, type_identity_t<T>& right) noexcept(
    is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>);
template <class T, size_t N>
CANN_ASC_STL_API constexpr enable_if_t<__is_swappable<T>::value> swap(T (&left)[N], T (&right)[N]) noexcept(
    __is_nothrow_swappable<T>::value);
namespace __detail {
template <class T, class U, bool = !is_void_v<T> && !is_void_v<U>>
struct __swappable_with {
    template <class Left, class Right>
    CANN_ASC_STL_API static auto __test_swap(
        int) -> decltype(swap(::asc::std::declval<Left>(), ::asc::std::declval<Right>()));
    template <class, class>
    CANN_ASC_STL_API static __nat __test_swap(long);

    using __swap1 = decltype(__test_swap<T, U>(0));
    using __swap2 = decltype(__test_swap<U, T>(0));
    static constexpr bool value = !is_same_v<__swap1, __nat> && !is_same_v<__swap2, __nat>;
};
template <class T, class U>
struct __swappable_with<T, U, false> : false_type {};
template <class T, class U, bool = __swappable_with<T, U>::value>
struct __nothrow_swappable_with : false_type {};
template <class T, class U>
struct __nothrow_swappable_with<T, U, true>
    : bool_constant<noexcept(swap(::asc::std::declval<T>(), ::asc::std::declval<U>())) &&
          noexcept(swap(::asc::std::declval<U>(), ::asc::std::declval<T>()))> {  // NOLINT(build/include_what_you_use)
};
}  // namespace __detail
template <class T>
struct __is_swappable : bool_constant<__detail::__swappable_with<T&, T&>::value> {};
template <class T>
struct __is_nothrow_swappable : __detail::__nothrow_swappable_with<T&, T&> {};
template <class T, class U>
inline constexpr bool is_swappable_with_v = __detail::__swappable_with<T, U>::value;
template <class T, bool = __is_referenceable<T>::value>
inline constexpr bool is_swappable_v = false;
template <class T>
inline constexpr bool is_swappable_v<T, true> =
    is_swappable_with_v<add_lvalue_reference_t<T>, add_lvalue_reference_t<T>>;
template <class T, class U>
inline constexpr bool is_nothrow_swappable_with_v = __detail::__nothrow_swappable_with<T, U>::value;
template <class T, bool = __is_referenceable<T>::value>
inline constexpr bool is_nothrow_swappable_v = false;
template <class T>
inline constexpr bool is_nothrow_swappable_v<T, true> =
    is_nothrow_swappable_with_v<add_lvalue_reference_t<T>, add_lvalue_reference_t<T>>;
template <class T, class U>
struct is_swappable_with : bool_constant<is_swappable_with_v<T, U>> {};
template <class T>
struct is_swappable : bool_constant<is_swappable_v<T>> {};
template <class T, class U>
struct is_nothrow_swappable_with : bool_constant<is_nothrow_swappable_with_v<T, U>> {};
template <class T>
struct is_nothrow_swappable : bool_constant<is_nothrow_swappable_v<T>> {};
template <class T, bool = __is_complete_v<T>>
inline constexpr bool __is_complete_and_nothrow_swappable_v = false;
template <class T>
inline constexpr bool __is_complete_and_nothrow_swappable_v<T, true> = is_nothrow_swappable_v<T>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__TYPE_TRAITS_IS_SWAPPABLE_H
