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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_H

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
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __search_detail {

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

}  // namespace __search_detail

template <class _BinaryPredicate, class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_API constexpr pair<_ForwardIterator1, _ForwardIterator1> __search(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred,
    forward_iterator_tag, forward_iterator_tag)
{
    if (__first2 == __last2) {
        return ::asc::std::make_pair(__first1, __first1);  // Everything matches an empty sequence
    }
    while (true) {
        // Find first element in sequence 1 that matches *__first2, with a minimum of loop checks
        while (true) {
            if (__first1 == __last1) {  // return __last1 if no element matches *__first2
                return ::asc::std::make_pair(__last1, __last1);
            }
            if (__pred(*__first1, *__first2)) {
                break;
            }
            ++__first1;
        }
        // *__first1 matches *__first2, now match elements after here
        _ForwardIterator1 __m1 = __first1;
        _ForwardIterator2 __m2 = __first2;
        while (true) {
            if (++__m2 == __last2) {  // If pattern exhausted, __first1 is the answer (works for 1 element pattern)
                return ::asc::std::make_pair(__first1, __m1);
            }
            if (++__m1 == __last1) {  // Otherwise if source exhausted, pattern not found
                return ::asc::std::make_pair(__last1, __last1);
            }
            if (!__pred(*__m1, *__m2)) {  // if there is a mismatch, restart with a new __first1
                ++__first1;
                break;
            }  // else there is a match, check next elements
        }
    }
}

template <class _BinaryPredicate, class _RandomAccessIterator1, class _RandomAccessIterator2>
CANN_ASC_STL_API constexpr pair<_RandomAccessIterator1, _RandomAccessIterator1> __search(
    _RandomAccessIterator1 __first1, _RandomAccessIterator1 __last1, _RandomAccessIterator2 __first2,
    _RandomAccessIterator2 __last2, _BinaryPredicate __pred, random_access_iterator_tag, random_access_iterator_tag)
{
    using _Diff1 = typename iterator_traits<_RandomAccessIterator1>::difference_type;
    using _Diff2 = typename iterator_traits<_RandomAccessIterator2>::difference_type;
    // Take advantage of knowing source and pattern lengths.  Stop short when source is smaller than pattern
    const _Diff2 __len2 = __last2 - __first2;
    if (__len2 == 0) {
        return ::asc::std::make_pair(__first1, __first1);
    }
    const _Diff1 __len1 = __last1 - __first1;
    if (__len1 < __len2) {
        return ::asc::std::make_pair(__last1, __last1);
    }
    const _RandomAccessIterator1 __s = __last1 - (__len2 - 1);  // Start of pattern match can't go beyond here

    while (true) {
        while (true) {
            if (__first1 == __s) {
                return ::asc::std::make_pair(__last1, __last1);
            }
            if (__pred(*__first1, *__first2)) {
                break;
            }
            ++__first1;
        }

        _RandomAccessIterator1 __m1 = __first1;
        _RandomAccessIterator2 __m2 = __first2;
        while (true) {
            if (++__m2 == __last2) {
                return ::asc::std::make_pair(__first1, __first1 + __len2);  // NOLINT(build/include_what_you_use)
            }
            ++__m1;  // no need to check range on __m1 because __s guarantees we have enough source
            if (!__pred(*__m1, *__m2)) {
                ++__first1;
                break;
            }
        }
    }
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
CANN_ASC_STL_API constexpr ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last,
    ForwardIterator2 pattern_first, ForwardIterator2 pattern_last, BinaryPredicate predicate)
{
    return ::asc::std::__search(first, last, pattern_first, pattern_last, predicate,
        __search_detail::__iterator_traits_category_or_concept_t<ForwardIterator1>(),
        __search_detail::__iterator_traits_category_or_concept_t<ForwardIterator2>())
        .first;
}

template <class ForwardIterator1, class ForwardIterator2>
CANN_ASC_STL_API constexpr ForwardIterator1 search(
    ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 pattern_first, ForwardIterator2 pattern_last)
{
    return ::asc::std::search(first, last, pattern_first, pattern_last, __equal_to{});
}

template <class ForwardIterator, class Searcher>
CANN_ASC_STL_API constexpr ForwardIterator search(ForwardIterator first, ForwardIterator last, const Searcher& searcher)
{
    return searcher(first, last).first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_H
