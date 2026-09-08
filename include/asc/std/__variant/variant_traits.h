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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_TRAITS_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/add_cv.h>
#include <asc/std/__type_traits/add_volatile.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/type_list.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct variant_size;

template <class... Types>
struct variant_size<variant<Types...>> : integral_constant<__SIZE_TYPE__, sizeof...(Types)> {};
template <class T>
struct variant_size<const T> : variant_size<T> {};
template <class T>
struct variant_size<volatile T> : variant_size<T> {};
template <class T>
struct variant_size<const volatile T> : variant_size<T> {};

template <__SIZE_TYPE__ Index, class T>
struct variant_alternative;

template <__SIZE_TYPE__ Index, class... Types>
struct variant_alternative<Index, variant<Types...>> {
    static_assert(Index < sizeof...(Types), "variant_alternative index out of bounds");
    using type = __type_index_c<Index, Types...>;
};
template <__SIZE_TYPE__ Index, class T>
struct variant_alternative<Index, const T> {
    using type = add_const_t<typename variant_alternative<Index, T>::type>;
};
template <__SIZE_TYPE__ Index, class T>
struct variant_alternative<Index, volatile T> {
    using type = add_volatile_t<typename variant_alternative<Index, T>::type>;
};
template <__SIZE_TYPE__ Index, class T>
struct variant_alternative<Index, const volatile T> {
    using type = add_cv_t<typename variant_alternative<Index, T>::type>;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_TRAITS_H
