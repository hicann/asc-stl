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
#include <asc/std/__tuple/tie.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_API constexpr tuple<> tuple_cat() noexcept
{
    return {};
}
template <class Left, class Right, size_t... LeftIndices, size_t... RightIndices>
CANN_ASC_STL_API constexpr auto __tuple_cat_two(Left&& left, Right&& right, __tuple_indices<LeftIndices...>,
    __tuple_indices<RightIndices...>) -> tuple<tuple_element_t<LeftIndices, remove_reference_t<Left>>...,
                                          tuple_element_t<RightIndices, remove_reference_t<Right>>...>
{
    using result_type = tuple<tuple_element_t<LeftIndices, remove_reference_t<Left>>...,
        tuple_element_t<RightIndices, remove_reference_t<Right>>...>;
    return result_type(::asc::std::get<LeftIndices>(::asc::std::forward<Left>(left))...,
        ::asc::std::get<RightIndices>(::asc::std::forward<Right>(right))...);
}
template <class Left, class Right>
CANN_ASC_STL_API constexpr auto __tuple_cat_pair(Left&& left, Right&& right)
{
    return __tuple_cat_two(::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right),
        __make_tuple_indices_t<tuple_size<remove_reference_t<Left>>::value>{},
        __make_tuple_indices_t<tuple_size<remove_reference_t<Right>>::value>{});
}
template <class Tuple>
CANN_ASC_STL_API constexpr auto tuple_cat(Tuple&& value)
{
    return __tuple_cat_pair(tuple<>{},  // NOLINT(build/include_what_you_use)
        ::asc::std::forward<Tuple>(value));
}
template <class Left, class Right, class... Rest>
CANN_ASC_STL_API constexpr auto tuple_cat(Left&& left, Right&& right, Rest&&... rest)
{
    auto joined = __tuple_cat_pair(::asc::std::forward<Left>(left), ::asc::std::forward<Right>(right));
    if constexpr (sizeof...(Rest) == 0) {
        return joined;
    } else {
        return ::asc::std::tuple_cat(::asc::std::move(joined),  // NOLINT(build/include_what_you_use)
            ::asc::std::forward<Rest>(rest)...);                // NOLINT(build/include_what_you_use)
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_CAT_H
