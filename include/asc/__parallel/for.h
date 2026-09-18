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

#include <asc/execution>
#include <asc/launch>
namespace asc::detail {
template <class First, class Last, class Function>
struct for_each_operation {
    First first;
    Last last;
    Function function;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (First current = first; current != last; ++current)
            function(*current);
    }
};
template <class First, class Size, class Function>
struct for_each_n_operation {
    First first;
    Size count;
    Function function;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Size index{}; index < count; ++index)
            function(first[index]);
    }
};
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
template <class First, class Size, class T>
struct fill_n_operation {
    First first;
    Size count;
    T value;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Size index{}; index < count; ++index)
            first[index] = value;
    }
};
template <class First, class Last, class Generator>
struct generate_operation {
    First first;
    Last last;
    Generator generator;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (First current = first; current != last; ++current)
            *current = generator();
    }
};
template <class First, class Size, class Generator>
struct generate_n_operation {
    First first;
    Size count;
    Generator generator;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        for (Size index{}; index < count; ++index)
            first[index] = generator();
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_FOR_H
