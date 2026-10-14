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

#ifndef CANN_ASC_STL_ASC___PARALLEL_ADJACENT_DIFFERENCE_H
#define CANN_ASC_STL_ASC___PARALLEL_ADJACENT_DIFFERENCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {
// Sequential-semantics baseline: one work item walks the whole range in order,
// so output[i] sees exactly the previous input element as the subtrahend.
// Parallelization path (later runtime work, kept as an anchor): the difference
// for element i depends only on input[i] and input[i-1], so a grid-strided
// launch can evaluate every element concurrently once the first element
// forwards its value as the init of its block; until that plan lands, the
// single-thread submit channel is the documented semantics.
template <class Input, class Output, class BinaryOperation>
struct adjacent_difference_operation {
    Input first;
    Input last;
    Output result;
    BinaryOperation operation;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (first == last)
            return;
        auto previous = *first;
        *result = previous;
        ++first;
        ++result;
        for (; first != last; ++first, ++result) {
            auto current = *first;
            *result = operation(current, previous);
            previous = current;
        }
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_ADJACENT_DIFFERENCE_H
