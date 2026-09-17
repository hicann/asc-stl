/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_SET_INTERSECTION_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_SET_INTERSECTION_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _InIter1, class _InIter2, class _OutIter>
struct __set_intersection_result {
    _InIter1 __in1_;
    _InIter2 __in2_;
    _OutIter __out_;

    // need a constructor as C++03 aggregate init is hard
    CANN_ASC_STL_API constexpr __set_intersection_result(
        _InIter1&& __in_iter1, _InIter2&& __in_iter2, _OutIter&& __out_iter)
        : __in1_(::asc::std::move(__in_iter1)),
          __in2_(::asc::std::move(__in_iter2)),
          __out_(::asc::std::move(__out_iter))
    {}
};
template <class _AlgPolicy, class _Compare, class _InIter1, class _Sent1, class _InIter2, class _Sent2, class _OutIter>
CANN_ASC_STL_API constexpr __set_intersection_result<_InIter1, _InIter2, _OutIter> __set_intersection(
    _InIter1 __first1, _Sent1 __last1, _InIter2 __first2, _Sent2 __last2, _OutIter __result, _Compare&& __comp)
{
    while (__first1 != __last1 && __first2 != __last2) {
        if (__comp(*__first1, *__first2)) {
            ++__first1;
        } else {
            if (!__comp(*__first2, *__first1)) {
                *__result = *__first1;
                ++__result;
                ++__first1;
            }
            ++__first2;
        }
    }

    return __set_intersection_result<_InIter1, _InIter2, _OutIter>(
        _IterOps<_AlgPolicy>::next(::asc::std::move(__first1), ::asc::std::move(__last1)),
        _IterOps<_AlgPolicy>::next(::asc::std::move(__first2), ::asc::std::move(__last2)), ::asc::std::move(__result));
}
template <class _InputIterator1, class _InputIterator2, class _OutputIterator, class _Compare>
CANN_ASC_STL_API constexpr _OutputIterator set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _OutputIterator __result, _Compare __comp)
{
    return ::asc::std::__set_intersection<_ClassicAlgPolicy, __comp_ref_type<_Compare>>(::asc::std::move(__first1),
        ::asc::std::move(__last1), ::asc::std::move(__first2), ::asc::std::move(__last2), ::asc::std::move(__result),
        __comp)
        .__out_;
}
template <class _InputIterator1, class _InputIterator2, class _OutputIterator>
CANN_ASC_STL_API constexpr _OutputIterator set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _OutputIterator __result)
{
    return ::asc::std::__set_intersection<_ClassicAlgPolicy>(::asc::std::move(__first1), ::asc::std::move(__last1),
        ::asc::std::move(__first2), ::asc::std::move(__last2),
        ::asc::std::move(__result),  // NOLINT(build/include_what_you_use)
        __less{})                    // NOLINT(build/include_what_you_use)
        .__out_;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_SET_INTERSECTION_H
