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

#ifndef CANN_ASC_STL_ASC___PARALLEL_FIND_H
#define CANN_ASC_STL_ASC___PARALLEL_FIND_H

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
template <class Input, class Predicate>
struct find_index_operation {
    Input first;
    Input last;
    __SIZE_TYPE__* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ index{};
        for (Input current = first; current != last; ++current, ++index) {
            if (predicate(*current)) {
                *output = index;
                return;
            }
        }
        *output = index;
    }
};
template <class Forward, class BinaryPredicate>
struct adjacent_find_operation {
    Forward first;
    Forward last;
    __SIZE_TYPE__* output;
    BinaryPredicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (first == last) {
            *output = 0;
            return;
        }
        Forward next = first;
        __SIZE_TYPE__ index{};
        while (++next != last) {
            if (predicate(*first, *next)) {
                *output = index;
                return;
            }
            first = next;
            ++index;
        }
        *output = index + 1;
    }
};
template <class Random, class Compare>
struct is_heap_until_operation {
    Random first;
    Random last;
    __SIZE_TYPE__* output;
    Compare compare;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ length = static_cast<__SIZE_TYPE__>(last - first);
        for (__SIZE_TYPE__ child = 1; child < length; ++child) {
            if (compare(first[(child - 1) / 2], first[child])) {
                *output = child;
                return;
            }
        }
        *output = length;
    }
};
template <class Random, class Compare>
struct is_heap_operation {
    Random first;
    Random last;
    unsigned int* output;
    Compare compare;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ length = static_cast<__SIZE_TYPE__>(last - first);
        for (__SIZE_TYPE__ child = 1; child < length; ++child) {
            if (compare(first[(child - 1) / 2], first[child])) {
                *output = 0;
                return;
            }
        }
        *output = 1;
    }
};
template <class Input, class Predicate>
struct is_partitioned_operation {
    Input first;
    Input last;
    unsigned int* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        while (first != last && predicate(*first))
            ++first;
        while (first != last) {
            if (predicate(*first)) {
                *output = 0;
                return;
            }
            ++first;
        }
        *output = 1;
    }
};
template <class Forward, class Compare>
struct is_sorted_until_operation {
    Forward first;
    Forward last;
    __SIZE_TYPE__* output;
    Compare compare;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (first == last) {
            *output = 0;
            return;
        }
        Forward next = first;
        __SIZE_TYPE__ index = 1;
        while (++next != last) {
            if (compare(*next, *first)) {
                *output = index;
                return;
            }
            first = next;
            ++index;
        }
        *output = index;
    }
};
template <class Forward, class Compare>
struct is_sorted_operation {
    Forward first;
    Forward last;
    unsigned int* output;
    Compare compare;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (first == last) {
            *output = 1;
            return;
        }
        Forward next = first;
        while (++next != last) {
            if (compare(*next, *first)) {
                *output = 0;
                return;
            }
            first = next;
        }
        *output = 1;
    }
};
template <class Input1, class Input2, class BinaryPredicate>
struct mismatch_operation {
    Input1 first1;
    Input1 last1;
    Input2 first2;
    Input2 last2;
    __SIZE_TYPE__* output;
    BinaryPredicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ index{};
        while (first1 != last1 && first2 != last2 && predicate(*first1, *first2)) {
            ++first1;
            ++first2;
            ++index;
        }
        output[0] = index;
        output[1] = index;
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_FIND_H
