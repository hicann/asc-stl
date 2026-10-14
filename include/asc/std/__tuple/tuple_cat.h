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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CAT_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CAT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__tuple/get.h>
#include <asc/std/__tuple/make_tuple_types.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class TTypes, class UTypes>
struct __tuple_cat_type;
template <class... TTypes, class... UTypes>
struct __tuple_cat_type<tuple<TTypes...>, __tuple_types<UTypes...>> {
    using type = tuple<TTypes..., UTypes...>;
};

// Value-semantic result type: the concatenation of the unqualified element
// type lists of all argument tuples (elements that are themselves
// references, as produced by tie, stay references).
template <class Result, bool IsTupleLike, class... Tuples>
struct __tuple_cat_return_1 {};
template <class... Types, class Tuple0>
struct __tuple_cat_return_1<tuple<Types...>, true, Tuple0> {
    using type = typename __tuple_cat_type<tuple<Types...>, __make_tuple_types_t<remove_cvref_t<Tuple0>>>::type;
};
template <class... Types, class Tuple0, class Tuple1, class... Tuples>
struct __tuple_cat_return_1<tuple<Types...>, true, Tuple0, Tuple1, Tuples...>
    : __tuple_cat_return_1<
          typename __tuple_cat_type<tuple<Types...>, __make_tuple_types_t<remove_cvref_t<Tuple0>>>::type,
          __tuple_like_ext<remove_reference_t<Tuple1>>, Tuple1, Tuples...> {};
template <class... Tuples>
struct __tuple_cat_return;
template <class Tuple0, class... Tuples>
struct __tuple_cat_return<Tuple0, Tuples...>
    : __tuple_cat_return_1<tuple<>, __tuple_like_ext<remove_reference_t<Tuple0>>, Tuple0, Tuples...> {};
template <>
struct __tuple_cat_return<> {
    using type = tuple<>;
};

// Flat-element bookkeeping: maps a result element index onto the argument
// tuple it originates from and its position inside that tuple. Both helpers
// are evaluated in constant expressions only; they never run.
template <size_t Index, class... Tuples>
CANN_ASC_STL_API constexpr size_t __tuple_cat_tuple_index()
{
    constexpr size_t sizes[] = {tuple_size<Tuples>::value...};
    size_t selected = 0;
    size_t offset = 0;
    while (Index >= offset + sizes[selected]) {
        offset += sizes[selected];
        ++selected;
    }
    return selected;
}
template <size_t Index, class... Tuples>
CANN_ASC_STL_API constexpr size_t __tuple_cat_element_index()
{
    constexpr size_t sizes[] = {tuple_size<Tuples>::value...};
    size_t offset = 0;
    for (size_t k = 0; k < __tuple_cat_tuple_index<Index, Tuples...>(); ++k) {
        offset += sizes[k];
    }
    return Index - offset;
}

// Extracts result element Index out of the packed references to the argument
// tuples. The nested get calls preserve each argument's value category:
// lvalue tuples yield lvalue elements, rvalue tuples yield rvalue elements,
// and reference elements keep their reference category.
template <size_t Index, class... Tuples, class Holder>
CANN_ASC_STL_API constexpr decltype(auto) __tuple_cat_element(Holder&& holder)
{
    return ::asc::std::get<__tuple_cat_element_index<Index, Tuples...>()>(
        ::asc::std::get<__tuple_cat_tuple_index<Index, Tuples...>()>(::asc::std::forward<Holder>(holder)));
}

// Single construction pass: the arguments are packed by reference exactly
// once and the result tuple is materialized exactly once, with no
// intermediate tuples and no per-argument call chain.
template <class... Tuples, size_t... Indices>
CANN_ASC_STL_API constexpr typename __tuple_cat_return<Tuples...>::type __tuple_cat_impl(
    __tuple_indices<Indices...>, Tuples&&... tuples)
{
    tuple<Tuples&&...> holder(::asc::std::forward<Tuples>(tuples)...);
    return typename __tuple_cat_return<Tuples...>::type(
        __tuple_cat_element<Indices, remove_reference_t<Tuples>...>(::asc::std::move(holder))...);
}

CANN_ASC_STL_API constexpr tuple<> tuple_cat() noexcept  // NOLINT(build/include_what_you_use)
{
    return {};
}
template <class... Tuples>
CANN_ASC_STL_API constexpr typename __tuple_cat_return<Tuples...>::type tuple_cat(Tuples&&... tuples)
{
    return __tuple_cat_impl(__make_tuple_indices_t<(tuple_size<remove_reference_t<Tuples>>::value + ...)>{},
        ::asc::std::forward<Tuples>(tuples)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CAT_H
