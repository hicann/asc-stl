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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_GET_H
#define CANN_ASC_STL_ASC_STD___VARIANT_GET_H

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
#include <asc/std/__fwd/variant.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__tuple/get.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_match.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(variant<Types...>& value)
{
    if (value.index() != Index) {
        __builtin_trap();
    }
    return value.template __get<Index>();
}

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(const variant<Types...>& value)
{
    if (value.index() != Index) {
        __builtin_trap();
    }
    return value.template __get<Index>();
}

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(variant<Types...>&& value)
{
    if (value.index() != Index) {
        __builtin_trap();
    }
    return ::asc::std::move(value).template __get<Index>();
}

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(const variant<Types...>&& value)
{
    if (value.index() != Index) {
        __builtin_trap();
    }
    return ::asc::std::move(value).template __get<Index>();
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(variant<Types...>& value)
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return ::asc::std::get<index>(value);
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(const variant<Types...>& value)
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return ::asc::std::get<index>(value);
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(variant<Types...>&& value)
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return ::asc::std::get<index>(::asc::std::move(value));  // NOLINT(build/include_what_you_use)
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr decltype(auto) get(const variant<Types...>&& value)
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return ::asc::std::get<index>(::asc::std::move(value));  // NOLINT(build/include_what_you_use)
}

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr add_pointer_t<variant_alternative_t<Index, variant<Types...>>> get_if(
    variant<Types...>* value) noexcept
{
    return value != nullptr && value->index() == Index ? ::asc::std::addressof(value->template __get<Index>()) :
                                                         nullptr;
}

template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr add_pointer_t<const variant_alternative_t<Index, variant<Types...>>> get_if(
    const variant<Types...>* value) noexcept
{
    return value != nullptr && value->index() == Index ? ::asc::std::addressof(value->template __get<Index>()) :
                                                         nullptr;
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr add_pointer_t<T> get_if(variant<Types...>* value) noexcept
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return ::asc::std::get_if<index>(value);
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr add_pointer_t<const T> get_if(const variant<Types...>* value) noexcept
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return ::asc::std::get_if<index>(value);
}

template <class T, class... Types>
CANN_ASC_STL_API constexpr bool holds_alternative(const variant<Types...>& value) noexcept
{
    constexpr size_t index = __variant_find_exact<T, Types...>::value;
    static_assert(index != variant_npos, "type is not a unique variant alternative");
    return value.index() == index;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_GET_H
