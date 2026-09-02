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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_LIKE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_LIKE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, class = void>
inline constexpr bool __integral_constant_like_impl = false;

template <class _Tp>
inline constexpr bool __integral_constant_like_impl<_Tp,
    void_t<decltype(_Tp::value), typename bool_constant<(_Tp() == _Tp::value)>::type,
        typename bool_constant<(static_cast<decltype(_Tp::value)>(_Tp()) == _Tp::value)>::type>> =
    is_integral_v<remove_cvref_t<decltype(_Tp::value)>> && !is_same_v<bool, remove_cvref_t<decltype(_Tp::value)>> &&
    convertible_to<_Tp, decltype(_Tp::value)> && equality_comparable_with<_Tp, decltype(_Tp::value)>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __integral_constant_like = __integral_constant_like_impl<_Tp>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_LIKE_H
