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

#ifndef ASC_STL_TEST_MEMORY_DEVICE_CHECKS_H
#define ASC_STL_TEST_MEMORY_DEVICE_CHECKS_H

#include <asc/std/memory>

namespace asc_stl_test_memory {
CANN_ASC_STL_API int check(int seed = 7)
{
    alignas(16) unsigned char storage[32]{};
    for (unsigned offset = 0; offset < 8; ++offset) {
        for (unsigned length = 0; length <= 16; ++length) {
            void* p = storage + offset;
            asc::std::size_t space = length;
            const unsigned padding = (8 - offset) % 8;
            void* result = asc::std::align(8, 4, p, space);
            if (length < padding + 4) {
                if (result || p != storage + offset || space != length)
                    return 1;
            } else if (result != storage + offset + padding || p != result || space != length - padding) {
                return 2;
            }
        }
    }
    alignas(int) unsigned char raw[3 * sizeof(int)];
    auto* dst = reinterpret_cast<int*>(raw);
    int src[] = {3, -1, seed};
    if (asc::std::uninitialized_copy(src, src + 3, dst) != dst + 3 || dst[1] != -1)
        return 3;
    if (asc::std::destroy_n(dst, 3) != dst + 3 || asc::std::uninitialized_copy_n(src, -2, dst) != dst)
        return 4;
    asc::std::uninitialized_fill(dst, dst + 3, 9);
    if (dst[0] != 9 || dst[2] != 9)
        return 5;
    asc::std::destroy(dst, dst + 3);
    if (asc::std::uninitialized_fill_n(dst, 3, 13) != dst + 3 || dst[1] != 13)
        return 6;
    asc::std::destroy(dst, dst + 3);
    asc::std::uninitialized_default_construct(dst, dst + 3);
    asc::std::destroy(dst, dst + 3);
    if (asc::std::uninitialized_default_construct_n(dst, 3) != dst + 3)
        return 7;
    asc::std::destroy(dst, dst + 3);
    asc::std::uninitialized_value_construct(dst, dst + 3);
    if (dst[0] || dst[1] || dst[2])
        return 8;
    asc::std::destroy(dst, dst + 3);
    if (asc::std::uninitialized_value_construct_n(dst, 3) != dst + 3 || dst[0] || dst[2])
        return 9;
    asc::std::destroy(dst, dst + 3);
    if (asc::std::uninitialized_move(src, src + 3, dst) != dst + 3 || dst[1] != -1)
        return 10;
    asc::std::destroy(dst, dst + 3);
    auto last = asc::std::uninitialized_move_n(src, 3, dst);
    if (last.first != src + 3 || last.second != dst + 3 || dst[2] != 7)
        return 11;
    asc::std::destroy(dst, dst + 3);
    if (asc::std::construct_at(dst, 11) != dst || *asc::std::addressof(*dst) != 11)
        return 12;
    asc::std::destroy_at(dst);
    return 0;
}
}  // namespace asc_stl_test_memory

#endif  // ASC_STL_TEST_MEMORY_DEVICE_CHECKS_H
