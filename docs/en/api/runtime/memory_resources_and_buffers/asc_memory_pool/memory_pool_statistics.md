# asc::memory_pool_statistics

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

`asc::memory_pool_statistics` is a snapshot of the memory pool state, recording separately the number of reserved bytes held from the underlying resource, the number currently in use by the caller, and the number reserved but not held by the caller (including pending blocks whose Event has not yet completed, which does not mean they are immediately reusable).

This interface is available on Host.

## Declaration

```cpp
namespace asc {
class memory_pool_statistics;
}  // namespace asc
```

## Constraints

- Provides a software memory pool, collect, trim, stats, and Event-safe reuse.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory_pool>

bool example()
{
    asc::memory_pool_statistics statistics(128, 32, 96);
    return statistics.reserved_bytes() == 128 && statistics.used_bytes() == 32 && statistics.cached_bytes() == 96;
}
```

## Related APIs

- [API list for this header](asc_memory_pool.md)
