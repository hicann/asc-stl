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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SET_SYMMETRIC_DIFFERENCE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SET_SYMMETRIC_DIFFERENCE_H

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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Internal result structure: packs the three end iterators, for reuse by the
// ranges entry.
template <class _InIter1, class _InIter2, class _OutIter>
struct __set_symmetric_difference_result {
    _InIter1 __in1_;
    _InIter2 __in2_;
    _OutIter __out_;

    CANN_ASC_STL_API constexpr __set_symmetric_difference_result(
        _InIter1&& __in_iter1, _InIter2&& __in_iter2, _OutIter&& __out_iter)
        : __in1_(::asc::std::move(__in_iter1)),
          __in2_(::asc::std::move(__in_iter2)),
          __out_(::asc::std::move(__out_iter))
    {}
};

// General internal implementation: sentinel parameters + single-point writes in
// the main loop + moving the tail as a whole. No policy-taking __copy variant is
// available here, so the tail is an equivalent inline loop.
template <class _AlgPolicy, class _Compare, class _InIter1, class _Sent1, class _InIter2, class _Sent2, class _OutIter>
CANN_ASC_STL_API constexpr __set_symmetric_difference_result<_InIter1, _InIter2, _OutIter> __set_symmetric_difference(
    _InIter1 __first1, _Sent1 __last1, _InIter2 __first2, _Sent2 __last2, _OutIter __result, _Compare&& __comp)
{
    bool __first_end_reached = true;
    while (__first1 != __last1) {
        if (__first2 == __last2) {
            __first_end_reached = false;
            break;
        }
        if (__comp(*__first1, *__first2)) {
            *__result = *__first1;
            ++__result;
            ++__first1;
        } else {
            if (__comp(*__first2, *__first1)) {
                *__result = *__first2;
                ++__result;
            } else {
                ++__first1;
            }
            ++__first2;
        }
    }

    if (__first_end_reached) {
        while (__first2 != __last2) {
            *__result = *__first2;
            ++__first2;
            ++__result;
        }
    } else {
        while (__first1 != __last1) {
            *__result = *__first1;
            ++__first1;
            ++__result;
        }
    }
    return __set_symmetric_difference_result<_InIter1, _InIter2, _OutIter>(
        ::asc::std::move(__first1), ::asc::std::move(__first2), ::asc::std::move(__result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
CANN_ASC_STL_API constexpr OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // CCE device side: moving the output iterator through the result structure
    // would attach a segment offset, so use a handwritten loop that returns
    // directly (same strategy as the device branch of set_difference).
    while (first1 != last1 && first2 != last2) {
        if (compare(*first1, *first2)) {
            *result++ = *first1++;
        } else if (compare(*first2, *first1)) {
            *result++ = *first2++;
        } else {
            ++first1;
            ++first2;
        }
    }
    while (first1 != last1) {
        *result++ = *first1++;
    }
    while (first2 != last2) {
        *result++ = *first2++;
    }
    return result;
#else
    return ::asc::std::__set_symmetric_difference<__classic_algorithm_iterator_operations, __comp_ref_type<Compare> >(
        ::asc::std::move(first1), ::asc::std::move(last1), ::asc::std::move(first2), ::asc::std::move(last2),
        ::asc::std::move(result), compare)  // NOLINT(build/include_what_you_use)
        .__out_;
#endif
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator set_symmetric_difference(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    return ::asc::std::set_symmetric_difference(first1, last1, first2, last2, result, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SET_SYMMETRIC_DIFFERENCE_H
