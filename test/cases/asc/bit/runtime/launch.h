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

#ifndef ASC_STL_TEST_BIT_RUNTIME_LAUNCH_H
#define ASC_STL_TEST_BIT_RUNTIME_LAUNCH_H

#include <asc/std/cstdint>

struct bit_record {
    asc::std::uint64_t destination;
    asc::std::uint64_t source;
    int start;
    int width;
};

inline constexpr unsigned bit_output_words = 8;

void launch_bit(asc::std::uint64_t* output, const bit_record* records, unsigned count, void* stream);

#endif  // ASC_STL_TEST_BIT_RUNTIME_LAUNCH_H
