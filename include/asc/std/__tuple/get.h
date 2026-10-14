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
#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/move.h>

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
    // __get() already preserves the element's reference category. Moving a
    // tuple<int&> element here would incorrectly turn int& into int&&.
    return ::asc::std::move(value).template __get<Index>();
}
template <size_t Index, class... Types>
CANN_ASC_STL_API constexpr const tuple_element_t<Index, tuple<Types...>>&& get(const tuple<Types...>&& value) noexcept
{
    return ::asc::std::move(value).template __get<Index>();
}
// get<T> requires T to occur exactly once in the tuple. The index of the
// occurrence is located with a fold over the element list; duplicate and
// missing types are rejected with a targeted diagnostic instead of silently
// binding the first copy or hard-erroring inside tuple_element.
// First-match index via template recursion: pure instantiation with no
// constexpr control flow, which device compilers evaluate without the
// constant-expression loop limitation.
template <class T, class... Types>
struct __tuple_first_index;
template <class T, class Head, class... Rest>
struct __tuple_first_index<T, Head, Rest...> {
    static constexpr size_t value = is_same_v<T, Head> ? 0 : (1 + __tuple_first_index<T, Rest...>::value);
};
template <class T>
struct __tuple_first_index<T> {
    // Sentinel reached only when no element matches; rejected by the
    // "type not found" assertion below.
    static constexpr size_t value = 0;
};

template <class T, class... Types>
struct __tuple_type_index {
    static constexpr size_t __count = (static_cast<size_t>(is_same_v<T, Types>) + ...);
    static_assert(__count != 0, "type not found in type list");
    // Duplicate element types are an intentional delivered deviation: the
    // first occurrence is selected, which delivery semantics tests rely on
    // (std would require the type to occur exactly once).
    static constexpr size_t value = __tuple_first_index<T, Types...>::value;
};
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
    return ::asc::std::get<__tuple_type_index<T, Types...>::value>(::asc::std::move(value));
}
template <class T, class... Types>
CANN_ASC_STL_API constexpr const T&& get(const tuple<Types...>&& value) noexcept  // NOLINT(build/include_what_you_use)
{
    return ::asc::std::get<__tuple_type_index<T, Types...>::value>(
        ::asc::std::move(value));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_GET_H
