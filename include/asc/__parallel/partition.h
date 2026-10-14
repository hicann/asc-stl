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

#ifndef CANN_ASC_STL_ASC___PARALLEL_PARTITION_H
#define CANN_ASC_STL_ASC___PARALLEL_PARTITION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__parallel/radix_sort.h>
namespace asc::detail {
// Hoare-style two-end exchange: satisfies the std::partition contract of a
// two-block range without preserving relative order (unlike
// stable_partition_operation below, which keeps input order). The returned
// left-first distance is the length of the satisfied block.
template <class Forward, class Predicate>
struct partition_operation {
    Forward first;
    Forward last;
    __SIZE_TYPE__* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        Forward left = first;
        Forward right = last;
        while (true) {
            while (left != right && predicate(*left))
                ++left;
            if (left == right)
                break;
            do {
                --right;
            } while (left != right && !predicate(*right));
            if (left == right)
                break;
            auto value = static_cast<decltype(*left)&&>(*left);
            *left = static_cast<decltype(*right)&&>(*right);
            *right = static_cast<decltype(value)&&>(value);
            ++left;
        }
        *output = static_cast<__SIZE_TYPE__>(left - first);
    }
};
template <class Input, class Output1, class Output2, class Predicate>
struct partition_copy_operation {
    Input first;
    Input last;
    Output1 true_result;
    Output2 false_result;
    __SIZE_TYPE__* output;
    Predicate predicate;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        __SIZE_TYPE__ selected{};
        __SIZE_TYPE__ rejected{};
        for (; first != last; ++first) {
            if (predicate(*first)) {
                true_result[selected] = *first;
                ++selected;
            } else {
                false_result[rejected] = *first;
                ++rejected;
            }
        }
        // The frontend contract exposes a single selected-count sink: only the
        // true count is written; the rejected count is the input length minus
        // it, so callers never need to reserve a second slot.
        *output = selected;
    }
};
template <class Bidirectional, class Predicate>
struct stable_partition_operation {
    using element = range_element<Bidirectional>;

    Bidirectional first;
    Bidirectional last;
    __SIZE_TYPE__* output;
    Predicate predicate;
    element* buffer;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        if (buffer != nullptr) {
            // Buffered two-pass form, O(n) moves: first sweep gathers the
            // satisfying elements into the front of the policy temporary
            // storage, second sweep appends the rest, final sweep copies the
            // compacted sequence back. Relative order inside both blocks is
            // preserved, matching the rotation fallback below.
            __SIZE_TYPE__ selected = 0;
            for (Bidirectional current = first; current != last; ++current) {
                if (predicate(*current)) {
                    buffer[selected] = static_cast<decltype(*current)&&>(*current);
                    ++selected;
                }
            }
            __SIZE_TYPE__ unselected = selected;
            for (Bidirectional current = first; current != last; ++current) {
                if (!predicate(*current)) {
                    buffer[unselected] = static_cast<decltype(*current)&&>(*current);
                    ++unselected;
                }
            }
            for (__SIZE_TYPE__ index = 0; index < unselected; ++index) {
                first[index] = static_cast<decltype(buffer[index])&&>(buffer[index]);
            }
            *output = selected;
            return;
        }
        // Storage-less fallback: stable forward rotation, worst-case O(n^2)
        // moves but no auxiliary memory; the frontend hands the buffer in
        // whenever the policy temporary storage covers one element per input.
        Bidirectional write = first;
        for (Bidirectional current = first; current != last; ++current) {
            if (!predicate(*current))
                continue;
            auto value = static_cast<decltype(*current)&&>(*current);
            Bidirectional position = current;
            while (position != write) {
                *position = static_cast<decltype(*(position - 1))&&>(*(position - 1));
                --position;
            }
            *write = static_cast<decltype(value)&&>(value);
            ++write;
        }
        *output = static_cast<__SIZE_TYPE__>(write - first);
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_PARTITION_H
