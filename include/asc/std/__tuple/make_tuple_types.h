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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_MAKE_TUPLE_TYPES_H
#define CANN_ASC_STL_ASC_STD___TUPLE_MAKE_TUPLE_TYPES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Tuple, class Indices>
struct __make_tuple_types_flat;
template <template <class...> class Tuple, class... T, size_t... I>
struct __make_tuple_types_flat<Tuple<T...>, __tuple_indices<I...>> {
    using __tuple_types_list = __type_list<T...>;
    template <class U, class Apply = __apply_cvref_fn<U>>
    using __apply_quals = __tuple_types<__type_call1<Apply, __type_at_c<I, __tuple_types_list>>...>;
};
template <class V, size_t N, size_t... I>
struct __make_tuple_types_flat<array<V, N>, __tuple_indices<I...>> {
    template <size_t>
    using __value_type = V;
    template <class U, class Apply = __apply_cvref_fn<U>>
    using __apply_quals = __tuple_types<__type_call1<Apply, __value_type<I>>...>;
};
template <class V, size_t... I>
struct __make_tuple_types_flat<complex<V>, __tuple_indices<I...>> {
    static_assert(sizeof...(I) == 2, "complex has two tuple elements");
    template <size_t>
    using __value_type = V;
    template <class U, class Apply = __apply_cvref_fn<U>>
    using __apply_quals = __tuple_types<__type_call1<Apply, __value_type<I>>...>;
};
template <class T, size_t End = tuple_size<remove_reference_t<T>>::value, size_t Start = 0,
    bool SameSize = (End == tuple_size<remove_reference_t<T>>::value)>
struct __make_tuple_types {
    static_assert(Start <= End, "invalid tuple type range");
    using raw = remove_cv_t<remove_reference_t<T>>;
    using type = typename __make_tuple_types_flat<raw, __make_tuple_indices_t<End, Start>>::template __apply_quals<T>;
};
// Identity fast paths: an unqualified tuple / __tuple_types spanning its full
// element range already is the requested __tuple_types - skip the cvref
// projection over the whole element list.
template <class... Types, size_t End>
struct __make_tuple_types<tuple<Types...>, End, 0, true> {  // NOLINT(build/include_what_you_use)
    using type = __tuple_types<Types...>;
};
template <class... Types, size_t End>
struct __make_tuple_types<__tuple_types<Types...>, End, 0, true> {
    using type = __tuple_types<Types...>;
};
template <class T, size_t End = tuple_size<remove_reference_t<T>>::value, size_t Start = 0>
using __make_tuple_types_t = typename __make_tuple_types<T, End, Start>::type;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_MAKE_TUPLE_TYPES_H
