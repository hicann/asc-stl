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

#ifndef ASC_STL_TEST_RANGES_RUNTIME_CONFIG_H
#define ASC_STL_TEST_RANGES_RUNTIME_CONFIG_H
namespace asc_stl_ranges_runtime {
inline constexpr int storage_length = 1024;
inline constexpr int path_length = 384;
inline constexpr int result_count = path_length * 2;
inline constexpr int poison = 1111;
inline constexpr int lengths[] = {0, 1, 2, 3, 4, 7, 16, 32};
inline constexpr int case_count = sizeof(lengths) / sizeof(lengths[0]);
inline constexpr int input_count = case_count * storage_length;
inline constexpr int output_count = case_count * result_count;
// Projection and swap fixtures are independent of the variable input length.
inline constexpr int projection_keys[] = {3, 1, 4, 2};
inline constexpr int projection_count = sizeof(projection_keys) / sizeof(projection_keys[0]);
inline constexpr int projection_find_key = 1;
inline constexpr int projection_contains_key = 2;
inline constexpr int swap_left = 5;
inline constexpr int swap_right = 9;
}  // namespace asc_stl_ranges_runtime
#endif  // ASC_STL_TEST_RANGES_RUNTIME_CONFIG_H
