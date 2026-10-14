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

#ifndef CANN_ASC_STL_ASC___PARALLEL_SELECT_H
#define CANN_ASC_STL_ASC___PARALLEL_SELECT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {
// Sequential-semantics baseline: the select/compact family writes through a
// running count, i.e. a serial dependency. Parallelization path (later runtime
// work, kept as an anchor): evaluate the predicate per element, prefix-scan
// the boolean flags into stable target offsets and scatter in parallel - the
// same flag-scan + two-cursor scatter construction planned for partition.
template <class Input, class Output, class Predicate>
struct select_copy_operation {
    Input first;
    Input last;
    Output result;
    __SIZE_TYPE__* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ count{};
        for (Input current = first; current != last; ++current)
            if (predicate(*current)) {
                result[count] = *current;
                ++count;
            }
        *output = count;
    }
};
template <class Forward, class Predicate>
struct select_in_place_operation {
    Forward first;
    Forward last;
    __SIZE_TYPE__* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        // Compaction with a self-assignment guard: elements are moved only
        // once the write cursor lags the read cursor. *output carries the
        // number of retained elements, so the logical end is result + count
        // and the tail beyond it holds unspecified leftovers - exactly the
        // std::remove_if contract.
        Forward write = first;
        __SIZE_TYPE__ count{};
        for (; first != last; ++first)
            if (predicate(*first)) {
                if (write != first)
                    *write = *first;
                ++write;
                ++count;
            }
        *output = count;
    }
};
template <class Input, class Output, class BinaryPredicate>
struct unique_copy_operation {
    Input first;
    Input last;
    Output result;
    __SIZE_TYPE__* output;
    BinaryPredicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (first == last) {
            *output = 0;
            return;
        }
        // Keeps the previous key as a value snapshot instead of re-reading
        // the last written output slot: the output iterator may be
        // write-only (a discard sink only counts), unlike unique_operation
        // below, whose in-place "write position is the previous value"
        // idiom relies on the readable input range and saves one copy.
        __SIZE_TYPE__ count = 1;
        auto previous = *first;
        result[0] = previous;
        ++first;
        for (; first != last; ++first)
            if (!predicate(previous, *first)) {
                previous = *first;
                result[count] = previous;
                ++count;
            }
        *output = count;
    }
};
template <class Forward, class BinaryPredicate>
struct unique_operation {
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
        Forward write = first;
        Forward current = first;
        ++current;
        __SIZE_TYPE__ count = 1;
        for (; current != last; ++current)
            if (!predicate(*write, *current)) {
                ++write;
                *write = *current;
                ++count;
            }
        *output = count;
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_SELECT_H
