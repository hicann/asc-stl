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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_IS_PERMUTATION_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_IS_PERMUTATION_H

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
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __is_permutation_counts_match(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    using _Diff1 = typename iterator_traits<_ForwardIterator1>::difference_type;
    for (_ForwardIterator1 __i = __first1; __i != __last1; ++__i) {
        _ForwardIterator1 __match = __first1;
        for (; __match != __i && !__pred(*__match, *__i); ++__match) {
        }
        if (__match != __i) {
            continue;
        }
        _Diff1 __second_count = 0;
        for (_ForwardIterator2 __j = __first2; __j != __last2; ++__j) {
            if (__pred(*__i, *__j)) {
                ++__second_count;
            }
        }
        if (__second_count == 0) {
            return false;
        }
        _Diff1 __first_count = 1;
        for (_ForwardIterator1 __j = ::asc::std::next(__i); __j != __last1; ++__j) {
            if (__pred(*__i, *__j)) {
                ++__first_count;
            }
        }
        if (__first_count != __second_count) {
            return false;
        }
    }
    return true;
}

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_permutation(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _BinaryPredicate __pred)
{
    //  shorten sequences as much as possible by lopping off any equal prefix
    for (; __first1 != __last1; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            break;
        }
    }
    if (__first1 == __last1) {
        return true;
    }

    using _Diff1 = typename iterator_traits<_ForwardIterator1>::difference_type;
    _Diff1 __l1 = ::asc::std::distance(__first1, __last1);
    if (__l1 == _Diff1(1)) {
        return false;
    }
    _ForwardIterator2 __last2 = ::asc::std::next(__first2, __l1);
    return ::asc::std::__is_permutation_counts_match(__first1, __last1, __first2, __last2, __pred);
}

template <class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_permutation(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2)
{
    return ::asc::std::is_permutation(__first1, __last1, __first2, __equal_to{});
}

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __is_permutation_forward(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    //  shorten sequences as much as possible by lopping off any equal prefix
    for (; __first1 != __last1 && __first2 != __last2; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            break;
        }
    }
    if (__first1 == __last1) {
        return __first2 == __last2;
    }
    if (__first2 == __last2) {
        return false;
    }

    using _Diff1 = typename iterator_traits<_ForwardIterator1>::difference_type;
    _Diff1 __l1 = ::asc::std::distance(__first1, __last1);
    if (__l1 == _Diff1(1)) {
        return false;
    }
    using _Diff2 = typename iterator_traits<_ForwardIterator2>::difference_type;
    _Diff2 __l2 = ::asc::std::distance(__first2, __last2);
    if (__l1 != __l2) {
        return false;
    }

    return ::asc::std::__is_permutation_counts_match(__first1, __last1, __first2, __last2, __pred);
}

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_permutation(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    return ::asc::std::__is_permutation_forward(__first1, __last1, __first2, __last2, __pred);
}

template <class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_permutation(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2)
{
    return ::asc::std::__is_permutation_forward(__first1, __last1, __first2, __last2, __equal_to{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_IS_PERMUTATION_H
