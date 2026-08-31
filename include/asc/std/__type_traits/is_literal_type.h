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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_LITERAL_TYPE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_LITERAL_TYPE_H

#include <asc/std/detail/__config>
#include <asc/std/__type_traits/integral_constant.h>

#define CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_LITERAL(...) __is_literal_type(__VA_ARGS__)

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Tp>
struct is_literal_type : bool_constant<CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_LITERAL(_Tp)> {};

template <class _Tp>
inline constexpr bool is_literal_type_v = CANN_ASC_STL_DETAIL_ACCL_BUILTIN_IS_LITERAL(_Tp);

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_LITERAL_TYPE_H
