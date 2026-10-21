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

#ifndef INC_EXTERNAL_ACL_ACL_RT_H_
#define INC_EXTERNAL_ACL_ACL_RT_H_

// Explicit offline ABI-shaped fixture, selected only by the regression script.
// Enum facts were read from CANN 9.2.0-beta.2 acl_rt.h, SHA256
// f4e1661220b0faf105e6a4e7fdfb038caea2cbcdcf1589b719d68d169d6079da.
// Passing this fixture does not establish compatibility with an installed SDK.
#include <cstddef>
#include <cstdint>

using aclError = int;
using aclrtStream = void*;
using aclrtEvent = void*;
enum aclrtStreamStatus {
    ACL_STREAM_STATUS_COMPLETE = 0,
    ACL_STREAM_STATUS_NOT_READY = 1,
    ACL_STREAM_STATUS_RESERVED = 0xffff
};
enum aclrtEventRecordedStatus { ACL_EVENT_RECORDED_STATUS_NOT_READY = 0, ACL_EVENT_RECORDED_STATUS_COMPLETE = 1 };
enum aclrtDevAttr {
    ACL_DEV_ATTR_AICORE_CORE_NUM = 101,
    ACL_DEV_ATTR_VECTOR_CORE_NUM = 201,
    ACL_DEV_ATTR_WARP_SIZE = 202,
    ACL_DEV_ATTR_MAX_THREADS_PER_BLOCK = 209,
    ACL_DEV_ATTR_UBUF_PER_VECTOR_CORE = 204,
    ACL_DEV_ATTR_TOTAL_GLOBAL_MEM_SIZE = 301,
    ACL_DEV_ATTR_L2_CACHE_SIZE = 302,
    ACL_DEV_ATTR_NPU_ARCH = 601
};
enum aclrtMemMallocPolicy { ACL_MEM_MALLOC_HUGE_FIRST = 0 };
enum aclrtMemcpyKind {
    ACL_MEMCPY_HOST_TO_HOST = 0,
    ACL_MEMCPY_HOST_TO_DEVICE = 1,
    ACL_MEMCPY_DEVICE_TO_HOST = 2,
    ACL_MEMCPY_DEVICE_TO_DEVICE = 3,
    ACL_MEMCPY_DEFAULT = 4
};
extern "C" {
aclError aclrtSynchronizeStream(aclrtStream);
aclError aclrtStreamQuery(aclrtStream, aclrtStreamStatus*);
aclError aclrtStreamGetPriority(aclrtStream, std::uint32_t*);
aclError aclrtStreamWaitEvent(aclrtStream, aclrtEvent);
aclError aclrtRecordEvent(aclrtEvent, aclrtStream);
aclError aclrtSynchronizeEvent(aclrtEvent);
aclError aclrtQueryEventStatus(aclrtEvent, aclrtEventRecordedStatus*);
aclError aclrtCreateStreamWithConfig(aclrtStream*, std::uint32_t, std::uint32_t);
aclError aclrtDestroyStream(aclrtStream);
aclError aclrtCreateEvent(aclrtEvent*);
aclError aclrtDestroyEvent(aclrtEvent);
aclError aclrtEventElapsedTime(float*, aclrtEvent, aclrtEvent);
aclError aclrtGetDeviceCount(std::uint32_t*);
aclError aclrtGetDevice(int*);
aclError aclrtSetDevice(int);
aclError aclrtGetDeviceInfo(std::uint32_t, aclrtDevAttr, std::int64_t*);
aclError aclrtMalloc(void**, std::size_t, aclrtMemMallocPolicy);
aclError aclrtFree(void*);
aclError aclrtMallocHost(void**, std::size_t);
aclError aclrtFreeHost(void*);
aclError aclrtMemcpyAsync(void*, std::size_t, const void*, std::size_t, aclrtMemcpyKind, aclrtStream);
aclError aclrtMemsetAsync(void*, std::size_t, int, std::size_t, aclrtStream);
}

#endif  // INC_EXTERNAL_ACL_ACL_RT_H_
