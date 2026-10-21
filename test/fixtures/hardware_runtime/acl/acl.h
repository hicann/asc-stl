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

#ifndef ASC_STL_TEST_FIXTURES_HARDWARE_RUNTIME_ACL_H
#define ASC_STL_TEST_FIXTURES_HARDWARE_RUNTIME_ACL_H

// Explicit offline ABI-shaped fixture; never a replacement for an installed SDK.
#include <cstdint>
using aclError = int;
using aclrtStream = void*;
constexpr aclError ACL_SUCCESS = 0;

extern "C" {
aclError aclInit(const char* config);
aclError aclFinalize();
aclError aclrtSetDevice(int device);
aclError aclrtResetDevice(int device);
aclError aclrtSetOpExecuteTimeOut(std::uint32_t seconds);
aclError aclrtSynchronizeStreamWithTimeout(aclrtStream stream, std::int32_t timeout);
aclError aclrtFree(void* pointer);
aclError aclrtDestroyStream(aclrtStream stream);
}

#endif  // ASC_STL_TEST_FIXTURES_HARDWARE_RUNTIME_ACL_H
