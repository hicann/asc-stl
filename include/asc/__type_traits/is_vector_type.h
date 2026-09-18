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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_VECTOR_TYPE_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_VECTOR_TYPE_H

#include <asc/std/detail/__config>

#include <asc/__type_traits/scalar_type.h>
#include <asc/__type_traits/vector_size.h>
#include <asc/std/__floating_point/traits.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Tp>
inline constexpr bool is_vector_type_v = (vector_size_v<_Tp> != 0);

template <class _Tp>
using is_vector_type = ::asc::std::bool_constant<is_vector_type_v<_Tp>>;

template <class _Tp, class = void>
inline constexpr bool is_extended_fp_vector_type_v = false;

template <class _Tp>
inline constexpr bool is_extended_fp_vector_type_v<_Tp, ::asc::std::void_t<typename scalar_type<_Tp>::type>> =
    ::asc::std::__is_ext_asc_fp_v<scalar_type_t<_Tp>>;

template <class _Tp>
using is_extended_fp_vector_type = ::asc::std::bool_constant<is_extended_fp_vector_type_v<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_VECTOR_TYPE_H
