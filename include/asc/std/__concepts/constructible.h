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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_CONSTRUCTIBLE_H
#define CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_CONSTRUCTIBLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T, class... Args>
concept constructible_from = destructible<T> && is_constructible_v<T, Args...>;
template <class T>
concept __default_initializable = requires { ::new T; };
template <class T>
concept default_initializable = constructible_from<T> && requires { T{}; } && __default_initializable<T>;
template <class T>
concept move_constructible = constructible_from<T, T> && convertible_to<T, T>;
template <class T>
concept copy_constructible =
    move_constructible<T> && constructible_from<T, T&> && convertible_to<T&, T> && constructible_from<T, const T&> &&
    convertible_to<const T&, T> && constructible_from<T, const T> && convertible_to<const T, T>;
#else
template <class T, class = void>
inline constexpr bool __default_initializable_impl = false;

template <class T>
inline constexpr bool __default_initializable_impl<T, void_t<decltype(::new T)>> = true;

template <class T>
inline constexpr bool __default_initializable = __default_initializable_impl<T>;

template <class T, class = void>
inline constexpr bool __brace_default_initializable = false;

template <class T>
inline constexpr bool __brace_default_initializable<T, void_t<decltype(T{})>> = true;

template <class T, class... Args>
inline constexpr bool constructible_from = destructible<T> && is_constructible_v<T, Args...>;
template <class T>
inline constexpr bool default_initializable =
    constructible_from<T> && __brace_default_initializable<T> && __default_initializable<T>;
template <class T>
inline constexpr bool move_constructible = constructible_from<T, T> && convertible_to<T, T>;
template <class T, class = void>
inline constexpr bool __copy_constructible_impl = false;
template <class T>
inline constexpr bool __copy_constructible_impl<T, void_t<T&>> =
    move_constructible<T> && constructible_from<T, T&> && convertible_to<T&, T> && constructible_from<T, const T&> &&
    convertible_to<const T&, T> && constructible_from<T, const T> && convertible_to<const T, T>;
template <class T>
inline constexpr bool copy_constructible = __copy_constructible_impl<T>;

#endif

CANN_ASC_STL_END_NAMESPACE

namespace asc {

template <class T, class... Args>
using __list_initializable_expr = decltype(T{::asc::std::declval<Args>()...});

template <class T, class... Args>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __list_initializable_from = ::asc::std::_IsValidExpansion<__list_initializable_expr, T, Args...>::value;
#else
inline constexpr bool __list_initializable_from =
    ::asc::std::_IsValidExpansion<__list_initializable_expr, T, Args...>::value;
#endif

template <class T, class Void, class... Args>
inline constexpr bool __nothrow_list_initializable_impl = false;

template <class T, class... Args>
inline constexpr bool
    __nothrow_list_initializable_impl<T, ::asc::std::void_t<__list_initializable_expr<T, Args...>>, Args...> =
        noexcept(T{::asc::std::declval<Args>()...});

template <class T, class... Args>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __nothrow_list_initializable_from = __nothrow_list_initializable_impl<T, void, Args...>;
#else
inline constexpr bool __nothrow_list_initializable_from = __nothrow_list_initializable_impl<T, void, Args...>;
#endif

template <class T, class... Args>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __initializable_from = ::asc::std::constructible_from<T, Args...> || __list_initializable_from<T, Args...>;
#else
inline constexpr bool __initializable_from =
    ::asc::std::is_constructible_v<T, Args...> || __list_initializable_from<T, Args...>;
#endif

template <class T, class... Args>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __nothrow_initializable_from = __initializable_from<T, Args...> &&
    (::asc::std::constructible_from<T, Args...> ? ::asc::std::is_nothrow_constructible_v<T, Args...> :
                                                  __nothrow_list_initializable_from<T, Args...>);
#else
inline constexpr bool __nothrow_initializable_from = __initializable_from<T, Args...> &&
    (::asc::std::is_constructible_v<T, Args...> ? ::asc::std::is_nothrow_constructible_v<T, Args...> :
                                                  __nothrow_list_initializable_from<T, Args...>);
#endif

template <class T, class Fn, class... Args>
using __emplaceable_expr = decltype(T(::asc::std::declval<Fn>()(::asc::std::declval<Args>()...)));

template <class T, class Fn, class... Args>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __emplaceable_from = ::asc::std::_IsValidExpansion<__emplaceable_expr, T, Fn, Args...>::value;
#else
inline constexpr bool __emplaceable_from = ::asc::std::_IsValidExpansion<__emplaceable_expr, T, Fn, Args...>::value;
#endif

template <class T, class Fn, class Void, class... Args>
inline constexpr bool __nothrow_emplaceable_impl = false;

template <class T, class Fn, class... Args>
inline constexpr bool
    __nothrow_emplaceable_impl<T, Fn, ::asc::std::void_t<__emplaceable_expr<T, Fn, Args...>>, Args...> =
        noexcept(T(::asc::std::declval<Fn>()(::asc::std::declval<Args>()...)));

template <class T, class Fn, class... Args>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __nothrow_emplaceable_from = __nothrow_emplaceable_impl<T, Fn, void, Args...>;
#else
inline constexpr bool __nothrow_emplaceable_from = __nothrow_emplaceable_impl<T, Fn, void, Args...>;
#endif

}  // namespace asc

#endif  // CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_CONSTRUCTIBLE_H
