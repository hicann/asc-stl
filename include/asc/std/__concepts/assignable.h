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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_ASSIGNABLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_ASSIGNABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Lhs, class _Rhs>
concept assignable_from = is_lvalue_reference_v<_Lhs> &&
    common_reference_with<__make_const_lvalue_ref<_Lhs>, __make_const_lvalue_ref<_Rhs>> &&
    requires(_Lhs __lhs, _Rhs&& __rhs) {
        { __lhs = ::asc::std::forward<_Rhs>(__rhs) } -> same_as<_Lhs>;  // NOLINT(build/include_what_you_use)
    };

#else

template <class _Lhs, class _Rhs, class = void>
inline constexpr bool __assignable_from_impl = false;

template <class _Lhs, class _Rhs>
inline constexpr bool __assignable_from_impl<_Lhs, _Rhs,
    void_t<__make_const_lvalue_ref<_Lhs>, __make_const_lvalue_ref<_Rhs>,
        decltype(::asc::std::declval<_Lhs>() = ::asc::std::declval<_Rhs>())>> = is_lvalue_reference_v<_Lhs> &&
    common_reference_with<__make_const_lvalue_ref<_Lhs>, __make_const_lvalue_ref<_Rhs>> &&
    same_as<_Lhs, decltype(::asc::std::declval<_Lhs>() = ::asc::std::declval<_Rhs>())>;

template <class _Lhs, class _Rhs>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT assignable_from = __assignable_from_impl<_Lhs, _Rhs>;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_ASSIGNABLE_H
