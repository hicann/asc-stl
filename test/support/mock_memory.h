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

#ifndef ASC_STL_TEST_SUPPORT_MOCK_MEMORY_H
#define ASC_STL_TEST_SUPPORT_MOCK_MEMORY_H

namespace asc_stl_test {

inline void copy_bytes(void* destination, const void* source, __SIZE_TYPE__ bytes)
{
    auto* output = static_cast<unsigned char*>(destination);
    const auto* input = static_cast<const unsigned char*>(source);
    for (__SIZE_TYPE__ index = 0; index < bytes; ++index) {
        output[index] = input[index];
    }
}

inline void move_bytes(void* destination, const void* source, __SIZE_TYPE__ bytes)
{
    auto* output = static_cast<unsigned char*>(destination);
    const auto* input = static_cast<const unsigned char*>(source);
    const auto output_address = reinterpret_cast<__UINTPTR_TYPE__>(output);
    const auto input_address = reinterpret_cast<__UINTPTR_TYPE__>(input);
    if (output_address < input_address || output_address >= input_address + bytes) {
        copy_bytes(destination, source, bytes);
        return;
    }
    for (__SIZE_TYPE__ index = bytes; index != 0; --index) {
        output[index - 1] = input[index - 1];
    }
}

inline void fill_bytes(void* destination, int value, __SIZE_TYPE__ bytes)
{
    auto* output = static_cast<unsigned char*>(destination);
    for (__SIZE_TYPE__ index = 0; index < bytes; ++index) {
        output[index] = static_cast<unsigned char>(value);
    }
}

}  // namespace asc_stl_test

#endif  // ASC_STL_TEST_SUPPORT_MOCK_MEMORY_H
