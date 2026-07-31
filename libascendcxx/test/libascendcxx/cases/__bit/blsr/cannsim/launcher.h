/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef LIBASCENDCXX_TEST_LIBASCENDCXX_CASES___BIT_BLSR_CANNSIM_LAUNCHER_H_
#define LIBASCENDCXX_TEST_LIBASCENDCXX_CASES___BIT_BLSR_CANNSIM_LAUNCHER_H_

#include <cstdint>

uint32_t asc_std_blsr_do(uint32_t core_num, void* stream, uint8_t* in0_dev, uint8_t* out0_dev);

#endif  // LIBASCENDCXX_TEST_LIBASCENDCXX_CASES___BIT_BLSR_CANNSIM_LAUNCHER_H_
