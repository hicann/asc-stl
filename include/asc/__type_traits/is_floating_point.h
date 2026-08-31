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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//! Tells whether a type is a floating point type, including extended floating point types.
//! Users are allowed to specialize this template for their own types.
template <class _Tp>
inline constexpr bool is_floating_point_v = asc::std::is_floating_point_v<asc::std::remove_cv_t<_Tp>> ||
    asc::std::__is_extended_floating_point_v<asc::std::remove_cv_t<_Tp>>;

// we define the trait as alias, so users cannot specialize it (they should specialize the variable template instead)
template <class _Tp>
using is_floating_point = asc::std::bool_constant<is_floating_point_v<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_H
