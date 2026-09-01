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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONSTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONSTRUCTIBLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/destructible.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp, class... _Args>
concept constructible_from = destructible<_Tp> && is_constructible_v<_Tp, _Args...>;

template <class _Tp>
concept __default_initializable = requires { ::new _Tp; };

template <class _Tp>
concept default_initializable = constructible_from<_Tp> && requires { _Tp{}; } && __default_initializable<_Tp>;

template <class _Tp>
concept move_constructible = constructible_from<_Tp, _Tp> && convertible_to<_Tp, _Tp>;

template <class _Tp>
concept copy_constructible = move_constructible<_Tp> && constructible_from<_Tp, _Tp&> && convertible_to<_Tp&, _Tp> &&
    constructible_from<_Tp, const _Tp&> && convertible_to<const _Tp&, _Tp> && constructible_from<_Tp, const _Tp> &&
    convertible_to<const _Tp, _Tp>;

#else

template <class _Tp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT constructible_from = destructible<_Tp> && is_constructible_v<_Tp, _Args...>;

template <class _Tp, class = void>
inline constexpr bool __default_initializable_impl = false;

template <class _Tp>
inline constexpr bool __default_initializable_impl<_Tp, void_t<decltype(::new _Tp)>> = true;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __default_initializable = __default_initializable_impl<_Tp>;

template <class _Tp, class = void>
inline constexpr bool __brace_default_initializable = false;

template <class _Tp>
inline constexpr bool __brace_default_initializable<_Tp, void_t<decltype(_Tp{})>> = true;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT default_initializable =
    constructible_from<_Tp> && __brace_default_initializable<_Tp> && __default_initializable<_Tp>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT move_constructible = constructible_from<_Tp, _Tp> && convertible_to<_Tp, _Tp>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT copy_constructible =
    move_constructible<_Tp> && constructible_from<_Tp, add_lvalue_reference_t<_Tp>> &&
    convertible_to<add_lvalue_reference_t<_Tp>, _Tp> && constructible_from<_Tp, const add_lvalue_reference_t<_Tp>> &&
    convertible_to<const add_lvalue_reference_t<_Tp>, _Tp> && constructible_from<_Tp, const _Tp> &&
    convertible_to<const _Tp, _Tp>;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Tp, class... _Args>
using __list_initializable_expr = decltype(_Tp{::asc::std::declval<_Args>()...});

template <class _Tp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __list_initializable_from =
    ::asc::std::_IsValidExpansion<__list_initializable_expr, _Tp, _Args...>::value;

template <class _Tp, class _Void, class... _Args>
inline constexpr bool __nothrow_list_initializable_impl = false;

template <class _Tp, class... _Args>
inline constexpr bool
    __nothrow_list_initializable_impl<_Tp, ::asc::std::void_t<__list_initializable_expr<_Tp, _Args...>>, _Args...> =
        noexcept(_Tp{::asc::std::declval<_Args>()...});

template <class _Tp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __nothrow_list_initializable_from =
    __nothrow_list_initializable_impl<_Tp, void, _Args...>;

template <class _Tp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __initializable_from =
    ::asc::std::constructible_from<_Tp, _Args...> || __list_initializable_from<_Tp, _Args...>;

template <class _Tp, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __nothrow_initializable_from = __initializable_from<_Tp, _Args...> &&
    (::asc::std::constructible_from<_Tp, _Args...> ? ::asc::std::is_nothrow_constructible_v<_Tp, _Args...> :
                                                     __nothrow_list_initializable_from<_Tp, _Args...>);

template <class _Tp, class _Fn, class... _Args>
using __emplaceable_expr = decltype(_Tp(::asc::std::declval<_Fn>()(::asc::std::declval<_Args>()...)));

template <class _Tp, class _Fn, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __emplaceable_from =
    ::asc::std::_IsValidExpansion<__emplaceable_expr, _Tp, _Fn, _Args...>::value;

template <class _Tp, class _Fn, class _Void, class... _Args>
inline constexpr bool __nothrow_emplaceable_impl = false;

template <class _Tp, class _Fn, class... _Args>
inline constexpr bool
    __nothrow_emplaceable_impl<_Tp, _Fn, ::asc::std::void_t<__emplaceable_expr<_Tp, _Fn, _Args...>>, _Args...> =
        noexcept(_Tp(::asc::std::declval<_Fn>()(::asc::std::declval<_Args>()...)));

template <class _Tp, class _Fn, class... _Args>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __nothrow_emplaceable_from = __nothrow_emplaceable_impl<_Tp, _Fn, void, _Args...>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONSTRUCTIBLE_H
