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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_CLASS_OR_ENUM_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_CLASS_OR_ENUM_H

#include <asc/std/detail/__config>

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_union.h>
#include <asc/std/__type_traits/remove_cvref.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __class_or_enum = is_class_v<_Tp> || is_union_v<_Tp> || is_enum_v<_Tp>;
#else
inline constexpr bool __class_or_enum = is_class_v<_Tp> || is_union_v<_Tp> || is_enum_v<_Tp>;
#endif

template <class _Tp>
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
concept __workaround_52970 = is_class_v<remove_cvref_t<_Tp>> || is_union_v<remove_cvref_t<_Tp>>;
#else
inline constexpr bool __workaround_52970 = is_class_v<remove_cvref_t<_Tp>> || is_union_v<remove_cvref_t<_Tp>>;
#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_CLASS_OR_ENUM_H
