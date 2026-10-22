# asc::device_memory_pool_ref

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

`asc::device_memory_pool_ref` is a non-owning reference to a `device_memory_pool`, forwarding asynchronous allocation, deferred reclamation, cache compaction, and statistics operations; the referenced memory pool must remain valid during its use.

This interface is available on Host.

## Declaration

```cpp
namespace asc {
class device_memory_pool_ref;
} // namespace asc
```

## Constraints

- Provides a software memory pool, collect, trim, stats, and Event-safe reuse.

## Example

The following Host example initializes the Runtime on device 0, checks the resource status, and closes the Runtime after the resource is released; running it requires CANN to be installed and the device to be available.

```cpp
#include <acl/acl.h>
#include <asc/memory_pool>

bool resource_example()
{
    asc::device_memory_pool pool;
    asc::device_memory_pool_config config{};
    if (!asc::device_memory_pool::create(pool, config).success()) return false;
    asc::device_memory_pool_ref view(pool);
    const bool ready = view.valid() && view.statistics().reserved_bytes() == 0;
    const bool closed = pool.close().success();
    return ready && closed && !pool.valid();
}

bool example()
{
    if (aclInit(nullptr) != ACL_SUCCESS) return false;
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
