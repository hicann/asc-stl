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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_FIND_FIRST_OF_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_FIND_FIRST_OF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator1 __find_first_of_ce(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2,
    _BinaryPredicate __pred)
{
    for (; __first1 != __last1; ++__first1) {
        for (_ForwardIterator2 __j = __first2; __j != __last2; ++__j) {
            if (__pred(*__first1, *__j)) {
                return __first1;
            }
        }
    }
    return __last1;
}

template <class _ForwardIterator1, class _ForwardIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator1 find_first_of(_ForwardIterator1 __first1,
    _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2, _BinaryPredicate __pred)
{
    return asc::std::__find_first_of_ce(__first1, __last1, __first2, __last2, __pred);
}

template <class _ForwardIterator1, class _ForwardIterator2>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator1 find_first_of(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2, _ForwardIterator2 __last2)
{
    return asc::std::__find_first_of_ce(__first1, __last1, __first2, __last2, __equal_to{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_FIND_FIRST_OF_H
