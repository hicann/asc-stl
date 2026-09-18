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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_ITERATOR_CONCEPT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_ITERATOR_CONCEPT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/remove_cvref.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class _IterMaybeQualified>
CANN_ASC_STL_API constexpr auto __get_iterator_concept()
{
    using _Iter = remove_cvref_t<_IterMaybeQualified>;

    if constexpr (contiguous_iterator<_Iter>) {
        return contiguous_iterator_tag();
    } else if constexpr (random_access_iterator<_Iter>) {
        return random_access_iterator_tag();
    } else if constexpr (bidirectional_iterator<_Iter>) {
        return bidirectional_iterator_tag();
    } else if constexpr (forward_iterator<_Iter>) {
        return forward_iterator_tag();
    } else if constexpr (input_iterator<_Iter>) {
        return input_iterator_tag();
    }
}

template <class _Iter>
using __iterator_concept = decltype(__get_iterator_concept<_Iter>());

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES
#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_RANGES_ITERATOR_CONCEPT_H
