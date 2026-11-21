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

#include <asc/std/random>

#include "../semantics.h"

__global__ void asc_stl_b024_cannsim_kernel(unsigned long long* output, asc::detail::work_cursor* cursor)
{
    asc_stl_b024_runtime::evaluate(output, cursor);

    // The host supplies the seeds in GM and checks the full-width draws after launch.
    constexpr unsigned long long modulus = 0xffffffffffffffc5ULL;
    asc::std::linear_congruential_engine<unsigned long long, 3, 1, 10> exact(output[2]);
    asc::std::linear_congruential_engine<unsigned, 5, 0, 0> zero(static_cast<unsigned>(output[3]));
    asc::std::linear_congruential_engine<unsigned long long, modulus - 5, modulus - 3, modulus> wide(output[4]);
    output[2] = exact();
    output[3] = zero();
    output[4] = wide();
}

void launch_asc_stl_b024_cannsim(unsigned long long* output, asc::detail::work_cursor* cursor, void* stream)
{
    asc_stl_b024_cannsim_kernel<<<1, 1, 0, stream>>>(output, cursor);
}
