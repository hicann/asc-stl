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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_END_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_END_H

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
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __find_end_detail {

// Minimal local traversal probes: a category probe against iterator_traits and
// a concept probe against a member iterator_concept, both SFINAE-friendly in
// C++17 mode.
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

template <class Iter>
using __iter_diff_t = typename iterator_traits<Iter>::difference_type;

}  // namespace __find_end_detail

template <class _BinaryPredicate, class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ForwardIterator1 __find_end(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred,
    forward_iterator_tag, forward_iterator_tag)
{
    // modeled after search algorithm
    _ForwardIterator1 __r = __last1;  // __last1 is the "default" answer
    if (__first2 == __last2) {
        return __r;
    }
    bool __searching = true;
    while (__searching) {
        while (__searching) {
            if (__first1 == __last1)  // if source exhausted return last correct answer
            {
                // return __r; //    (or __last1 if never found)
                __searching = false;
                break;
            }
            if (__pred(*__first1, *__first2)) {
                break;
            }
            ++__first1;
        }
        // *__first1 matches *__first2, now match elements after here
        _ForwardIterator1 __m1 = __first1;
        _ForwardIterator2 __m2 = __first2;
        while (__searching) {
            if (++__m2 == __last2) {  // Pattern exhausted, record answer and search for another one
                __r = __first1;
                ++__first1;
                break;
            }
            if (++__m1 == __last1)  // Source exhausted, return last answer
            {
                // return __r;
                __searching = false;
                break;
            }
            if (!__pred(*__m1, *__m2))  // mismatch, restart with a new __first
            {
                ++__first1;
                break;
            }  // else there is a match, check next elements
        }
    }
    return __r;
}

template <class _BinaryPredicate, class _BidirectionalIterator1, class _BidirectionalIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _BidirectionalIterator1 __find_end(_BidirectionalIterator1 __first1,
    _BidirectionalIterator1 __last1, _BidirectionalIterator2 __first2, _BidirectionalIterator2 __last2,
    _BinaryPredicate __pred, bidirectional_iterator_tag, bidirectional_iterator_tag)
{
    // modeled after search algorithm (in reverse)
    if (__first2 == __last2) {
        return __last1;  // Everything matches an empty sequence
    }
    _BidirectionalIterator1 __l1 = __last1;
    _BidirectionalIterator2 __l2 = __last2;
    --__l2;
    while (true) {
        // Find last element in sequence 1 that matches *(__last2-1), with a minimum of loop checks
        while (true) {
            if (__first1 == __l1)  // return __last1 if no element matches *__first2
            {
                return __last1;
            }
            if (__pred(*--__l1, *__l2)) {
                break;
            }
        }
        // *__l1 matches *__l2, now match elements before here
        _BidirectionalIterator1 __m1 = __l1;
        _BidirectionalIterator2 __m2 = __l2;
        while (true) {
            if (__m2 == __first2)  // If pattern exhausted, __m1 is the answer (works for 1 element pattern)
            {
                return __m1;
            }
            if (__m1 == __first1)  // Otherwise if source exhausted, pattern not found
            {
                return __last1;
            }
            if (!__pred(*--__m1, *--__m2))  // if there is a mismatch, restart with a new __l1
            {
                break;
            }  // else there is a match, check next elements
        }
    }
}

template <class _BinaryPredicate, class _RandomAccessIterator1, class _RandomAccessIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _RandomAccessIterator1 __find_end(_RandomAccessIterator1 __first1,
    _RandomAccessIterator1 __last1, _RandomAccessIterator2 __first2, _RandomAccessIterator2 __last2,
    _BinaryPredicate __pred, random_access_iterator_tag, random_access_iterator_tag)
{
    // Take advantage of knowing source and pattern lengths.  Stop short when source is smaller than pattern
    __find_end_detail::__iter_diff_t<_RandomAccessIterator2> __len2 = __last2 - __first2;
    if (__len2 == 0) {
        return __last1;
    }
    __find_end_detail::__iter_diff_t<_RandomAccessIterator1> __len1 = __last1 - __first1;
    if (__len1 < __len2) {
        return __last1;
    }
    const _RandomAccessIterator1 __s = __first1 + (__len2 - 1);  // End of pattern match can't go before here
    _RandomAccessIterator1 __l1 = __last1;
    _RandomAccessIterator2 __l2 = __last2;
    --__l2;
    while (true) {
        while (true) {
            if (__s == __l1) {
                return __last1;
            }
            if (__pred(*--__l1, *__l2)) {
                break;
            }
        }
        _RandomAccessIterator1 __m1 = __l1;
        _RandomAccessIterator2 __m2 = __l2;
        while (true) {
            if (__m2 == __first2) {
                return __m1;
            }
            // no need to check range on __m1 because __s guarantees we have enough source
            if (!__pred(*--__m1, *--__m2)) {
                break;
            }
        }
    }
}

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ForwardIterator1 find_end(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    return ::asc::std::__find_end<add_lvalue_reference_t<_BinaryPredicate>>(__first1, __last1, __first2, __last2,
        __pred, __find_end_detail::__iterator_traits_category_or_concept_t<_ForwardIterator1>{},
        __find_end_detail::__iterator_traits_category_or_concept_t<_ForwardIterator2>{});
}

template <class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _ForwardIterator1 find_end(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2)
{
    return ::asc::std::find_end(__first1, __last1, __first2, __last2, __equal_to{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_END_H
