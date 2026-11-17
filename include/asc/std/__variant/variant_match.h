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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_MATCH_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_MATCH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/integer_sequence.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class... Types>
struct __variant_find_exact;
template <class T>
struct __variant_find_exact<T> : integral_constant<__SIZE_TYPE__, static_cast<__SIZE_TYPE__>(-1)> {};
template <class T, class Head, class... Tail>
struct __variant_find_exact<T, Head, Tail...>
    : integral_constant<__SIZE_TYPE__,
          is_same_v<T, Head> ? 0 :
                               (__variant_find_exact<T, Tail...>::value == static_cast<__SIZE_TYPE__>(-1) ?
                                       static_cast<__SIZE_TYPE__>(-1) :
                                       1 + __variant_find_exact<T, Tail...>::value)> {};

// Implicit-conversion probe: overload resolution admits the alternative only
// when Source converts implicitly to Destination (function-parameter style)
// and no list-initialization narrowing occurs.
template <class Destination>
CANN_ASC_STL_API void __variant_accept_implicit_conversion(Destination) noexcept
{}

template <class Destination, class Source, class = void>
struct __variant_is_non_narrowing_convertible : false_type {};

template <class Destination, class Source>
struct __variant_is_non_narrowing_convertible<Destination, Source,
    void_t<decltype(::asc::std::__variant_accept_implicit_conversion<Destination>(::asc::std::declval<Source>())),
        decltype(Destination{::asc::std::declval<Source>()})>> : true_type {};

struct __variant_no_narrowing_check {
    template <class Destination, class Source>
    using apply = type_identity<Destination>;
};

struct __variant_narrowing_check {
    template <class Destination, class Source,
        bool NonNarrowing = __variant_is_non_narrowing_convertible<Destination, Source>::value>
    struct conversion {};

    template <class Destination, class Source>
    struct conversion<Destination, Source, true> {
        using type = type_identity<Destination>;
    };

    template <class Destination, class Source>
    using apply = typename conversion<Destination, Source>::type;
};

// Arithmetic alternatives participate in matching under the narrowing check;
// all other alternatives only require a regular implicit conversion.
template <class Destination, class Source>
using __variant_check_for_narrowing = typename conditional_t<is_arithmetic_v<Destination>, __variant_narrowing_check,
    __variant_no_narrowing_check>::template apply<Destination, Source>;

template <class T, __SIZE_TYPE__ Index>
struct __variant_overload {
    template <class Source>
    CANN_ASC_STL_API auto operator()(T, Source&&) const -> __variant_check_for_narrowing<T, Source>;
};

// The bool alternative accepts only genuine bool arguments, preventing
// integers/pointers from usurping the bool slot via standard conversions.
template <class T, __SIZE_TYPE__>
struct __variant_overload_bool {
    template <class Source, class Arg = remove_cvref_t<Source>>
    CANN_ASC_STL_API auto operator()(bool, Source&&) const -> enable_if_t<is_same_v<Arg, bool>, type_identity<T>>;
};

template <__SIZE_TYPE__ Index>
struct __variant_overload<bool, Index> : __variant_overload_bool<bool, Index> {};
template <__SIZE_TYPE__ Index>
struct __variant_overload<bool const, Index> : __variant_overload_bool<bool const, Index> {};
template <__SIZE_TYPE__ Index>
struct __variant_overload<bool volatile, Index> : __variant_overload_bool<bool volatile, Index> {};
template <__SIZE_TYPE__ Index>
struct __variant_overload<bool const volatile, Index> : __variant_overload_bool<bool const volatile, Index> {};

template <class... Bases>
struct __variant_all_overloads : Bases... {
    CANN_ASC_STL_API void operator()() const;
    using Bases::operator()...;
};

template <class IndexSequence>
struct __variant_make_overloads_imp;

template <size_t... Indices>
struct __variant_make_overloads_imp<__tuple_indices<Indices...>> {
    template <class... Types>
    using apply = __variant_all_overloads<__variant_overload<Types, Indices>...>;
};

template <class... Types>
using __variant_make_overloads =
    typename __variant_make_overloads_imp<__make_indices_imp<sizeof...(Types), 0>>::template apply<Types...>;

// Overload resolution picks the best-matching alternative for T; on ambiguity
// or no match the alias is unavailable (SFINAE-friendly).
template <class T, class... Types>
using __variant_best_match_t = typename __invoke_result_t<__variant_make_overloads<Types...>, T, T>::type;

template <class T, class Void, class... Types>
struct __variant_best_match {};

template <class T, class... Types>
struct __variant_best_match<T, void_t<__variant_best_match_t<T, Types...>>, Types...>
    : integral_constant<__SIZE_TYPE__, __variant_find_exact<__variant_best_match_t<T, Types...>, Types...>::value> {};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_MATCH_H
