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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_ADJACENT_FIND_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_ADJACENT_FIND_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ForwardIterator, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator adjacent_find(
    _ForwardIterator __first, _ForwardIterator __last, _BinaryPredicate __pred)
{
    if (__first != __last) {
        _ForwardIterator __i = __first;
        while (++__i != __last) {
            if (__pred(*__first, *__i)) {
                __last = __first;
                break;
            }
            __first = __i;
        }
    }
    return __last;
}

template <class _ForwardIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator adjacent_find(
    _ForwardIterator __first, _ForwardIterator __last)
{
    return asc::std::adjacent_find(__first, __last, __equal_to{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_ADJACENT_FIND_H
