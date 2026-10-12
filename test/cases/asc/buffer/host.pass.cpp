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
#include <asc/buffer>
#include <asc/memory_pool>
#include <cassert>
#include <cstring>

namespace {
alignas(64) unsigned char device_storage[4096];
alignas(64) unsigned char pinned_storage[4096];
int active_device = 0;
int device_live = 0;
int pinned_live = 0;
bool event_done = true;
}  // namespace

extern "C" {
int aclrtGetDevice(int* device)
{
    *device = active_device;
    return 0;
}
int aclrtMalloc(void** pointer, __SIZE_TYPE__ bytes, int)
{
    if (bytes > sizeof(device_storage))
        return 7;
    static unsigned char* cursor = device_storage;
    if (cursor + bytes > device_storage + sizeof(device_storage))
        return 7;
    *pointer = cursor;
    cursor += bytes;
    ++device_live;
    return 0;
}
int aclrtFree(void* pointer)
{
    (void)pointer;
    --device_live;
    return 0;
}
int aclrtMallocHost(void** pointer, __SIZE_TYPE__ bytes)
{
    if (bytes > sizeof(pinned_storage))
        return 7;
    static unsigned char* pcursor = pinned_storage;
    if (pcursor + bytes > pinned_storage + sizeof(pinned_storage))
        return 7;
    *pointer = pcursor;
    pcursor += bytes;
    ++pinned_live;
    return 0;
}
int aclrtFreeHost(void* pointer)
{
    (void)pointer;
    --pinned_live;
    return 0;
}
int aclrtCreateEvent(void** event)
{
    *event = reinterpret_cast<void*>(0x1234);
    return 0;
}
int aclrtDestroyEvent(void* event)
{
    (void)event;
    return 0;
}
int aclrtRecordEvent(void* event, void* stream)
{
    (void)event;
    (void)stream;
    return 0;
}
int aclrtQueryEventStatus(void* event, int* status)
{
    (void)event;
    *status = event_done ? 1 : 0;
    return 0;
}
int aclrtSynchronizeEvent(void* event)
{
    (void)event;
    return 0;
}
int aclrtSynchronizeStream(void* stream)
{
    (void)stream;
    return 0;
}
int aclrtStreamQuery(void* s, int* status)
{
    (void)s;
    *status = 0;
    return 0;
}
int aclrtMemcpyAsync(
    void* destination, __SIZE_TYPE__ dsz, const void* source, __SIZE_TYPE__ bytes, int kind, void* stream)
{
    (void)dsz;
    (void)stream;
    if (kind == 3) {
        std::memmove(destination, source, bytes);
        return 0;
    }
    std::memcpy(destination, source, bytes);
    return 0;
}
int aclrtMemsetAsync(void* destination, __SIZE_TYPE__ dsz, int value, __SIZE_TYPE__ bytes, void* stream)
{
    (void)dsz;
    (void)stream;
    std::memset(destination, value, bytes);
    return 0;
}
}
int main()
{
    asc::device_memory_resource device{0};
    asc::device_memory_resource_ref resource{device};
    asc::stream_ref stream{reinterpret_cast<void*>(0x99)};

    // no-init, value, host range and host range with size forms.
    asc::device_buffer<int> buffer;
    assert(asc::make_device_buffer(buffer, resource, stream, 8).success());
    assert(buffer && buffer.size() == 8 && buffer.size_bytes() == 32 && !buffer.empty());
    assert(buffer.stream() == stream && buffer.resource() == resource);
    assert(asc::make_device_buffer(buffer, resource, stream, 4, 7).success());
    assert(buffer.size() == 4);
    const int source[4]{1, 2, 3, 4};
    assert(asc::make_device_buffer(buffer, resource, stream, source, source + 4).success());
    assert(buffer.size() == 4);
    assert(asc::make_device_buffer(buffer, resource, stream, source, 2).success());
    assert(buffer.size() == 2);
    // failure: zero count closes the output and reports invalid_argument
    // (replace semantics).
    assert(asc::make_device_buffer(buffer, resource, stream, 0).code() == asc::execution_errc::invalid_argument);
    assert(!buffer);
    assert(asc::make_device_buffer(buffer, resource, stream, 3, 9).success());
    assert(buffer && buffer.size() == 3);
    // move-only ownership transfer
    asc::device_buffer<int> moved{static_cast<asc::device_buffer<int>&&>(buffer)};
    assert(moved && !buffer);
    assert(moved.close().success() && !moved);
    assert(moved.close().success());

    asc::pinned_memory_resource pinned_resource{};
    asc::pinned_memory_resource_ref presource{pinned_resource};
    asc::pinned_buffer<int> staging;
    assert(asc::make_pinned_buffer(staging, presource, stream, 6, 42).success());
    assert(staging.size() == 6 && staging.data()[0] == 42 && staging.data()[5] == 42);
    assert(asc::make_pinned_buffer(staging, presource, stream, source, source + 4).success());
    assert(staging.size() == 4 && staging.data()[3] == 4);
    assert(asc::make_pinned_buffer(staging, presource, stream, source, 3).success());
    assert(staging.data()[2] == 3);
    assert(staging.close().success());
    assert(staging.close().success());
    assert(device_live == 0 && pinned_live == 0);
    return 0;
}
