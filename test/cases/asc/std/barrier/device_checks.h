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

#ifndef ASC_STL_TEST_BARRIER_DEVICE_CHECKS_H
#define ASC_STL_TEST_BARRIER_DEVICE_CHECKS_H

#include <asc/std/barrier>
#include <asc/std/new>

namespace asc_stl_test_barrier {
struct completed {
    int* count;
    CANN_ASC_STL_HOST_SIMT_API void operator()() noexcept
    {
        ++*count;
    }
};
CANN_ASC_STL_HOST_SIMT_API int check(int seed, void* workspace)
{
    using gate = asc::std::barrier<completed>;
    static_assert(gate::max() >= 3);
    static_assert(sizeof(gate) <= 128);
    auto* count = reinterpret_cast<int*>(static_cast<unsigned char*>(workspace) + 128);
    ::new (static_cast<void*>(count)) int{0};
    int& phases = *count;
    auto* participants = static_cast<gate*>(workspace);
    ::new (static_cast<void*>(participants)) gate(seed - 4, completed{&phases});
    auto first = participants->arrive(2);
    if (phases != 0)
        return 1;
    participants->arrive_and_drop();
    participants->wait(static_cast<gate::arrival_token&&>(first));
    if (phases != 1)
        return 2;
    auto second = participants->arrive(2);
    participants->wait(static_cast<gate::arrival_token&&>(second));
    if (phases != 2)
        return 3;
    participants->arrive_and_drop();
    participants->arrive_and_wait();
    participants->arrive_and_wait();
    participants->~gate();
    return phases == 4 ? 0 : 4;
}
}  // namespace asc_stl_test_barrier

#endif  // ASC_STL_TEST_BARRIER_DEVICE_CHECKS_H
