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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_INDIRECTLY_COMPARABLE_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_INDIRECTLY_COMPARABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Iter1, class _Iter2, class _BinaryPred, class _Proj1 = identity, class _Proj2 = identity>
concept indirectly_comparable =
    indirect_binary_predicate<_BinaryPred, projected<_Iter1, _Proj1>, projected<_Iter2, _Proj2>>;

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Iter1, class _Iter2, class _BinaryPred, class _Proj1, class _Proj2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_comparable_,
    requires()(requires(indirect_binary_predicate<_BinaryPred, projected<_Iter1, _Proj1>, projected<_Iter2, _Proj2>>)));

template <class _Iter1, class _Iter2, class _BinaryPred, class _Proj1 = identity, class _Proj2 = identity>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_comparable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_comparable_, _Iter1, _Iter2, _BinaryPred, _Proj1, _Proj2);

#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_INDIRECTLY_COMPARABLE_H
