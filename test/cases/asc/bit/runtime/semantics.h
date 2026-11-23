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

#ifndef ASC_STL_TEST_BIT_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_BIT_RUNTIME_SEMANTICS_H

#include <asc/bit>

#include "launch.h"

template <class T, class Output>
CANN_ASC_STL_API void bit_store_results(Output output, T destination, T source, int start, int width)
{
    output[0] = asc::bit_reverse(destination);
    output[1] = asc::bitfield_extract(destination, start, width);
    output[2] = asc::bitfield_insert(destination, source, start, width);
    output[3] = asc::bitmask<T>(start, width);
}

template <class Records, class Output>
CANN_ASC_STL_API void bit_evaluate_record(Records records, Output output, unsigned index)
{
    const auto destination = records[index].destination;
    const auto source = records[index].source;
    const int start = records[index].start;
    const int width = records[index].width;
    bit_store_results(output + index * bit_output_words, static_cast<asc::std::uint32_t>(destination),
        static_cast<asc::std::uint32_t>(source), start, width);
    bit_store_results(output + index * bit_output_words + 4, destination, source, start, width);
}

#endif  // ASC_STL_TEST_BIT_RUNTIME_SEMANTICS_H
