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

#ifndef CANN_ASC_STL_ASC_STD___CONCEPTS_ASSIGNABLE_H
#define CANN_ASC_STL_ASC_STD___CONCEPTS_ASSIGNABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class Lhs, class Rhs>
concept assignable_from = is_lvalue_reference_v<Lhs> &&
    common_reference_with<__make_const_lvalue_ref<Lhs>, __make_const_lvalue_ref<Rhs>> && requires(Lhs lhs, Rhs&& rhs) {
        { lhs = ::asc::std::forward<Rhs>(rhs) } -> same_as<Lhs>;  // NOLINT(build/include_what_you_use)
    };
#else
template <class Lhs, class Rhs, class = void>
inline constexpr bool __assignable_from_impl = false;

template <class Lhs, class Rhs>
inline constexpr bool __assignable_from_impl<Lhs, Rhs,
    void_t<__make_const_lvalue_ref<Lhs>, __make_const_lvalue_ref<Rhs>,
        decltype(::asc::std::declval<Lhs>() = ::asc::std::declval<Rhs>())>> = is_lvalue_reference_v<Lhs> &&
    __common_reference_with_impl<__make_const_lvalue_ref<Lhs>, __make_const_lvalue_ref<Rhs>> &&
    is_same_v<Lhs, decltype(::asc::std::declval<Lhs>() = ::asc::std::declval<Rhs>())> &&
    is_same_v<decltype(::asc::std::declval<Lhs>() = ::asc::std::declval<Rhs>()), Lhs>;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_ASSIGNABLE_H
