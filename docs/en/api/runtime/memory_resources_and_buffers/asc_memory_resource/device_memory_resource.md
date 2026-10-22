# asc::device_memory_resource

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

Header: `<asc/memory_resource>`.

`asc::device_memory_resource` allocates and releases global memory directly on the specified Device. When called, that Device must be the current Runtime Device.

## Declaration

```cpp
namespace asc {
class device_memory_resource;
} // namespace asc
```

## Constraints

- May only be called on Host.
- The memory resource does not throw exceptions.
- The allocation size, alignment, and output pointer must be valid, and deallocation must use the same resource with the original size and alignment.
- The lifetimes of the resource and its references are managed by the caller.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory_resource>

bool example()
{
    asc::device_memory_resource resource(0);
    auto properties = resource.properties();
    return resource.device_ordinal() == 0 && !properties.host_accessible() && properties.device_accessible() && properties.maximum_alignment() == 32;
}
```

## Related APIs

- [API list for this header](asc_memory_resource.md)
