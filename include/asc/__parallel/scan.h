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

#ifndef CANN_ASC_STL_ASC___PARALLEL_SCAN_H
#define CANN_ASC_STL_ASC___PARALLEL_SCAN_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__parallel/temporary_storage.h>
#include <asc/launch>
namespace asc::detail {
template <class Input, class Output, class T, class BinaryOperation, class UnaryOperation>
struct scan_operation {
    Input first;
    Input last;
    Output result;
    T init;
    BinaryOperation binary;
    UnaryOperation unary;
    bool inclusive;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        T value = init;
        for (; first != last; ++first, ++result) {
            if (inclusive) {
                value = binary(value, unary(*first));
                *result = value;
            } else {
                *result = value;
                value = binary(value, unary(*first));
            }
        }
    }
};
template <class T>
struct identity_operation {
    CANN_ASC_STL_DEVICE_API T operator()(const T& value) const
    {
        return value;
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_SCAN_H
