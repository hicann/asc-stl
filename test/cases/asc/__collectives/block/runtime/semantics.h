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

#ifndef ASC_STL_TEST_ASC_COLLECTIVES_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_COLLECTIVES_RUNTIME_SEMANTICS_H
#include <acl/acl.h>
#include <asc/collectives>
void launch_asc_stl_b018_cannsim(unsigned int*, aclrtStream);
void launch_asc_stl_b018_simt(unsigned int*, aclrtStream);
void launch_asc_stl_b018_simd(unsigned int*, aclrtStream);

namespace asc_stl_collective_test {
inline constexpr unsigned int threads = 64;
inline constexpr unsigned int columns = 8;
inline constexpr unsigned int groups = 3;
inline constexpr unsigned int result_count = threads * columns * groups;

inline bool verify(const unsigned int* values)
{
    for (unsigned int group = 0; group < groups; ++group) {
        for (unsigned int thread = 0; thread < threads; ++thread) {
            const auto* row = values + (group * threads + thread) * columns;
            if (row[0] != 2080 || row[1] != 1 || row[2] != 64 || row[3] != 18 ||
                row[4] != (thread + 1) * (thread + 2) / 2 || row[5] != thread * (thread + 1) / 2 || row[6] != 0 ||
                row[7] != 1)
                return false;
        }
    }
    return true;
}

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class T>
CANN_ASC_STL_SIMT_API void evaluate_group(T* shared, unsigned int* output, unsigned int thread)
{
    const auto workspace = asc::make_block_collective_workspace(shared, 32U);
    const T value = static_cast<T>(thread + 1);
    auto* row = output + thread * columns;
    row[0] = static_cast<unsigned int>(asc::block_reduce_add(workspace, value));
    row[1] = static_cast<unsigned int>(asc::block_reduce_min(workspace, value));
    row[2] = static_cast<unsigned int>(asc::block_reduce_max(workspace, value));
    row[3] = static_cast<unsigned int>(asc::block_broadcast(workspace, value, 17));
    row[4] = static_cast<unsigned int>(asc::block_inclusive_scan(workspace, value));
    row[5] = static_cast<unsigned int>(asc::block_exclusive_scan(workspace, value));
    const auto predicate_workspace = asc::make_block_collective_workspace(reinterpret_cast<unsigned int*>(shared), 32U);
    row[6] = asc::block_all(predicate_workspace, thread != 63);
    row[7] = asc::block_any(predicate_workspace, thread == 63);
}
#endif
}  // namespace asc_stl_collective_test

#endif
