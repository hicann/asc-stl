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

#include <memory>

#include "../../../../support/w09_w10_semantics.h"
#include "../../../../support/allocator_public_contract.h"

int main()
{
    std::allocator<int> allocator;
    const int value = asc::std::make_obj_using_allocator<int>(allocator, 7);
    alignas(int) unsigned char storage[sizeof(int)];
    int* address = reinterpret_cast<int*>(storage);
    int* constructed = asc::std::uninitialized_construct_using_allocator(address, allocator, 8);
    const bool allocator_construction_ok = value == 7 && constructed == address && *constructed == 8;
    asc::std::destroy_at(constructed);
    return (allocator_construction_ok ? 0 : 1) + asc_stl_w09_w10_test::evaluate_memory_variant() +
        asc_stl_allocator_public_test::allocator_bulk_behavior();
}
