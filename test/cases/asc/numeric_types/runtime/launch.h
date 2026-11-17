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

#ifndef ASC_STL_TEST_NUMERIC_TYPES_LAUNCH_H
#define ASC_STL_TEST_NUMERIC_TYPES_LAUNCH_H

#include <asc/numeric_types>
#include <cstdint>

struct numeric_parameters {
    asc::float16 fp16;
    asc::bfloat16 bf16;
    asc::float8_e4m3fn e4m3;
    asc::float8_e5m2 e5m2;
    asc::float8_e8m0 scale;
    asc::hifloat8 hif8;
    asc::float4_e2m1x2 e2m1;
    asc::float4_e1m2x2 e1m2;
    asc::int4x2 packed;
    asc::int4 scalar;
};

inline constexpr unsigned numeric_lanes = 32;
// Separate scalar writers by 512 bytes, including the status words. AI Core
// scalar caches are not coherent between cores for adjacent GM word stores.
inline constexpr unsigned numeric_cache_words = 128;
CANN_ASC_STL_API constexpr unsigned numeric_invariant_base(unsigned count)
{
    return ((count + numeric_cache_words - 1) / numeric_cache_words) * numeric_cache_words;
}

asc::float16 numeric_types_host_prepare(float input);

void launch_numeric_types(
    std::uint32_t* output, const std::uint32_t* records, unsigned count, numeric_parameters parameters, void* stream);

#endif  // ASC_STL_TEST_NUMERIC_TYPES_LAUNCH_H
