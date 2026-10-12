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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_COMMON_REFERENCE_WITH_H
#define CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_COMMON_REFERENCE_WITH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/copy_cv.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T, class U>
concept common_reference_with = same_as<common_reference_t<T, U>, common_reference_t<U, T>> &&
    convertible_to<T, common_reference_t<T, U>> && convertible_to<U, common_reference_t<T, U>>;
#else
template <class T, class U, class = void>
inline constexpr bool __common_reference_with_impl = false;

template <class T, class U>
inline constexpr bool __common_reference_with_impl<T, U, void_t<common_reference_t<T, U>, common_reference_t<U, T>>> =
    is_same_v<common_reference_t<T, U>, common_reference_t<U, T>> &&
    is_same_v<common_reference_t<U, T>, common_reference_t<T, U>> && is_convertible_v<T, common_reference_t<T, U>> &&
    is_convertible_v<U, common_reference_t<T, U>>;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_COMMON_REFERENCE_WITH_H
