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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_COMMON_WITH_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_COMMON_WITH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp, class _Up>
concept common_with = same_as<common_type_t<_Tp, _Up>, common_type_t<_Up, _Tp>> &&
    requires {
        static_cast<common_type_t<_Tp, _Up>>(::asc::std::declval<_Tp>());
        static_cast<common_type_t<_Tp, _Up>>(::asc::std::declval<_Up>());
    } && common_reference_with<add_lvalue_reference_t<const _Tp>, add_lvalue_reference_t<const _Up>> &&
    common_reference_with<add_lvalue_reference_t<common_type_t<_Tp, _Up>>,
        common_reference_t<add_lvalue_reference_t<const _Tp>, add_lvalue_reference_t<const _Up>>>;

#else

template <class _Tp, class _Up, class = void>
inline constexpr bool __common_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __common_with_impl<_Tp, _Up,
    void_t<common_type_t<_Tp, _Up>, common_type_t<_Up, _Tp>,
        decltype(static_cast<common_type_t<_Tp, _Up>>(::asc::std::declval<_Tp>())),
        decltype(static_cast<common_type_t<_Tp, _Up>>(::asc::std::declval<_Up>())),
        common_reference_t<add_lvalue_reference_t<const _Tp>, add_lvalue_reference_t<const _Up>>>> =
    same_as<common_type_t<_Tp, _Up>, common_type_t<_Up, _Tp>> &&
    common_reference_with<add_lvalue_reference_t<const _Tp>, add_lvalue_reference_t<const _Up>> &&
    common_reference_with<add_lvalue_reference_t<common_type_t<_Tp, _Up>>,
        common_reference_t<add_lvalue_reference_t<const _Tp>, add_lvalue_reference_t<const _Up>>>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT common_with = __common_with_impl<_Tp, _Up>;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_COMMON_WITH_H
