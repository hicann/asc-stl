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

#ifndef ASC_STL_TEST_B022_RUNTIME_INPUTS_H
#define ASC_STL_TEST_B022_RUNTIME_INPUTS_H

#include <asc/__config>

namespace asc_stl_b022_runtime_inputs {

// Slots 40..45 belong to visibility; 48..51 hold the narrow CAS objects.
enum : unsigned { reordered_begin = 52, heap_begin = 57, seed_slot = 62 };

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_HOST_API void initialize(int* storage)
{
    for (unsigned index = 0; index < 5; ++index)
        storage[reordered_begin + index] = static_cast<int>(index) + 1;
    storage[heap_begin] = 1;
    storage[heap_begin + 1] = 5;
    storage[heap_begin + 2] = 2;
    storage[heap_begin + 3] = 4;
    storage[heap_begin + 4] = 3;
    storage[seed_slot] = 0;
}

CANN_ASC_STL_HOST_API bool unchanged(const int* storage)
{
    for (unsigned index = 0; index < 5; ++index) {
        if (storage[reordered_begin + index] != static_cast<int>(index) + 1)
            return false;
    }
    return storage[heap_begin] == 1 && storage[heap_begin + 1] == 5 && storage[heap_begin + 2] == 2 &&
        storage[heap_begin + 3] == 4 && storage[heap_begin + 4] == 3 && storage[seed_slot] == 0;
}
#endif

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class InputPointer>
CANN_ASC_STL_SIMT_API int value(InputPointer storage, unsigned slot)
{
    return storage[slot];
}
#endif

}  // namespace asc_stl_b022_runtime_inputs

#endif  // ASC_STL_TEST_B022_RUNTIME_INPUTS_H
