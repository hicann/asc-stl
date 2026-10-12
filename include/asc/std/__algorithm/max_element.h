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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MAX_ELEMENT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MAX_ELEMENT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __max_element_detail {

// Minimal local equivalent of the input-traversal probe used by the migrated
// implementation: a category probe against iterator_traits and a concept probe
// against a member iterator_concept, both SFINAE-friendly in C++17 mode.
template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_category_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool
    __has_iterator_category_convertible_to<Iter, Tag, void_t<typename iterator_traits<Iter>::iterator_category>> =
        is_convertible_v<typename iterator_traits<Iter>::iterator_category, Tag>;

template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_concept_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool __has_iterator_concept_convertible_to<Iter, Tag, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, Tag>;

template <class Iter>
inline constexpr bool __has_input_traversal = __has_iterator_category_convertible_to<Iter, input_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, input_iterator_tag>;

}  // namespace __max_element_detail

template <class _Compare, class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __max_element(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    static_assert(__max_element_detail::__has_input_traversal<_ForwardIterator>,
        "::asc::std::max_element requires a ForwardIterator");
    if (__first != __last) {
        _ForwardIterator __i = __first;
        while (++__i != __last) {
            if (__comp(*__first, *__i)) {
                __first = __i;
            }
        }
    }
    return __first;
}

template <class _ForwardIterator, class _Compare>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ForwardIterator max_element(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    return ::asc::std::__max_element<__comp_ref_type<_Compare>>(__first, __last, __comp);
}

template <class _ForwardIterator>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ForwardIterator max_element(
    _ForwardIterator __first, _ForwardIterator __last)
{
    return ::asc::std::max_element(__first, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MAX_ELEMENT_H
