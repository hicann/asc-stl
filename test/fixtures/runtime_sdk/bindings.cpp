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

#if defined(ASC_STL_TEST_SDK_FIRST)
#include <acl/acl_rt.h>
#endif

#if defined(ASC_STL_TEST_REVERSE_HEADERS)
#include <asc/memory_resource>
#include <asc/__algorithm/byte_operations.h>
#else
#include <asc/__algorithm/byte_operations.h>
#include <asc/memory_resource>
#endif

#if defined(ASC_STL_TEST_SDK_LAST)
// The separate fixture mode checks SDK inclusion after the product headers.
#include <acl/acl_rt.h>  // NOLINT(build/include)
#endif
#if defined(ASC_STL_TEST_SDK_ABSENT) && defined(INC_EXTERNAL_ACL_ACL_RT_H_)
#error "The SDK-absent regression unexpectedly found an SDK header"
#endif

#if defined(INC_EXTERNAL_ACL_ACL_RT_H_)
using stream_status = aclrtStreamStatus;
using event_status = aclrtEventRecordedStatus;
using device_attribute = aclrtDevAttr;
using allocation_policy = aclrtMemMallocPolicy;
using copy_kind = aclrtMemcpyKind;
#else
using stream_status = int;
using event_status = int;
using device_attribute = int;
using allocation_policy = int;
using copy_kind = int;
#endif

namespace {
int stream_token, event_token, allocation_token;
stream_status stream_state = static_cast<stream_status>(0);
event_status event_state = static_cast<event_status>(1);
int query_error, last_copy_kind = -1, last_allocation_policy = -1;
unsigned queried_attributes;
}  // namespace

extern "C" int aclrtSynchronizeStream(void* stream)
{
    return stream == &stream_token ? 0 : 1;
}
extern "C" int aclrtStreamQuery(void*, stream_status* output)
{
    if (query_error)
        return query_error;
    *output = stream_state;
    return 0;
}
extern "C" int aclrtStreamGetPriority(void*, unsigned* output)
{
    *output = 3;
    return 0;
}
extern "C" int aclrtStreamWaitEvent(void*, void*)
{
    return 0;
}
extern "C" int aclrtRecordEvent(void*, void*)
{
    return 0;
}
extern "C" int aclrtSynchronizeEvent(void* event)
{
    return event == &event_token ? 0 : 1;
}
extern "C" int aclrtQueryEventStatus(void*, event_status* output)
{
    if (query_error)
        return query_error;
    *output = event_state;
    return 0;
}
extern "C" int aclrtCreateStreamWithConfig(void** output, unsigned, unsigned)
{
    *output = &stream_token;
    return 0;
}
extern "C" int aclrtDestroyStream(void* stream)
{
    return stream == &stream_token ? 0 : 1;
}
extern "C" int aclrtCreateEvent(void** output)
{
    *output = &event_token;
    return 0;
}
extern "C" int aclrtDestroyEvent(void* event)
{
    return event == &event_token ? 0 : 1;
}
extern "C" int aclrtEventElapsedTime(float* output, void*, void*)
{
    *output = 2.5F;
    return 0;
}
extern "C" int aclrtGetDeviceCount(asc::std::uint32_t* output)
{
    *output = 1;
    return 0;
}
extern "C" int aclrtGetDevice(int* output)
{
    *output = 0;
    return 0;
}
extern "C" int aclrtSetDevice(int ordinal)
{
    return ordinal == 0 ? 0 : 1;
}
extern "C" int aclrtGetDeviceInfo(asc::std::uint32_t, device_attribute attribute, asc::std::int64_t* output)
{
    ++queried_attributes;
    switch (static_cast<int>(attribute)) {
        case 101:
            *output = 4;
            break;
        case 201:
            *output = 8;
            break;
        case 202:
            *output = 32;
            break;
        case 209:
            *output = 256;
            break;
        case 204:
            *output = 262144;
            break;
        case 301:
            *output = 1073741824;
            break;
        case 302:
            *output = 1048576;
            break;
        case 601:
            *output = 3510;
            break;
        default:
            return 1;
    }
    return 0;
}
extern "C" int aclrtMalloc(void** output, __SIZE_TYPE__, allocation_policy policy)
{
    last_allocation_policy = static_cast<int>(policy);
    *output = &allocation_token;
    return 0;
}
extern "C" int aclrtFree(void* pointer)
{
    return pointer == &allocation_token ? 0 : 1;
}
extern "C" int aclrtMallocHost(void** output, __SIZE_TYPE__)
{
    *output = &allocation_token;
    return 0;
}
extern "C" int aclrtFreeHost(void* pointer)
{
    return pointer == &allocation_token ? 0 : 1;
}
extern "C" int aclrtMemcpyAsync(void*, __SIZE_TYPE__, const void*, __SIZE_TYPE__, copy_kind kind, void*)
{
    last_copy_kind = static_cast<int>(kind);
    return 0;
}
extern "C" int aclrtMemsetAsync(void*, __SIZE_TYPE__, int, __SIZE_TYPE__, void*)
{
    return 0;
}

namespace {
struct bindings_context {
    asc::stream stream;
    asc::event event;
};

int check_stream_and_event_states(asc::stream& stream, asc::event& event)
{
    if (!asc::make_stream(stream, 3) || !asc::make_event(event))
        return 1;
    bool done = false;
    if (!stream.is_done(done) || !done || !event.is_done(done) || !done)
        return 2;
    stream_state = static_cast<stream_status>(1);
    event_state = static_cast<event_status>(0);
    if (!stream.is_done(done) || done || !event.is_done(done) || done)
        return 3;
    query_error = 9;
    done = true;
    if (stream.is_done(done) || !done || event.is_done(done) || !done)
        return 4;
    query_error = 0;
    return 0;
}

int check_device_properties()
{
    asc::device_properties properties{};
    if (!asc::device_ref(0).properties(properties) || queried_attributes != 8 || properties.aicore_count != 4 ||
        properties.vector_core_count != 8 || properties.warp_size != 32 ||
        properties.maximum_threads_per_block != 256 || properties.unified_buffer_bytes_per_vector_core != 262144 ||
        properties.total_global_memory_bytes != 1073741824 || properties.l2_cache_bytes != 1048576 ||
        properties.architecture != asc::npu_arch::ascend_3510)
        return 5;
    return 0;
}

int check_copy_and_allocation(asc::stream& stream)
{
    int source = 1, destination = 0;
    if (!asc::copy_bytes(stream, &destination, &source, sizeof(source)).success() || last_copy_kind != 4)
        return 6;
    asc::device_memory_resource resource(0);
    void* memory = nullptr;
    if (!resource.allocate(&memory, 32).success() || memory != &allocation_token || last_allocation_policy != 0)
        return 7;
    if (!resource.deallocate(memory, 32).success())
        return 8;
    return 0;
}
}  // namespace

int main()
{
    bindings_context context;
    int result = check_stream_and_event_states(context.stream, context.event);
    if (result != 0)
        return result;
    result = check_device_properties();
    if (result != 0)
        return result;
    result = check_copy_and_allocation(context.stream);
    if (result != 0)
        return result;
    return context.stream.close() && context.event.close() ? 0 : 9;
}
