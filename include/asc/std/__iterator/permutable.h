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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_PERMUTABLE_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_PERMUTABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_swap.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Iterator>
concept permutable = forward_iterator<_Iterator> && indirectly_movable_storable<_Iterator, _Iterator> &&
    indirectly_swappable<_Iterator, _Iterator>;

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Iterator>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__permutable_,
    requires()(requires(forward_iterator<_Iterator>), requires(indirectly_movable_storable<_Iterator, _Iterator>),
        requires(indirectly_swappable<_Iterator, _Iterator>)));

template <class _Iterator>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT permutable = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__permutable_, _Iterator);

#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_PERMUTABLE_H
