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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_INTEGER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_INTEGER_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/is_signed_integer.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// __asc_is_integer is a trait that tests whether a type is an integral type intended for arithmetic.
// In contrast to is_integral, __asc_is_integer excludes bool and character types.
// See https://eel.is/c++draft/basic.fundamental#1
template <class _Tp>
inline constexpr bool __asc_is_integer_v = __asc_is_signed_integer_v<_Tp> || __asc_is_unsigned_integer_v<_Tp>;

template <class _Tp>
inline constexpr bool __asc_is_cv_integer_v = __asc_is_cv_signed_integer_v<_Tp> || __asc_is_cv_unsigned_integer_v<_Tp>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_INTEGER_H
