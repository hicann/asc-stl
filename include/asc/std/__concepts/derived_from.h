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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_DERIVED_FROM_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_DERIVED_FROM_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_convertible.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Derived, class _Base>
concept derived_from =
    is_base_of_v<_Base, _Derived> && is_convertible_v<const volatile _Derived*, const volatile _Base*>;

#else

template <class _Derived, class _Base>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT derived_from = is_base_of_v<_Base, _Derived> &&
    is_convertible_v<add_pointer_t<const volatile _Derived>, add_pointer_t<const volatile _Base> >;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_DERIVED_FROM_H
