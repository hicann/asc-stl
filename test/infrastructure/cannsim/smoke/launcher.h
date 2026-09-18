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

#ifndef CANN_ASC_STL_TEST_INFRASTRUCTURE_CANNSIM_SMOKE_LAUNCHER_H
#define CANN_ASC_STL_TEST_INFRASTRUCTURE_CANNSIM_SMOKE_LAUNCHER_H

#include <cstdint>

uint32_t launch_asc_stl_cannsim_add(void* stream, void* x, void* y, void* output);

#endif  // CANN_ASC_STL_TEST_INFRASTRUCTURE_CANNSIM_SMOKE_LAUNCHER_H
