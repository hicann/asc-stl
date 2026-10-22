# asc::pinned_memory_pool

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/memory_pool>`.

`asc::pinned_memory_pool` is a movable, non-copyable page-locked Host memory pool owner. Release operations reclaim memory in a deferred manner through Stream events; blocks whose use has completed can be reused up to the cache limit or returned to the underlying resource.

## Declaration

```cpp
namespace asc {
class pinned_memory_pool;
}  // namespace asc
```

## Constraints

- The Host software memory pool registers at most 64 concurrently retained blocks; when the table is full, new block requests return insufficient_storage, regardless of the device's remaining capacity.
- Allocate and asynchronously release using the same pool; a release must be ordered after all uses of that block on that Stream, and the block can be reused only after the retirement Event completes.
- All in-use blocks must be returned before close; on failure, unreleased blocks and valid ownership are retained, and the caller must handle the status and may retry.
- Device pool operations require the current Runtime Device to match the configured ordinal; concurrent operations are protected by a metadata lock, and the pool and Stream must remain valid during use.

## Example

The following Host example initializes the Runtime on device 0, checks the resource status, and closes the Runtime after the resource is released; running it requires CANN to be installed and the device to be available.

```cpp
#include <acl/acl.h>
#include <asc/memory_pool>

bool resource_example()
{
    asc::pinned_memory_pool pool;
    asc::pinned_memory_pool_config config{};
    if (!asc::pinned_memory_pool::create(pool, config).success())
        return false;
    const bool ready = pool.valid() && pool.statistics().reserved_bytes() == 0;
    const bool closed = pool.close().success();
    return ready && closed && !pool.valid();
}

bool example()
{
    if (aclInit(nullptr) != ACL_SUCCESS)
        return false;
    if (aclrtSetDevice(0) != ACL_SUCCESS) {
        const bool finalized = aclFinalize() == ACL_SUCCESS;
        return finalized && false;
    }
    const bool passed = resource_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return passed && reset && finalized;
}
```

## Related APIs

- [API list for this header](asc_memory_pool.md)
