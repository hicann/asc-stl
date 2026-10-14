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

#ifndef CANN_ASC_STL_ASC___COLLECTIVES_UB_RANGE_H
#define CANN_ASC_STL_ASC___COLLECTIVES_UB_RANGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__memory/views.h>

namespace asc::detail {

#if !CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class T>
CANN_ASC_STL_DEVICE_API T ub_reduce_add_impl(ub_span<const T> input) noexcept
{
    T result{};
    for (__SIZE_TYPE__ index = 0; index < input.size(); ++index) {
        result = result + input.data()[index];
    }
    return result;
}

template <class T>
CANN_ASC_STL_DEVICE_API T ub_reduce_min_impl(ub_span<const T> input) noexcept
{
    // The registered contract declares the min/max input nonempty; an empty
    // span is still handled defensively (value-initialized result, matching
    // ub_reduce_add_impl) instead of reading out of bounds.
    if (input.size() == 0) {
        return T{};
    }
    T result = input.data()[0];
    for (__SIZE_TYPE__ index = 1; index < input.size(); ++index) {
        if (input.data()[index] < result) {
            result = input.data()[index];
        }
    }
    return result;
}

template <class T>
CANN_ASC_STL_DEVICE_API T ub_reduce_max_impl(ub_span<const T> input) noexcept
{
    // Empty input: same defensive contract as ub_reduce_min_impl.
    if (input.size() == 0) {
        return T{};
    }
    T result = input.data()[0];
    for (__SIZE_TYPE__ index = 1; index < input.size(); ++index) {
        if (result < input.data()[index]) {
            result = input.data()[index];
        }
    }
    return result;
}

// Registered scan contract: the two ranges have equal size and may alias
// only by exact in-place equality.  In-place aliasing is safe for both scan
// directions here because every element is read before the same-index write.
// A short output is a size-contract violation the no-status, no-trap
// vocabulary cannot report, so each walk is clipped to the shorter range
// instead of writing past the output's end.
template <class T>
CANN_ASC_STL_DEVICE_API void ub_inclusive_scan_add_impl(ub_span<T> output, ub_span<const T> input) noexcept
{
    const __SIZE_TYPE__ count = input.size() < output.size() ? input.size() : output.size();
    T prefix{};
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        prefix = prefix + input.data()[index];
        output.data()[index] = prefix;
    }
}

template <class T>
CANN_ASC_STL_DEVICE_API void ub_exclusive_scan_add_impl(ub_span<T> output, ub_span<const T> input) noexcept
{
    const __SIZE_TYPE__ count = input.size() < output.size() ? input.size() : output.size();
    T prefix{};
    for (__SIZE_TYPE__ index = 0; index < count; ++index) {
        const T value = input.data()[index];
        output.data()[index] = prefix;
        prefix = prefix + value;
    }
}
#endif

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___COLLECTIVES_UB_RANGE_H
