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
#ifndef CANN_ASC_STL_ASC___PARALLEL_FOR_H
#define CANN_ASC_STL_ASC___PARALLEL_FOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {
// fill_operation stays as the iterator-pair sequential reference body: the
// runtime semantics suite (cannsim kernel) pins its exact braced layout. The
// for_each/fill_n/generate frontends no longer keep serial twins here; they
// submit through the grid-stride channel below.
template <class First, class Last, class T>
struct fill_operation {
    First first;
    Last last;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (First current = first; current != last; ++current)
            *current = value;
    }
};
// Grid-stride companions of the for/fill/generate operations, shaped for the
// coordinate-parameterized kernel: each device thread visits the elements
// whose linear index is congruent to its thread index modulo the total thread
// count, so every element is still visited exactly once while the launch
// spans the whole grid. One body per family covers both frontend shapes
// (iterator pair and first+count) through the count parameter. Note for the
// callable-taking variants: a stateful callable keeps its "invoked exactly
// once per element" guarantee but loses the sequential call order under this
// channel.
template <class Input, class Function>
struct grid_strided_for_each_operation {
    Input first;
    __SIZE_TYPE__ count;
    Function function;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride) {
            function(first[index]);
        }
    }
};
template <class First, class T>
struct grid_strided_fill_operation {
    First first;
    __SIZE_TYPE__ count;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            first[index] = value;
    }
};
template <class First, class Generator>
struct grid_strided_generate_operation {
    First first;
    __SIZE_TYPE__ count;
    Generator generator;
    CANN_ASC_STL_DEVICE_API void operator()(__SIZE_TYPE__ index, __SIZE_TYPE__ stride)
    {
        for (; index < count; index += stride)
            first[index] = generator();
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_FOR_H
