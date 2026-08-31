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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_FOLD_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_FOLD_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// Use fold expressions when possible to implement __fold_and[_v] and
// __fold_or[_v].
template <bool... _Preds>
inline constexpr bool __fold_and_v = (_Preds && ...);

template <bool... _Preds>
inline constexpr bool __fold_or_v = (_Preds || ...);

template <bool... _Preds>
using __fold_and = bool_constant<bool((_Preds && ...))>;  // cast to bool to avoid error from gcc < 8

template <bool... _Preds>
using __fold_or = bool_constant<bool((_Preds || ...))>;  // cast to bool to avoid error from gcc < 8

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_FOLD_H
