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

#ifndef CANN_ASC_STL_STD_DETAIL_NUMERIC_TRANSFORM_REDUCE_H
#define CANN_ASC_STL_STD_DETAIL_NUMERIC_TRANSFORM_REDUCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class InputIterator1, class InputIterator2, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T transform_reduce(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
{
    for (; first1 != last1; ++first1, ++first2) {
        init = ::asc::std::move(init) + (*first1 * *first2);
    }
    return init;
}

template <class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T transform_reduce(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, T init, BinaryOperation1 reduce_op, BinaryOperation2 transform_op)
{
    for (; first1 != last1; ++first1, ++first2) {
        init = reduce_op(::asc::std::move(init), transform_op(*first1, *first2));
    }
    return init;
}

template <class InputIterator, class T, class BinaryOperation, class UnaryOperation>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T transform_reduce(
    InputIterator first, InputIterator last, T init, BinaryOperation reduce_op, UnaryOperation transform_op)
{
    for (; first != last; ++first) {
        init = reduce_op(::asc::std::move(init), transform_op(*first));  // NOLINT(build/include_what_you_use)
    }
    return init;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_NUMERIC_TRANSFORM_REDUCE_H
