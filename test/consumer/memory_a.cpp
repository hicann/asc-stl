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

#include <asc/memory>

int asc_stl_memory_consumer_b();

int asc_stl_memory_consumer_a()
{
    alignas(16) unsigned char storage[32] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::arena_allocator<int> allocator(arena);
    int* data = allocator.allocate(2);
    asc::gm_span<int> view(data, 2);
    if (data != nullptr) {
        view[0] = 3;
        view[1] = 5;
    }
    return data != nullptr && view.size() == 2 && view[0] + view[1] == 8 ? asc_stl_memory_consumer_b() : 1;
}
