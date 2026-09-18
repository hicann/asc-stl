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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_IS_PERMUTATION_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_IS_PERMUTATION_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr bool is_permutation(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _BinaryPredicate __pred)
{
    //  shorten sequences as much as possible by lopping of any equal prefix
    for (; __first1 != __last1; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            break;
        }
    }
    if (__first1 == __last1) {
        return true;
    }

    //  __first1 != __last1 && *__first1 != *__first2
    using _Diff1 = __iter_diff_t<_ForwardIterator1>;
    _Diff1 __l1 = ::asc::std::distance(__first1, __last1);
    if (__l1 == _Diff1(1)) {
        return false;
    }
    _ForwardIterator2 __last2 = ::asc::std::next(__first2, __l1);
    // For each element in [f1, l1) see if there are the same number of
    //    equal elements in [f2, l2)
    bool __result = true;
    for (_ForwardIterator1 __i = __first1; __i != __last1; ++__i) {
        //  Have we already counted the number of *__i in [f1, l1)?
        _ForwardIterator1 __match = __first1;
        for (; __match != __i; ++__match) {
            if (__pred(*__match, *__i)) {
                break;
            }
        }
        if (__match == __i) {
            // Count number of *__i in [f2, l2)
            _Diff1 __c2 = 0;
            for (_ForwardIterator2 __j = __first2; __j != __last2; ++__j) {
                if (__pred(*__i, *__j)) {
                    ++__c2;
                }
            }
            if (__c2 == 0) {
                __result = false;
                break;
            }
            // Count number of *__i in [__i, l1) (we can start with 1)
            _Diff1 __c1 = 1;
            for (_ForwardIterator1 __j = ::asc::std::next(__i); __j != __last1; ++__j) {
                if (__pred(*__i, *__j)) {
                    ++__c1;
                }
            }
            if (__c1 != __c2) {
                __result = false;
                break;
            }
        }
    }
    return __result;
}

template <class _ForwardIterator1, class _ForwardIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool is_permutation(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2)
{
    return ::asc::std::is_permutation(__first1, __last1, __first2, __equal_to{});
}

template <class _BinaryPredicate, class _ForwardIterator1, class _ForwardIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred, forward_iterator_tag,
    forward_iterator_tag)
{
    //  shorten sequences as much as possible by lopping of any equal prefix
    for (; __first1 != __last1 && __first2 != __last2; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            break;
        }
    }
    if (__first1 == __last1) {
        return __first2 == __last2;
    } else if (__first2 == __last2) {
        return false;
    }
    using _Diff1 = __iter_diff_t<_ForwardIterator1>;
    _Diff1 __l1 = ::asc::std::distance(__first1, __last1);
    using _Diff2 = __iter_diff_t<_ForwardIterator2>;
    _Diff2 __l2 = ::asc::std::distance(__first2, __last2);
    if (__l1 != __l2) {
        return false;
    }
    // For each element in [f1, l1) see if there are the same number of
    //    equal elements in [f2, l2)
    bool __result = true;
    for (_ForwardIterator1 __i = __first1; __i != __last1; ++__i) {
        //  Have we already counted the number of *__i in [f1, l1)?
        _ForwardIterator1 __match = __first1;
        for (; __match != __i; ++__match) {
            if (__pred(*__match, *__i)) {
                break;
            }
        }
        if (__match == __i) {
            // Count number of *__i in [f2, l2)
            _Diff1 __c2 = 0;
            for (_ForwardIterator2 __j = __first2; __j != __last2; ++__j) {
                if (__pred(*__i, *__j)) {
                    ++__c2;
                }
            }
            if (__c2 == 0) {
                __result = false;
                break;
            }
            // Count number of *__i in [__i, l1) (we can start with 1)
            _Diff1 __c1 = 1;
            for (_ForwardIterator1 __j = ::asc::std::next(__i); __j != __last1; ++__j) {
                if (__pred(*__i, *__j)) {
                    ++__c1;
                }
            }
            if (__c1 != __c2) {
                __result = false;
                break;
            }
        }
    }
    return __result;
}

// The random-access overload keeps its parameter list verbatim from the reference:
// the element types of __last1 and __first2 are intentionally interleaved.
template <class _BinaryPredicate, class _RandomAccessIterator1, class _RandomAccessIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __is_permutation(_RandomAccessIterator1 __first1,
    _RandomAccessIterator2 __last1, _RandomAccessIterator1 __first2, _RandomAccessIterator2 __last2,
    _BinaryPredicate __pred, random_access_iterator_tag, random_access_iterator_tag)
{
    if (__last1 - __first1 != __last2 - __first2) {
        return false;
    }
    return ::asc::std::is_permutation<_RandomAccessIterator1, _RandomAccessIterator2,
        add_lvalue_reference_t<_BinaryPredicate>>(__first1, __last1, __first2, __pred);
}

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr bool is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    return ::asc::std::__is_permutation<add_lvalue_reference_t<_BinaryPredicate>>(__first1, __last1, __first2, __last2,
        __pred, __iterator_category_type<_ForwardIterator1>{}, __iterator_category_type<_ForwardIterator2>{});
}

template <class _ForwardIterator1, class _ForwardIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool is_permutation(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2)
{
    return ::asc::std::__is_permutation(__first1, __last1, __first2, __last2, __equal_to{},
        __iterator_category_type<_ForwardIterator1>{}, __iterator_category_type<_ForwardIterator2>{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_IS_PERMUTATION_H
