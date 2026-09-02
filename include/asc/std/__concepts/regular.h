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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_REGULAR_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_REGULAR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/semiregular.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

// [concept.object]

template <class _Tp>
concept regular = semiregular<_Tp> && equality_comparable<_Tp>;

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

// [concept.object]

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __regular_, requires()(requires(semiregular<_Tp>), requires(equality_comparable<_Tp>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT regular = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__regular_, _Tp);

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_REGULAR_H
