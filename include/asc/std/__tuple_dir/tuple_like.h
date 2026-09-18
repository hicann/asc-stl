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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_LIKE_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_LIKE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Extended tuple-like detection: true for any type that participates
//! in structured-binding-style element access via tuple_size/tuple_element.
template <class _Tp>
inline constexpr bool __tuple_like_ext = false;

template <class _Tp>
inline constexpr bool __tuple_like_ext<const _Tp> = __tuple_like_ext<_Tp>;
template <class _Tp>
inline constexpr bool __tuple_like_ext<volatile _Tp> = __tuple_like_ext<_Tp>;
template <class _Tp>
inline constexpr bool __tuple_like_ext<const volatile _Tp> = __tuple_like_ext<_Tp>;

template <class... _Tp>
inline constexpr bool __tuple_like_ext<tuple<_Tp...>> = true;

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class... _Tp>
inline constexpr bool __tuple_like_ext<::std::tuple<_Tp...>> = true;  // NOLINT(build/include_what_you_use)
#endif

template <class _T1, class _T2>
inline constexpr bool __tuple_like_ext<pair<_T1, _T2>> = true;

#if CANN_ASC_STL_DETAIL_HOSTED()
template <class _T1, class _T2>
inline constexpr bool __tuple_like_ext<::std::pair<_T1, _T2>> = true;  // NOLINT(build/include_what_you_use)
#endif

template <class... _Tp>
inline constexpr bool __tuple_like_ext<__tuple_types<_Tp...>> = true;

//! @brief Concept constraining types usable in tuple protocol (get, apply, etc).
template <class _Tp>
inline constexpr bool __tuple_like_v = __tuple_like_ext<remove_cvref_t<_Tp>>;

//! @brief Concept constraining tuple-like types with exactly two elements.
// tuple_size<T> is incomplete for unspecialized types (e.g. asc::std::byte), so
// reading ::value directly is a hard error; the reference gets natural SFINAE from a
// requires-expression. The detection-idiom form below is the equivalent.
template <class _Tp, class = void>
inline constexpr bool __pair_like_size_is_2 = false;

template <class _Tp>
inline constexpr bool __pair_like_size_is_2<_Tp, void_t<decltype(tuple_size<remove_cvref_t<_Tp>>::value)>> =
    tuple_size<remove_cvref_t<_Tp>>::value == 2;

template <class _Tp>
inline constexpr bool __pair_like_v = __tuple_like_ext<remove_cvref_t<_Tp>> && __pair_like_size_is_2<_Tp>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_LIKE_H
