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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_ITERATOR_CONCEPT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_ITERATOR_CONCEPT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
template <class Iter, class = void>
inline constexpr bool __has_explicit_iterator_concept = false;
template <class Iter>
inline constexpr bool __has_explicit_iterator_concept<Iter, void_t<typename iterator_traits<Iter>::iterator_concept>> =
    true;

// Prefer the explicit tag, otherwise classify through the shared iterator
// predicates. Both language modes and Device use the same chain.
template <class _IterMaybeQualified>
CANN_ASC_STL_API constexpr auto __get_iterator_concept()
{
    using _Iter = remove_cvref_t<_IterMaybeQualified>;

    if constexpr (__has_explicit_iterator_concept<_Iter>) {
        return typename iterator_traits<_Iter>::iterator_concept();
    } else if constexpr (contiguous_iterator<_Iter>) {
        return contiguous_iterator_tag();
    } else if constexpr (random_access_iterator<_Iter>) {
        return random_access_iterator_tag();
    } else if constexpr (bidirectional_iterator<_Iter>) {
        return bidirectional_iterator_tag();
    } else if constexpr (forward_iterator<_Iter>) {
        return forward_iterator_tag();
    } else if constexpr (input_iterator<_Iter>) {
        return input_iterator_tag();
    } else {
        return typename iterator_traits<_Iter>::iterator_category();
    }
}

template <class _Iter>
using __iterator_concept = decltype(__get_iterator_concept<_Iter>());
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_ITERATOR_CONCEPT_H
