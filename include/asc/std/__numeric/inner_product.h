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

#ifndef CANN_ASC_STL_STD_DETAIL_NUMERIC_INNER_PRODUCT_H
#define CANN_ASC_STL_STD_DETAIL_NUMERIC_INNER_PRODUCT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIterator1, class _InputIterator2, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp inner_product(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _Tp __init)
{
    for (; __first1 != __last1; ++__first1, (void)++__first2) {
        __init = ::asc::std::move(__init) + *__first1 * *__first2;
    }
    return __init;
}

template <class _InputIterator1, class _InputIterator2, class _Tp, class _BinaryOperation1, class _BinaryOperation2>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _Tp __init, _BinaryOperation1 __binary_op1, _BinaryOperation2 __binary_op2)
{
    for (; __first1 != __last1; ++__first1, (void)++__first2) {
        __init = __binary_op1(
            ::asc::std::move(__init), __binary_op2(*__first1, *__first2));  // NOLINT(build/include_what_you_use)
    }
    return __init;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_NUMERIC_INNER_PRODUCT_H
