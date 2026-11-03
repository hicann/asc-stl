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

#ifndef ASC_STL_TEST_BOUNDS_RUNTIME_CONFIG_H
#define ASC_STL_TEST_BOUNDS_RUNTIME_CONFIG_H
namespace asc_stl_bounds_runtime {
inline constexpr int storage_length = 288;
inline constexpr int length_count = 21;
inline constexpr int query_count = 64;
inline constexpr int result_count = length_count * query_count * 4;
}  // namespace asc_stl_bounds_runtime
#endif  // ASC_STL_TEST_BOUNDS_RUNTIME_CONFIG_H
