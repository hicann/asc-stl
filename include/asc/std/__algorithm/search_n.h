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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_N_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_N_H

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
#include <asc/std/__utility/convert_to_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __search_n_detail {

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

}  // namespace __search_n_detail

template <class _BinaryPredicate, class _ForwardIterator, class _Size, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator __search_n(_ForwardIterator __first, _ForwardIterator __last,
    _Size __count, const _Tp& __value_, _BinaryPredicate __pred, forward_iterator_tag)
{
    if (__count <= 0) {
        return __first;
    }
    while (true) {
        // Find first element in sequence that matches __value_, with a minimum of loop checks
        while (true) {
            if (__first == __last)  // return __last if no element matches __value_
            {
                return __last;
            }
            if (__pred(*__first, __value_)) {
                break;
            }
            ++__first;
        }
        // *__first matches __value_, now match elements after here
        _ForwardIterator __m = __first;
        _Size __c(0);
        while (true) {
            if (++__c == __count)  // If pattern exhausted, __first is the answer (works for 1 element pattern)
            {
                return __first;
            }
            if (++__m == __last)  // Otherwise if source exhausted, pattern not found
            {
                return __last;
            }
            if (!__pred(*__m, __value_))  // if there is a mismatch, restart with a new __first
            {
                __first = __m;
                ++__first;
                break;
            }  // else there is a match, check next elements
        }
    }
}

template <class _BinaryPredicate, class _RandomAccessIterator, class _Size, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _RandomAccessIterator __search_n(_RandomAccessIterator __first,
    _RandomAccessIterator __last, _Size __count, const _Tp& __value_, _BinaryPredicate __pred,
    random_access_iterator_tag)
{
    if (__count <= 0) {
        return __first;
    }
    _Size __len = static_cast<_Size>(__last - __first);
    if (__len < __count) {
        return __last;
    }
    const _RandomAccessIterator __s = __last - (__count - 1);  // Start of pattern match can't go beyond here
    while (true) {
        // Find first element in sequence that matches __value_, with a minimum of loop checks
        while (true) {
            if (__first >= __s)  // return __last if no element matches __value_
            {
                return __last;
            }
            if (__pred(*__first, __value_)) {
                break;
            }
            ++__first;
        }
        // *__first matches __value_, now match elements after here
        _RandomAccessIterator __m = __first;
        _Size __c(0);
        while (true) {
            if (++__c == __count)  // If pattern exhausted, __first is the answer (works for 1 element pattern)
            {
                return __first;
            }
            ++__m;                        // no need to check range on __m because __s guarantees we have enough source
            if (!__pred(*__m, __value_))  // if there is a mismatch, restart with a new __first
            {
                __first = __m;
                ++__first;
                break;
            }  // else there is a match, check next elements
        }
    }
}

template <class _ForwardIterator, class _Size, class _Tp, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator search_n(
    _ForwardIterator __first, _ForwardIterator __last, _Size __count, const _Tp& __value_, _BinaryPredicate __pred)
{
    return ::asc::std::__search_n<add_lvalue_reference_t<_BinaryPredicate>>(__first, __last,
        __convert_to_integral(__count), __value_, __pred,
        __search_n_detail::__iterator_traits_category_or_concept_t<_ForwardIterator>());
}

template <class _ForwardIterator, class _Size, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator search_n(
    _ForwardIterator __first, _ForwardIterator __last, _Size __count, const _Tp& __value_)
{
    return ::asc::std::search_n(__first, __last, __convert_to_integral(__count), __value_, __equal_to{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SEARCH_N_H
