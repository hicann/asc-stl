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

#include <asc/std/memory>
#include <asc/std/type_traits>

int main()
{
    int value = 7;
    int* pointer = asc::std::addressof(value);

    using traits = asc::std::pointer_traits<int*>;
    static_assert(asc::std::is_same_v<traits::pointer, int*>);
    static_assert(asc::std::is_same_v<traits::element_type, int>);
    static_assert(asc::std::is_same_v<traits::difference_type, asc::std::ptrdiff_t>);
    static_assert(asc::std::is_same_v<traits::rebind<long>, long*>);

    if (traits::pointer_to(value) != pointer || asc::std::to_address(pointer) != pointer)
        return 1;
    if (asc::std::assume_aligned<alignof(int)>(pointer) != pointer)
        return 2;
    alignas(16) int aligned_values[2]{};
    if (!asc::std::is_sufficiently_aligned<16>(aligned_values))
        return 3;
    if (asc::std::is_sufficiently_aligned<16>(aligned_values + 1))
        return 4;

    alignas(16) unsigned char storage[32]{};
    void* position = storage + 1;
    asc::std::size_t space = sizeof(storage) - 1;
    void* aligned = asc::std::align(alignof(int), sizeof(int), position, space);
    if (aligned == nullptr || aligned != position)
        return 5;
    return 0;
}
