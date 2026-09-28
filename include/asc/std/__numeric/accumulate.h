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

#ifndef CANN_ASC_STL_STD_DETAIL_NUMERIC_ACCUMULATE_H
#define CANN_ASC_STL_STD_DETAIL_NUMERIC_ACCUMULATE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class InputIterator, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T accumulate(InputIterator first, InputIterator last, T init)
{
    for (; first != last; ++first) {
        init = ::asc::std::move(init) + *first;
    }
    return init;
}

template <class InputIterator, class T, class BinaryOperation>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T accumulate(
    InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
    for (; first != last; ++first) {
        init = binary_op(::asc::std::move(init), *first);  // NOLINT(build/include_what_you_use)
    }
    return init;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_NUMERIC_ACCUMULATE_H
