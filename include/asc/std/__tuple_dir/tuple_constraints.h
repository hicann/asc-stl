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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_CONSTRAINTS_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_CONSTRAINTS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER
#include <asc/std/__tuple_dir/tuple_like.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__type_traits/is_assignable.h>
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
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class... _Types>
inline constexpr bool __tuple_all_nothrow_copy_constructible_v = (is_nothrow_copy_constructible_v<_Types> && ...);
template <class... _Types>
inline constexpr bool __tuple_all_nothrow_move_constructible_v = (is_nothrow_move_constructible_v<_Types> && ...);
template <class, class>
inline constexpr bool __tuple_all_nothrow_constructible_v = false;
template <class... _Types, class... _UTypes>
inline constexpr bool __tuple_all_nothrow_constructible_v<__tuple_types<_Types...>, __tuple_types<_UTypes...>> =
    (is_nothrow_constructible_v<_Types, _UTypes> && ...);
template <class... _Types>
inline constexpr bool __tuple_all_copy_assignable_v = (is_copy_assignable_v<_Types> && ...);
template <class... _Types>
inline constexpr bool __tuple_all_move_assignable_v = (is_move_assignable_v<_Types> && ...);
template <class _Tuple, size_t _ExpectedSize, bool = __tuple_like_v<_Tuple>>
inline constexpr bool __tuple_like_with_size = false;
template <class _Tuple, size_t _ExpectedSize>
inline constexpr bool __tuple_like_with_size<_Tuple, _ExpectedSize, true> =
    _ExpectedSize == tuple_size<remove_cvref_t<_Tuple>>::value;

enum class __select_constructor {
    __none,
    __implicit,
    __explicit,
};

template <__select_constructor _Trait>
inline constexpr bool __can_construct_implicitly = _Trait == __select_constructor::__implicit;
template <__select_constructor _Trait>
inline constexpr bool __can_construct_explicitly = _Trait == __select_constructor::__explicit;
template <__select_constructor _Trait>
inline constexpr bool __can_construct = _Trait != __select_constructor::__none;

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL __select_constructor __tuple_select_default_constructible(
    __tuple_types<_Types...>) noexcept
{
    if constexpr (!(is_default_constructible_v<_Types> && ...)) {
        return __select_constructor::__none;
    } else if constexpr ((__is_implicitly_default_constructible<_Types>::value && ...)) {
        return __select_constructor::__implicit;
    } else {
        return __select_constructor::__explicit;
    }
}

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL __select_constructor
__tuple_select_variadic_copy_constructible(__tuple_types<_Types...>) noexcept
{
    if constexpr (!(is_copy_constructible_v<_Types> && ...)) {
        return __select_constructor::__none;
    } else if constexpr ((is_convertible_v<const _Types&, _Types> && ...)) {
        return __select_constructor::__implicit;
    } else {
        return __select_constructor::__explicit;
    }
}

template <class _TupleTypes>
inline constexpr __select_constructor __tuple_select_variadic_copy_constructible_v =
    ::asc::std::__tuple_select_variadic_copy_constructible(_TupleTypes{});

template <class... _Types>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL __select_constructor
__tuple_select_variadic_move_constructible(__tuple_types<_Types...>) noexcept
{
    if constexpr (!(is_move_constructible_v<_Types> && ...)) {
        return __select_constructor::__none;
    } else if constexpr ((is_convertible_v<_Types&&, _Types> && ...)) {
        return __select_constructor::__implicit;
    } else {
        return __select_constructor::__explicit;
    }
}

template <class _TupleTypes>
inline constexpr __select_constructor __tuple_select_variadic_move_constructible_v =
    ::asc::std::__tuple_select_variadic_move_constructible(_TupleTypes{});

template <class... _Types, class... _UTypes>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL __select_constructor __tuple_select_variadic_constructible(
    __tuple_types<_Types...>, __tuple_types<_UTypes...>) noexcept
{
    if constexpr (sizeof...(_Types) != sizeof...(_UTypes)) {
        return __select_constructor::__none;
    } else if constexpr (sizeof...(_Types) == 0) {
        return __select_constructor::__none;
    } else if constexpr ((is_constructible_v<_Types, _UTypes> && ...)) {
        constexpr bool can_implicit = (is_convertible_v<_UTypes, _Types> && ...);
        return can_implicit ? __select_constructor::__implicit : __select_constructor::__explicit;
    } else {
        return __select_constructor::__none;
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_CONSTRAINTS_H
