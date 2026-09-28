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

#include "../../../../support/allocator_public_contract.h"

template <class T>
struct host_allocator : std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = host_allocator<U>;
    };
    host_allocator() = default;
    template <class U>
    host_allocator(const host_allocator<U>&) noexcept
    {}
};

int main()
{
    host_allocator<int> outer{};
    asc::std::scoped_allocator_adaptor<host_allocator<int>> allocator(outer);
    int* value = allocator.allocate(1);
    allocator.construct(value, 7);
    const int result = *value;
    allocator.destroy(value);
    allocator.deallocate(value, 1);
    return asc_stl_allocator_public_test::scoped_allocator_behavior() + (result == 7 ? 0 : 1);
}
