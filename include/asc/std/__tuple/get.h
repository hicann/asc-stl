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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_GET_H
#define CANN_ASC_STL_ASC_STD___TUPLE_GET_H

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
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr tuple_element_t<Index, tuple<Types...>>& get(tuple<Types...>& value) noexcept
{
    return value.template __get<Index>();
}
template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr const tuple_element_t<Index, tuple<Types...>>& get(const tuple<Types...>& value) noexcept
{
    return value.template __get<Index>();
}
template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr tuple_element_t<Index, tuple<Types...>>&& get(tuple<Types...>&& value) noexcept
{
    return ::asc::std::move(value).template __get<Index>();
}
template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr const tuple_element_t<Index, tuple<Types...>>&& get(const tuple<Types...>&& value) noexcept
{
    return ::asc::std::move(value).template __get<Index>();
}
template <class T, class Head, class... Tail>
struct __tuple_type_index : integral_constant<size_t, 1 + __tuple_type_index<T, Tail...>::value> {};
template <class T, class... Tail>
struct __tuple_type_index<T, T, Tail...> : integral_constant<size_t, 0> {};
template <class T, class... Types>
CANN_ASC_STL_API constexpr T& get(tuple<Types...>& value) noexcept
{
    return ::asc::std::get<__tuple_type_index<T, Types...>::value>(value);
}
template <class T, class... Types>
CANN_ASC_STL_API constexpr const T& get(const tuple<Types...>& value) noexcept
{
    return ::asc::std::get<__tuple_type_index<T, Types...>::value>(value);
}
template <class T, class... Types>
CANN_ASC_STL_API constexpr T&& get(tuple<Types...>&& value) noexcept
{
    return ::asc::std::get<__tuple_type_index<T, Types...>::value>(  // NOLINT(build/include_what_you_use)
        ::asc::std::move(value));
}
template <class T, class... Types>
CANN_ASC_STL_API constexpr const T&& get(    // NOLINT(build/include_what_you_use)
    const tuple<Types...>&& value) noexcept  // NOLINT(build/include_what_you_use)
{
    return ::asc::std::get<__tuple_type_index<T, Types...>::value>(  // NOLINT(build/include_what_you_use)
        ::asc::std::move(value));                                    // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_GET_H
