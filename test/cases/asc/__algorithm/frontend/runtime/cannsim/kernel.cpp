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

#include "../../../../../../support/b019_runtime_submit.h"
#include "../semantics.h"

__global__ void asc_stl_b019_user_kernel(int* input, int* output)
{
    if (blockIdx.x != 0 || blockIdx.y != 0 || blockIdx.z != 0 || threadIdx.x != 0 || threadIdx.y != 0 ||
        threadIdx.z != 0)
        return;
    for (int index = 0; index != 4; ++index)
        output[index] = input[index];
    output[4] = 0x7f7f7f7f;
    asc::detail::transform_operation<int*, int*, asc_stl_b019_runtime::plus_one>{input, input + 4, output + 5, {}}();
    asc::detail::fill_operation<int*, int*, int>{output + 38, output + 40, 6}();
    asc::detail::adjacent_difference_operation<int*, int*, asc_stl_b019_runtime::minus_int>{
        input, input + 4, output + 9, {}}();
#if ASC_STL_B019_CANNSIM_STAGE >= 2
    asc::detail::merge_operation<int*, int*, int*, asc_stl_b019_runtime::less_int>{
        input, input + 2, input + 2, input + 4, output + 13, {}}();
    asc::detail::merge_sort_operation<int*, asc_stl_b019_runtime::less_int>{input + 4, input + 8, {}}();
#endif
#if ASC_STL_B019_CANNSIM_STAGE >= 3
    asc::detail::partition_operation<int*, asc_stl_b019_runtime::even_int>{
        input + 8, input + 12, reinterpret_cast<asc::std::size_t*>(output + 30), {}}();
    asc::detail::radix_sort_operation<int*, asc_stl_b019_runtime::less_int>{input + 12, input + 16, {}}();
#endif
#if ASC_STL_B019_CANNSIM_STAGE >= 4
    asc::detail::reduce_operation<int*, int, asc_stl_b019_runtime::plus_int>{input, input + 4, 0, output + 17, {}}();
    asc::detail::scan_operation<int*, int*, int, asc_stl_b019_runtime::plus_int, asc::detail::identity_operation<int>>{
        input, input + 4, output + 18, 0, {}, {}, false}();
#endif
#if ASC_STL_B019_CANNSIM_STAGE >= 5
    asc::detail::select_copy_operation<int*, int*, asc_stl_b019_runtime::even_int>{
        input, input + 4, output + 22, reinterpret_cast<asc::std::size_t*>(output + 32), {}}();
    asc::detail::find_index_operation<int*, asc::detail::equal_value<int>>{
        input, input + 4, reinterpret_cast<asc::std::size_t*>(output + 34), {3}}();
#endif
    output[37] = 19;
}

int launch_asc_stl_b019_cannsim(int* input, int* output, void* workspace, void* stream, int* callback_count)
{
    return asc_stl_b019_runtime::submit_cannsim<asc_stl_b019_user_kernel>(
        input, output, workspace, stream, callback_count);
}
