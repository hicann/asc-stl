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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_SEARCH_N_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_SEARCH_N_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__utility/convert_to_integral.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _BinaryPredicate, class _ForwardIterator, class _Size, class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator __search_n(_ForwardIterator __first,
    _ForwardIterator __last, _Size __count, const _Tp& __value_, _BinaryPredicate __pred, forward_iterator_tag)
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
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _RandomAccessIterator __search_n(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Size __count, const _Tp& __value_,
    _BinaryPredicate __pred, random_access_iterator_tag)
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
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator search_n(
    _ForwardIterator __first, _ForwardIterator __last, _Size __count, const _Tp& __value_, _BinaryPredicate __pred)
{
    return ::asc::std::__search_n<add_lvalue_reference_t<_BinaryPredicate>>(__first, __last,
        __convert_to_integral(__count), __value_, __pred, __iterator_traits_category_or_concept_t<_ForwardIterator>());
}

template <class _ForwardIterator, class _Size, class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator search_n(
    _ForwardIterator __first, _ForwardIterator __last, _Size __count, const _Tp& __value_)
{
    return ::asc::std::search_n(__first, __last, __convert_to_integral(__count), __value_, __equal_to{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_SEARCH_N_H
