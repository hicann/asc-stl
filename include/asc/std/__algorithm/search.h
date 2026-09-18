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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_SEARCH_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_SEARCH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _BinaryPredicate, class _ForwardIterator1, class _ForwardIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_ForwardIterator1, _ForwardIterator1> __search(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred,
    forward_iterator_tag, forward_iterator_tag)
{
    if (__first2 == __last2) {
        return ::asc::std::make_pair(__first1, __first1);  // Everything matches an empty sequence
    }
    while (true) {
        // Find first element in sequence 1 that matches *__first2, with a minimum of loop checks
        while (true) {
            if (__first1 == __last1)  // return __last1 if no element matches *__first2
            {
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
            if (++__m2 == __last2)  // If pattern exhausted, __first1 is the answer (works for 1 element pattern)
            {
                return ::asc::std::make_pair(__first1, __m1);
            }
            if (++__m1 == __last1)  // Otherwise if source exhausted, pattern not found
            {
                return ::asc::std::make_pair(__last1, __last1);
            }
            if (!__pred(*__m1, *__m2))  // if there is a mismatch, restart with a new __first1
            {
                ++__first1;
                break;
            }  // else there is a match, check next elements
        }
    }
}

template <class _BinaryPredicate, class _RandomAccessIterator1, class _RandomAccessIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_RandomAccessIterator1, _RandomAccessIterator1> __search(
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

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator1 search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    return ::asc::std::__search<add_lvalue_reference_t<_BinaryPredicate>>(__first1, __last1, __first2, __last2, __pred,
        __iterator_traits_category_or_concept_t<_ForwardIterator1>(),
        __iterator_traits_category_or_concept_t<_ForwardIterator2>())
        .first;
}

template <class _ForwardIterator1, class _ForwardIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator1 search(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2)
{
    return ::asc::std::search(__first1, __last1, __first2, __last2, __equal_to{});
}

template <class _ForwardIterator, class _Searcher>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator search(
    _ForwardIterator __f, _ForwardIterator __l, const _Searcher& __s)
{
    return __s(__f, __l).first;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_SEARCH_H
