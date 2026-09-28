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

#ifndef ASC_STL_TEST_ASC_STD_SOURCE_LOCATION_RUNTIME_HARDWARE_LAUNCH_H
#define ASC_STL_TEST_ASC_STD_SOURCE_LOCATION_RUNTIME_HARDWARE_LAUNCH_H

void launch_asc_stl_source_location_simd(__UINT32_TYPE__* output, void* stream);
void launch_asc_stl_source_location_simt(__UINT32_TYPE__* output, void* stream);

#endif  // ASC_STL_TEST_ASC_STD_SOURCE_LOCATION_RUNTIME_HARDWARE_LAUNCH_H
