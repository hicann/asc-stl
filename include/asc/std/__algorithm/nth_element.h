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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_NTH_ELEMENT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_NTH_ELEMENT_H

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
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/min_element.h>
#include <asc/std/__algorithm/sort.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __nth_element_detail {

//  stable, 2-3 compares, 0-2 swaps; returns the number of swaps performed.
//  Inlined here because this tree's sort internals do not expose __sort3.
template <class _Compare, class _ForwardIterator>
CANN_ASC_STL_API constexpr unsigned __sort3(
    _ForwardIterator __x, _ForwardIterator __y, _ForwardIterator __z, _Compare __c)
{
    unsigned __r = 0;
    if (!__c(*__y, *__x)) {      // if x <= y
        if (!__c(*__z, *__y)) {  // if y <= z
            return __r;          // x <= y && y <= z
        }
        // x <= y && y > z
        ::asc::std::iter_swap(__y, __z);  // x <= z && y < z
        __r = 1;
        if (__c(*__y, *__x)) {                // if x > y
            ::asc::std::iter_swap(__x, __y);  // x < y && y <= z
            __r = 2;
        }
        return __r;  // x <= y && y < z
    }
    if (__c(*__z, *__y)) {                // x > y, if y > z
        ::asc::std::iter_swap(__x, __z);  // x < y && y < z
        return 1;
    }
    ::asc::std::iter_swap(__x, __y);      // x > y && y <= z
    __r = 1;                              // x < y && x <= z
    if (__c(*__z, *__y)) {                // if y > z
        ::asc::std::iter_swap(__y, __z);  // x <= y && y < z
        __r = 2;
    }
    return __r;
}  // x <= y && y <= z

//  assumes size > 0
template <class _Compare, class _BidirectionalIterator>
CANN_ASC_STL_API constexpr void __selection_sort(
    _BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp)
{
    _BidirectionalIterator __lm1 = __last;
    for (--__lm1; __first != __lm1; ++__first) {
        _BidirectionalIterator __i =
            ::asc::std::min_element(__first, __last, __comp);  // NOLINT(build/include_what_you_use)
        if (__i != __first) {
            ::asc::std::iter_swap(__first, __i);
        }
    }
}

}  // namespace __nth_element_detail

template <class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr bool __nth_element_find_guard(
    _RandomAccessIterator& __i, _RandomAccessIterator& __j, _RandomAccessIterator __m, _Compare __comp)
{
    //  manually guard downward moving __j against __i
    while (true) {
        if (__i == --__j) {
            return false;
        }
        if (__comp(*__j, *__m)) {
            return true;  // found guard for downward moving __j, now use unguarded partition
        }
    }
}

template <class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __nth_element(
    _RandomAccessIterator __first, _RandomAccessIterator __nth, _RandomAccessIterator __last, _Compare __comp)
{
    //  _Compare is known to be a reference type
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    const difference_type __limit = 7;
    while (true) {
        if (__nth == __last) {
            return;
        }
        difference_type __len = __last - __first;
        switch (__len) {
            case 0:
            case 1:
                return;
            case 2:
                if (__comp(*--__last, *__first)) {
                    ::asc::std::iter_swap(__first, __last);
                }
                return;
            case 3: {
                _RandomAccessIterator __m = __first;
                __nth_element_detail::__sort3<_Compare>(__first, ++__m, --__last, __comp);
                return;
            }
        }
        if (__len <= __limit) {
            __nth_element_detail::__selection_sort<_Compare>(__first, __last, __comp);
            return;
        }
        //  __len > __limit >= 3
        _RandomAccessIterator __m = __first + __len / 2;
        _RandomAccessIterator __lm1 = __last;
        unsigned __n_swaps = __nth_element_detail::__sort3<_Compare>(__first, __m, --__lm1, __comp);
        //  *__m is median
        //  partition [__first, __m) < *__m and *__m <= [__m, __last)
        //  (this inhibits tossing elements equivalent to __m around unnecessarily)
        _RandomAccessIterator __i = __first;
        _RandomAccessIterator __j = __lm1;
        //  j points beyond range to be tested, *__lm1 is known to be <= *__m
        //  The search going up is known to be guarded but the search coming down isn't.
        //  Prime the downward search with a guard.
        if (!__comp(*__i, *__m)) {  // if *__first == *__m
            //  *__first == *__m, *__first doesn't go in first part
            if (::asc::std::__nth_element_find_guard<_Compare>(__i, __j, __m, __comp)) {
                ::asc::std::iter_swap(__i, __j);
                ++__n_swaps;
            } else {
                //  *__first == *__m, *__m <= all other elements
                //  Partition instead into [__first, __i) == *__first and *__first < [__i, __last)
                ++__i;  // __first + 1
                __j = __last;
                if (!__comp(*__first, *--__j)) {  // we need a guard if *__first == *(__last-1)
                    while (true) {
                        if (__i == __j) {
                            return;  // [__first, __last) all equivalent elements
                        }
                        if (__comp(*__first, *__i)) {
                            ::asc::std::iter_swap(__i, __j);
                            ++__n_swaps;
                            ++__i;
                            break;
                        }
                        ++__i;
                    }
                }
                //  [__first, __i) == *__first and *__first < [__j, __last) and __j == __last - 1
                if (__i == __j) {
                    return;
                }
                while (true) {
                    while (!__comp(*__first, *__i)) {
                        ++__i;
                        CANN_ASC_STL_DETAIL_ASSERT(__i != __last,
                            "Would read out of bounds, does your comparator satisfy the strict-weak ordering "
                            "requirement?");
                    }
                    do {
                        CANN_ASC_STL_DETAIL_ASSERT(__j != __first,
                            "Would read out of bounds, does your comparator satisfy the strict-weak ordering "
                            "requirement?");
                        --__j;
                    } while (__comp(*__first, *__j));
                    if (__i >= __j) {
                        break;
                    }
                    ::asc::std::iter_swap(__i, __j);
                    ++__n_swaps;
                    ++__i;
                }
                //  [__first, __i) == *__first and *__first < [__i, __last)
                //  The first part is sorted,
                if (__nth < __i) {
                    return;
                }
                //  __nth_element the second part
                __first = __i;
                continue;
            }
        }
        ++__i;
        //  j points beyond range to be tested, *__lm1 is known to be <= *__m
        //  if not yet partitioned...
        if (__i < __j) {
            //  known that *(__i - 1) < *__m
            while (true) {
                //  __m still guards upward moving __i
                while (__comp(*__i, *__m)) {
                    ++__i;
                    CANN_ASC_STL_DETAIL_ASSERT(__i != __last,
                        "Would read out of bounds, does your comparator satisfy the strict-weak "
                        "ordering requirement?");
                }
                //  It is now known that a guard exists for downward moving __j
                do {
                    CANN_ASC_STL_DETAIL_ASSERT(__j != __first,
                        "Would read out of bounds, does your comparator satisfy the strict-weak "
                        "ordering requirement?");
                    --__j;
                } while (!__comp(*__j, *__m));
                if (__i >= __j) {
                    break;
                }
                ::asc::std::iter_swap(__i, __j);
                ++__n_swaps;
                //  It is known that __m != __j
                //  If __m just moved, follow it
                if (__m == __i) {
                    __m = __j;
                }
                ++__i;
            }
        }
        //  [__first, __i) < *__m and *__m <= [__i, __last)
        if (__i != __m && __comp(*__m, *__i)) {
            ::asc::std::iter_swap(__i, __m);
            ++__n_swaps;
        }
        //  [__first, __i) < *__i and *__i <= [__i+1, __last)
        if (__nth == __i) {
            return;
        }
        if (__n_swaps == 0) {
            //  We were given a perfectly partitioned sequence.  Coincidence?
            if (__nth < __i) {
                //  Check for [__first, __i) already sorted
                __j = __m = __first;
                while (true) {
                    if (++__j == __i) {
                        //  [__first, __i) sorted
                        return;
                    }
                    if (__comp(*__j, *__m)) {
                        //  not yet sorted, so sort
                        break;
                    }
                    __m = __j;
                }
            } else {
                //  Check for [__i, __last) already sorted
                __j = __m = __i;
                while (true) {
                    if (++__j == __last) {
                        //  [__i, __last) sorted
                        return;
                    }
                    if (__comp(*__j, *__m)) {
                        //  not yet sorted, so sort
                        break;
                    }
                    __m = __j;
                }
            }
        }
        //  __nth_element on range containing __nth
        if (__nth < __i) {
            __last = __i;
        } else {
            __first = ++__i;
        }
    }
}

template <class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void __nth_element_impl(
    _RandomAccessIterator __first, _RandomAccessIterator __nth, _RandomAccessIterator __last, _Compare& __comp)
{
    if (__nth == __last) {
        return;
    }
    ::asc::std::__nth_element<__comp_ref_type<_Compare>>(__first, __nth, __last, __comp);
}

template <class RandomAccessIterator, class Compare>
CANN_ASC_STL_API constexpr void nth_element(
    RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare compare)
{
    ::asc::std::__nth_element_impl(::asc::std::move(first), ::asc::std::move(nth), ::asc::std::move(last), compare);
}

template <class RandomAccessIterator>
CANN_ASC_STL_API constexpr void nth_element(
    RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last)
{
    ::asc::std::nth_element(::asc::std::move(first), ::asc::std::move(nth),  // NOLINT(build/include_what_you_use)
        ::asc::std::move(last), __less{});                                   // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_NTH_ELEMENT_H
