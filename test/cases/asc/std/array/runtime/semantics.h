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

#ifndef ASC_STL_STANDARD_RUNTIME_SEMANTICS_H
#define ASC_STL_STANDARD_RUNTIME_SEMANTICS_H

namespace asc_stl_standard_runtime {

enum class test_group {
    calendar,
    algorithms,
    function_objects,
    value_types,
    ranges,
    layouts,
    bytes_and_complex,
    text,
    memory,
    numeric,
    random,
#if defined(ASC_STL_STANDARD_RUNTIME_SIMT)
    sequences,
    ordered_set,
    unordered_set,
    unordered_map,
    scoped_allocator,
    adaptors,
    synchronization,
#endif
    count,
};

constexpr int kGroupCount = static_cast<int>(test_group::count);
#if defined(ASC_STL_STANDARD_RUNTIME_SIMT)
constexpr int kCoreGroupCount = static_cast<int>(test_group::sequences);
#else
constexpr int kCoreGroupCount = kGroupCount;
#endif

struct test_data {
    int seed;
    int failures[kGroupCount];
#if defined(ASC_STL_STANDARD_RUNTIME_SIMT)
    alignas(16) unsigned char container_storage[4096];
    alignas(16) unsigned char synchronization_storage[128];
#endif
};

bool run(test_data& data, int selected);

}  // namespace asc_stl_standard_runtime

#endif  // ASC_STL_STANDARD_RUNTIME_SEMANTICS_H
