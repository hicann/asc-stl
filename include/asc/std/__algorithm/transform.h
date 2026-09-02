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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_TRANSFORM_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_TRANSFORM_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIterator, class _OutputIterator, class _UnaryOperation>
CANN_ASC_STL_API constexpr _OutputIterator transform(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result, _UnaryOperation __op)
{
    for (; __first != __last; ++__first, (void)++__result) {
        *__result = __op(*__first);
    }
    return __result;
}

template <class _InputIterator1, class _InputIterator2, class _OutputIterator, class _BinaryOperation>
CANN_ASC_STL_API constexpr _OutputIterator transform(  // NOLINT(build/include_what_you_use)
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _OutputIterator __result,
    _BinaryOperation __binary_op)
{
    for (; __first1 != __last1; ++__first1, (void)++__first2, ++__result) {
        *__result = __binary_op(*__first1, *__first2);
    }
    return __result;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_TRANSFORM_H
