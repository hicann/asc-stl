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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CONSTRAINTS_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CONSTRAINTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__tuple/make_tuple_types.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_comparable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_implicitly_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/lazy.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class To, class From>
struct __tuple_constructible : is_constructible<To, From> {};
template <class To, class From>
struct __tuple_convertible : is_convertible<From, To> {};
template <class To, class From>
struct __tuple_assignable : is_assignable<To&, From> {};

template <class T1, class T2, class U1, class U2>
inline constexpr bool __pair_constructible_v = is_constructible_v<T1, U1> && is_constructible_v<T2, U2>;
template <class T1, class T2, class U1, class U2>
inline constexpr bool __pair_convertible_v = is_convertible_v<U1, T1> && is_convertible_v<U2, T2>;
template <class T1, class T2, class U1, class U2>
inline constexpr bool __pair_assignable_v = is_assignable_v<T1&, U1> && is_assignable_v<T2&, U2>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CONSTRAINTS_H
