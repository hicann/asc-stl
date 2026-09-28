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

#ifndef CANN_ASC_STL_STD_DETAIL_NUMERIC_INCLUSIVE_SCAN_H
#define CANN_ASC_STL_STD_DETAIL_NUMERIC_INCLUSIVE_SCAN_H

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

template <class InputIterator, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator inclusive_scan(InputIterator first, InputIterator last, OutputIterator result)
{
    if (first == last) {
        return result;
    }
    typename iterator_traits<InputIterator>::value_type partial = *first;
    *result = partial;
    for (++first, ++result; first != last; ++first, ++result) {
        partial = ::asc::std::move(partial) + *first;  // NOLINT(build/include_what_you_use)
        *result = partial;
    }
    return result;
}

template <class InputIterator, class OutputIterator, class BinaryOperation>
CANN_ASC_STL_API constexpr OutputIterator inclusive_scan(
    InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op)
{
    if (first == last) {
        return result;
    }
    typename iterator_traits<InputIterator>::value_type partial = *first;
    *result = partial;
    for (++first, ++result; first != last; ++first, ++result) {
        partial = binary_op(::asc::std::move(partial), *first);
        *result = partial;
    }
    return result;
}

template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
CANN_ASC_STL_API constexpr OutputIterator inclusive_scan(
    InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op, T init)
{
    for (; first != last; ++first, ++result) {
        init = binary_op(::asc::std::move(init), *first);  // NOLINT(build/include_what_you_use)
        *result = init;
    }
    return result;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_NUMERIC_INCLUSIVE_SCAN_H
