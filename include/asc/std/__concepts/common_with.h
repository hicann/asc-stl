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

#ifndef CANN_ASC_STL_ASC_STD___CONCEPTS_COMMON_WITH_H
#define CANN_ASC_STL_ASC_STD___CONCEPTS_COMMON_WITH_H

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
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T, class U>
concept common_with = same_as<common_type_t<T, U>, common_type_t<U, T>> &&
    requires {
        static_cast<common_type_t<T, U>>(::asc::std::declval<T>());
        static_cast<common_type_t<T, U>>(::asc::std::declval<U>());
    } && common_reference_with<add_lvalue_reference_t<const T>, add_lvalue_reference_t<const U>> &&
    common_reference_with<add_lvalue_reference_t<common_type_t<T, U>>,
        common_reference_t<add_lvalue_reference_t<const T>, add_lvalue_reference_t<const U>>>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_COMMON_WITH_H
