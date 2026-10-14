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

#ifndef CANN_ASC_STL_ASC___PARALLEL_MERGE_SORT_H
#define CANN_ASC_STL_ASC___PARALLEL_MERGE_SORT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__parallel/merge.h>
#include <asc/__parallel/radix_sort.h>

namespace asc::detail {

// One bottom-up merge pass over [0, count): merges each pair of adjacent runs
// of the given width from source into destination through merge_operation; a
// run without a right partner is copied across unchanged.
template <class Source, class Destination, class Compare>
CANN_ASC_STL_DEVICE_API void merge_sort_pass(
    Source source, __SIZE_TYPE__ count, __SIZE_TYPE__ width, Destination destination, Compare compare)
{
    for (__SIZE_TYPE__ index = 0; index < count; index += width * 2) {
        const __SIZE_TYPE__ middle = index + width;
        if (middle >= count) {
            for (__SIZE_TYPE__ remaining = index; remaining < count; ++remaining) {
                destination[remaining] = static_cast<decltype(source[remaining])&&>(source[remaining]);
            }
            continue;
        }
        __SIZE_TYPE__ end = middle + width;
        if (end > count) {
            end = count;
        }
        merge_operation<Source, Source, Destination, Compare>{
            source + index, source + middle, source + middle, source + end, destination + index, compare}();
    }
}

// Iterative bottom-up merge sort for arbitrary strict-weak-ordering
// comparators: the run width doubles each pass and the roles of the input
// range and the buffer swap between passes (double buffering). Non-recursive;
// O(n log n) comparisons and stable, because merge_operation keeps the left
// run on ties. The buffer is one element copy per input element, carved out of
// the policy temporary storage by the sort frontend; braced construction with
// only {first, last, compare} leaves the buffer null and takes the shared
// insertion path, as does any range below the insertion threshold.
template <class Random, class Compare>
struct merge_sort_operation {
    using element = range_element<Random>;

    Random first;
    Random last;
    Compare compare;
    element* buffer;
    CANN_ASC_STL_DEVICE_API void operator()()
    {
        const __SIZE_TYPE__ count = static_cast<__SIZE_TYPE__>(last - first);
        if (count < 2) {
            return;
        }
        if (count < sort_insertion_threshold || buffer == nullptr) {
            insertion_sort_range(first, last, compare);
            return;
        }
        bool sorted_in_buffer = false;
        for (__SIZE_TYPE__ width = 1; width < count; width *= 2) {
            if (sorted_in_buffer) {
                merge_sort_pass(buffer, count, width, first, compare);
            } else {
                merge_sort_pass(first, count, width, buffer, compare);
            }
            sorted_in_buffer = !sorted_in_buffer;
        }
        if (sorted_in_buffer) {
            for (__SIZE_TYPE__ index = 0; index < count; ++index) {
                first[index] = static_cast<decltype(buffer[index])&&>(buffer[index]);
            }
        }
    }
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_MERGE_SORT_H
