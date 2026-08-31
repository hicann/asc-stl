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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_integral.h>

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_signed)
#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED(...) __is_signed(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_signed)

// if we put this trait to asc::std::, it colides with libstdc++, putting it to to global namespace seems to work fine
#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED)
template <class _Tp>
inline constexpr bool __asc_is_signed_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED(_Tp);
#endif  // CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED)

template <class _Tp>
struct is_signed : bool_constant<::__asc_is_signed_v<_Tp>> {};

template <class _Tp>
inline constexpr bool is_signed_v = ::__asc_is_signed_v<_Tp>;

#else  // ^^^ CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED ^^^ / vvv !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED vvv

template <class _Tp, bool = is_integral_v<_Tp>>
inline constexpr bool __asc_is_signed_helper_v = true;

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4197)  // top-level volatile in cast is ignored

template <class _Tp>
inline constexpr bool __asc_is_signed_helper_v<_Tp, true> = _Tp(-1) < _Tp(0);

CANN_ASC_STL_DETAIL_DIAG_POP

template <class _Tp>
inline constexpr bool is_signed_v = is_arithmetic_v<_Tp> && __asc_is_signed_helper_v<_Tp>;

template <class _Tp>
struct is_signed : bool_constant<is_signed_v<_Tp>> {};

#endif  // ^^^ !CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_SIGNED ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_SIGNED_H
