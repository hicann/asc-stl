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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_DESTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_DESTRUCTIBLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_nothrow_destructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT destructible = __is_nothrow_destructible(_Tp);

#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv

template <class _Tp, class = void, class = void>
inline constexpr bool __destructible_impl = false;

template <class _Tp>
inline constexpr bool __destructible_impl<_Tp, enable_if_t<is_object_v<_Tp> >,
#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
    enable_if_t<is_destructible_v<_Tp> > >
#else   // ^^^ CANN_ASC_STL_DETAIL_COMPILER(GCC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(GCC) vvv
    void_t<decltype(::asc::std::declval<_Tp>().~_Tp())> >
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(GCC)
    = noexcept(::asc::std::declval<_Tp>().~_Tp());

template <class _Tp>
inline constexpr bool __destructible = __destructible_impl<_Tp>;

template <class _Tp>
inline constexpr bool __destructible<_Tp&> = true;

template <class _Tp>
inline constexpr bool __destructible<_Tp&&> = true;

template <class _Tp, size_t _Nm>
inline constexpr bool __destructible<_Tp[_Nm]> = __destructible<_Tp>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT destructible = __destructible<_Tp>;

#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_DESTRUCTIBLE_H
