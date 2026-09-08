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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_APPLY_H
#define CANN_ASC_STL_ASC_STD___TUPLE_APPLY_H

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
#include <asc/std/__tuple/get.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Function, class Tuple, size_t... Indices>
CANN_ASC_STL_API constexpr decltype(auto) __apply_tuple_impl(
    Function&& function, Tuple&& value, __tuple_indices<Indices...>)
{
    return ::asc::std::invoke(::asc::std::forward<Function>(function),  // NOLINT(build/include_what_you_use)
        ::asc::std::get<Indices>(::asc::std::forward<Tuple>(value))...);
}
template <class Function, class Tuple>
CANN_ASC_STL_API constexpr decltype(auto) apply(Function&& function, Tuple&& value)
{
    using tuple_type = remove_reference_t<Tuple>;
    return __apply_tuple_impl(::asc::std::forward<Function>(function),  // NOLINT(build/include_what_you_use)
        ::asc::std::forward<Tuple>(value), __make_tuple_indices_t<tuple_size<tuple_type>::value>{});
}
template <class T, class Tuple, size_t... Indices>
CANN_ASC_STL_API constexpr T __make_from_tuple_impl(Tuple&& value, __tuple_indices<Indices...>)
{
    return T(::asc::std::get<Indices>(::asc::std::forward<Tuple>(value))...);
}
template <class T, class Tuple>
CANN_ASC_STL_API constexpr T make_from_tuple(Tuple&& value)
{
    using tuple_type = remove_reference_t<Tuple>;
    return __make_from_tuple_impl<T>(::asc::std::forward<Tuple>(value),  // NOLINT(build/include_what_you_use)
        __make_tuple_indices_t<tuple_size<tuple_type>::value>{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_APPLY_H
