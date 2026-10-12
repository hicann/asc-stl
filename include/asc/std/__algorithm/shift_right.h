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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SHIFT_RIGHT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SHIFT_RIGHT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/move.h>
#include <asc/std/__algorithm/move_backward.h>
#include <asc/std/__algorithm/swap_ranges.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __shift_right_detail {

// Minimal local equivalents of the traversal probes used by the migrated
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

template <class Iter>
inline constexpr bool __has_forward_traversal = __has_iterator_category_convertible_to<Iter, forward_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, forward_iterator_tag>;

template <class Iter>
inline constexpr bool __has_bidirectional_traversal =
    __has_iterator_category_convertible_to<Iter, bidirectional_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, bidirectional_iterator_tag>;

template <class Iter>
inline constexpr bool __has_random_access_traversal =
    __has_iterator_category_convertible_to<Iter, random_access_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, random_access_iterator_tag>;

template <class Iter>
inline constexpr bool __has_contiguous_traversal =
    __has_iterator_category_convertible_to<Iter, contiguous_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, contiguous_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __has_member_iterator_concept = false;

template <class Iter>
inline constexpr bool __has_member_iterator_concept<Iter, void_t<typename Iter::iterator_concept>> = true;

// C++20 iterators do not always carry a C++17-compatible iterator_category;
// deduce the effective category from the maximum of iterator_concept and
// iterator_category, mirroring __iterator_traits_category_or_concept.
template <class Iter>
CANN_ASC_STL_API constexpr auto __iterator_traits_category_or_concept() noexcept
{
    if constexpr (!__has_member_iterator_concept<Iter>) {
        return typename iterator_traits<Iter>::iterator_category{};
    } else if constexpr (__has_contiguous_traversal<Iter>) {
        return contiguous_iterator_tag{};
    } else if constexpr (__has_random_access_traversal<Iter>) {
        return random_access_iterator_tag{};
    } else if constexpr (__has_bidirectional_traversal<Iter>) {
        return bidirectional_iterator_tag{};
    } else if constexpr (__has_forward_traversal<Iter>) {
        return forward_iterator_tag{};
    } else if constexpr (__has_input_traversal<Iter>) {
        return input_iterator_tag{};
    } else {
        return typename Iter::iterator_category{};
    }
}

template <class Iter>
using __iterator_traits_category_or_concept_t = decltype(__iterator_traits_category_or_concept<Iter>());

}  // namespace __shift_right_detail

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __shift_right(_ForwardIterator __first, _ForwardIterator __last,
    typename iterator_traits<_ForwardIterator>::difference_type __n, random_access_iterator_tag)
{
    decltype(__n) __d = __last - __first;
    if (__n >= __d) {
        return __last;
    }
    _ForwardIterator __m = __first + (__d - __n);
    return ::asc::std::move_backward(__first, __m, __last);
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __shift_right(_ForwardIterator __first, _ForwardIterator __last,
    typename iterator_traits<_ForwardIterator>::difference_type __n, bidirectional_iterator_tag)
{
    _ForwardIterator __m = __last;
    for (; __n > 0; --__n) {
        if (__m == __first) {
            return __last;
        }
        --__m;
    }
    return ::asc::std::move_backward(__first, __m, __last);
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __shift_right(_ForwardIterator __first, _ForwardIterator __last,
    typename iterator_traits<_ForwardIterator>::difference_type __n, forward_iterator_tag)
{
    _ForwardIterator __ret = __first;
    for (; __n > 0; --__n) {
        if (__ret == __last) {
            return __last;
        }
        ++__ret;
    }
    // An __n-element scratch space [__first, __ret) slides left to right; once
    // the leading edge reaches __last the remaining prefix is moved into place.
    _ForwardIterator __trail = __first;
    _ForwardIterator __lead = __ret;
    while (__trail != __ret) {
        if (__lead == __last) {
            ::asc::std::move(__first, __trail, __ret);
            return __ret;
        }
        ++__trail;
        ++__lead;
    }
    _ForwardIterator __mid = __first;
    while (true) {
        if (__lead == __last) {
            __trail = ::asc::std::move(__mid, __ret, __trail);
            ::asc::std::move(__first, __mid, __trail);
            return __ret;
        }
        ::asc::std::swap(*__mid, *__trail);  // NOLINT(build/include_what_you_use)
        ++__mid;
        ++__trail;
        ++__lead;
        if (__mid == __ret) {
            __mid = __first;
        }
    }
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator shift_right(
    _ForwardIterator __first, _ForwardIterator __last, typename iterator_traits<_ForwardIterator>::difference_type __n)
{
    if (__n == 0) {
        return __first;
    }
    using _IterCategory = __shift_right_detail::__iterator_traits_category_or_concept_t<_ForwardIterator>;
    return ::asc::std::__shift_right(__first, __last, __n, _IterCategory());
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SHIFT_RIGHT_H
