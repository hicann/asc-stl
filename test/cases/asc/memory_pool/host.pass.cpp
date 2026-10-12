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
bool event_destroy_fails = false;
int event_destroy_calls = 0;
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
    ++event_destroy_calls;
    return event_destroy_fails ? 7 : 0;
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
    // create / allocate / event-safe reuse / statistics / trim / close.
    asc::device_memory_pool pool;
    asc::device_memory_pool_config config{0, 1 << 20, 1 << 18};
    assert(asc::device_memory_pool::create(pool, config).success());
    assert(pool.valid() && pool.device_ordinal() == 0);
    void* block = nullptr;
    asc::stream_ref stream{reinterpret_cast<void*>(0x99)};
    assert(pool.allocate_async(&block, 128, 32, stream).success() && block != nullptr);
    auto stats = pool.statistics();
    assert(stats.used_bytes() == 128 && stats.reserved_bytes() == 128 && stats.cached_bytes() == 0);
    event_done = false;
    assert(pool.deallocate_async(block, stream).success());
    // A pending block is not reused until its event reports completion.
    void* second = nullptr;
    assert(pool.allocate_async(&second, 128, 32, stream).success() && second != block);
    assert(pool.deallocate_async(second, stream).success());
    event_done = true;
    assert(pool.collect().success());
    void* reused = nullptr;
    assert(pool.allocate_async(&reused, 128, 32, stream).success());
    assert(reused == block || reused == second);
    stats = pool.statistics();
    assert(stats.used_bytes() == 128);
    assert(pool.deallocate_async(reused, stream).success());
    event_done = true;
    assert(pool.collect().success());
    // The release threshold keeps small cached blocks retained.
    assert(pool.trim_to(0).success());
    stats = pool.statistics();
    assert(stats.reserved_bytes() == 256 && stats.cached_bytes() == 256);
    assert(pool.close().success() && !pool.valid() && device_live == 0);
    // A pool with a zero release threshold releases everything on trim.
    asc::device_memory_pool_config eager{0, 1 << 20, 0};
    assert(asc::device_memory_pool::create(pool, eager).success());
    void* eager_block = nullptr;
    assert(pool.allocate_async(&eager_block, 128, 32, stream).success());
    assert(pool.deallocate_async(eager_block, stream).success());
    assert(pool.collect().success());
    assert(pool.trim_to(0).success());
    stats = pool.statistics();
    assert(stats.reserved_bytes() == 0);
    // failure paths
    void* bad = reinterpret_cast<void*>(1);
    assert(pool.deallocate_async(bad, stream).code() == asc::execution_errc::invalid_argument);
    void* null_output = nullptr;
    assert(pool.allocate_async(&null_output, 0, 32, stream).code() == asc::execution_errc::invalid_argument);
    assert(pool.close().success());
    // The configured maximum cache is a byte limit, not merely descriptive.
    asc::device_memory_pool_config no_cache{0, 0, 1 << 18};
    assert(asc::device_memory_pool::create(pool, no_cache).success());
    void* uncached = nullptr;
    assert(pool.allocate_async(&uncached, 128, 32, stream).success());
    assert(pool.deallocate_async(uncached, stream).success());
    assert(pool.collect().success());
    stats = pool.statistics();
    assert(stats.reserved_bytes() == 0 && stats.cached_bytes() == 0);
    assert(pool.close().success() && device_live == 0);
    // ref forwarding
    assert(asc::device_memory_pool::create(pool, config).success());
    asc::device_memory_pool_ref ref = pool.as_ref();
    assert(ref.valid() && (ref == pool.as_ref()));
    void* via_ref = nullptr;
    assert(ref.allocate_async(&via_ref, 64, 32, stream).success());
    assert(pool.deallocate_async(via_ref, stream).success());
    event_destroy_fails = true;
    const int live_before_failed_close = device_live;
    assert(pool.close().code() == asc::execution_errc::backend_error);
    assert(pool.valid() && device_live == live_before_failed_close);
    stats = pool.statistics();
    assert(stats.reserved_bytes() == 64);
    assert(asc::device_memory_pool::create(pool, config).code() == asc::execution_errc::backend_error);
    assert(pool.valid() && device_live == live_before_failed_close);
    event_destroy_fails = false;
    assert(pool.close().success() && !pool.valid() && device_live == 0);
    assert(event_destroy_calls > 0);
    asc::device_memory_pool_ref empty_ref;
    assert(!empty_ref.valid());
    assert(empty_ref.collect().code() == asc::execution_errc::invalid_argument);

    // pinned pool: same software backend over pinned staging memory.
    asc::pinned_memory_pool pinned;
    asc::pinned_memory_pool_config pconfig{1 << 18, 1 << 16};
    assert(asc::pinned_memory_pool::create(pinned, pconfig).success());
    void* staged = nullptr;
    assert(pinned.allocate_async(&staged, 256, 8, stream).success());
    assert(pinned.deallocate_async(staged, stream).success());
    event_done = true;
    assert(pinned.collect().success());
    assert(pinned.close().success() && pinned_live == 0);
    return 0;
}
