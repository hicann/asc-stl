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

#ifndef ASC_STL_TEST_ASC_HIERARCHY_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_HIERARCHY_RUNTIME_SEMANTICS_H

#include <asc/hierarchy>
#include <acl/acl.h>

void launch_asc_stl_b016_cannsim(int*, aclrtStream);
void launch_asc_stl_b016(int*, aclrtStream);

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
namespace asc_stl_b016_runtime {
template <class OutputPointer>
CANN_ASC_STL_DEVICE_API void evaluate(OutputPointer output)
{
    int failures = asc::block_count() == 0 || asc::block_index() >= asc::block_count();
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    failures += asc::thread_count() == 0 || asc::thread_index() >= asc::thread_count();
    failures += asc::thread_extents_3d().count() != asc::thread_count();
    failures += asc::block_extents_3d().count() != asc::block_count();
    failures += asc::lane_id() >= asc::warp_size;
    failures += asc::warp_index() >= asc::warp_count();
#else
    failures += asc::sub_block_count() == 0 || asc::sub_block_index() >= asc::sub_block_count();
#endif
    output[0] = failures;
}
}  // namespace asc_stl_b016_runtime
#endif

#endif  // ASC_STL_TEST_ASC_HIERARCHY_RUNTIME_SEMANTICS_H
