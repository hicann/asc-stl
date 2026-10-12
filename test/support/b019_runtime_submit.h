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

#ifndef ASC_STL_TEST_B019_RUNTIME_SUBMIT_H
#define ASC_STL_TEST_B019_RUNTIME_SUBMIT_H

#include <asc/__algorithm/byte_operations.h>
#include <asc/algorithm>

namespace asc_stl_b019_runtime {

struct plus_one {
    __aicore__ int operator()(int value) const noexcept
    {
        return value + 1;
    }
};

struct plus_int {
    __aicore__ int operator()(int left, int right) const noexcept
    {
        return left + right;
    }
};

struct minus_int {
    __aicore__ int operator()(int left, int right) const noexcept
    {
        return left - right;
    }
};

struct less_int {
    __aicore__ bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};

struct even_int {
    __aicore__ bool operator()(int value) const noexcept
    {
        return value % 2 == 0;
    }
};

inline void increment_callback(void* data)
{
    ++*static_cast<int*>(data);
}

template <auto Kernel>
inline int submit(int* input, int* output, void* workspace, void* stream, int* callback_count)
{
    int stage = 1;
    const asc::stream_ref stream_reference{stream};
    const auto policy =
        asc::execution::device.on(stream_reference).with_temporary_storage({workspace, 256, asc::memory_space::global});
#if CANN_ASC_STL_USE_SIMT_LAUNCH
    const auto rejected =
        asc::launch<Kernel>(stream_reference, asc::simt_launch_config{{0, 1, 1}, {1, 1, 1}, 0}, output + 37);
    asc::execution_status status = rejected.code() == asc::execution_errc::invalid_argument ?
        asc::launch<Kernel>(stream_reference, asc::simt_launch_config{{1, 1, 1}, {1, 1, 1}, 0}, output + 37) :
        asc::execution_status{asc::execution_errc::backend_error};
#else
    const auto rejected = asc::launch<Kernel>(stream_reference, asc::aicore_launch_config{}, output + 37);
    asc::execution_status status = rejected.code() == asc::execution_errc::invalid_argument ?
        asc::launch<Kernel>(stream_reference, asc::aicore_launch_config{1}, output + 37) :
        asc::execution_status{asc::execution_errc::backend_error};
#endif
    if (status.success()) {
        stage = 2;
        status = asc::copy_bytes(stream_reference, output, input, 4 * sizeof(int));
    }
    if (status.success()) {
        stage = 3;
        status = asc::fill_bytes(stream_reference, output + 4, 0x7f, sizeof(int));
    }
    if (status.success()) {
        stage = 4;
        status = asc::parallel::transform(policy, input, input + 4, output + 5, plus_one{});
    }
    if (status.success()) {
        stage = 5;
        status = asc::parallel::fill(policy, output + 38, output + 40, 6);
    }
    if (status.success())
        status = asc::parallel::adjacent_difference(policy, input, input + 4, output + 9, minus_int{});
    if (status.success())
        status = asc::parallel::merge(policy, input, input + 2, input + 2, input + 4, output + 13, less_int{});
    if (status.success())
        status = asc::detail::submit(
            policy, asc::detail::merge_sort_operation<int*, less_int>{input + 4, input + 8, less_int{}});
    if (status.success())
        status = asc::parallel::partition(
            policy, input + 8, input + 12, reinterpret_cast<asc::std::size_t*>(output + 30), even_int{});
    if (status.success())
        status = asc::parallel::sort(policy, input + 12, input + 16, less_int{});
    if (status.success())
        status = asc::parallel::reduce(policy, input, input + 4, 0, output + 17, plus_int{});
    if (status.success())
        status = asc::parallel::exclusive_scan(policy, input, input + 4, output + 18, 0, plus_int{});
    if (status.success())
        status = asc::parallel::copy_if(
            policy, input, input + 4, output + 22, reinterpret_cast<asc::std::size_t*>(output + 32), even_int{});
    if (status.success())
        status = asc::parallel::find(policy, input, input + 4, 3, reinterpret_cast<asc::std::size_t*>(output + 34));
    if (status.success()) {
        stage = 99;
        status = asc::host_callback(stream_reference, increment_callback, callback_count);
    }
    return status.success() ? 0 : stage * 100 + static_cast<int>(status.code());
}

template <auto Kernel>
inline int submit_cannsim(int* input, int* output, void* workspace, void* stream, int* callback_count)
{
    (void)workspace;
    (void)callback_count;
    const asc::stream_ref stream_reference{stream};
    const asc::execution_status status =
        asc::launch<Kernel>(stream_reference, asc::simt_launch_config{{1, 1, 1}, {1, 1, 1}, 0}, input, output);
    return status.success() ? 0 : static_cast<int>(status.code());
}

}  // namespace asc_stl_b019_runtime

#endif  // ASC_STL_TEST_B019_RUNTIME_SUBMIT_H
