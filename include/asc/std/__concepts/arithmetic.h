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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_ARITHMETIC_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_ARITHMETIC_H

#include <asc/std/detail/__config>

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_signed_integer.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// [concepts.arithmetic], arithmetic concepts

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept integral = is_integral_v<_Tp>;

template <class _Tp>
concept signed_integral = integral<_Tp> && is_signed_v<_Tp>;

template <class _Tp>
concept unsigned_integral = integral<_Tp> && !signed_integral<_Tp>;

template <class _Tp>
concept floating_point = is_floating_point_v<_Tp>;

template <class _Tp>
concept __asc_signed_integer = __asc_is_cv_signed_integer_v<_Tp>;

#else

template <class _Tp>
inline constexpr bool integral = is_integral_v<_Tp>;

template <class _Tp>
inline constexpr bool signed_integral = integral<_Tp> && is_signed_v<_Tp>;

template <class _Tp>
inline constexpr bool unsigned_integral = integral<_Tp> && !signed_integral<_Tp>;

template <class _Tp>
inline constexpr bool floating_point = is_floating_point_v<_Tp>;

template <class _Tp>
inline constexpr bool __asc_signed_integer = __asc_is_cv_signed_integer_v<_Tp>;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_ARITHMETIC_H
