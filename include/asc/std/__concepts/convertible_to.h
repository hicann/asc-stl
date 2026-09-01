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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONVERTIBLE_TO_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONVERTIBLE_TO_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _From, class _To>
concept convertible_to = is_convertible_v<_From, _To> && requires { static_cast<_To>(declval<_From>()); };

#else

template <class _From, class _To, class = void>
struct __convertible_to_impl : false_type {};

template <class _From, class _To>
struct __convertible_to_impl<_From, _To, void_t<decltype(static_cast<_To>(declval<_From>()))> >
    : bool_constant<is_convertible_v<_From, _To> > {};

template <class _From, class _To>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT convertible_to = __convertible_to_impl<_From, _To>::value;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONVERTIBLE_TO_H
