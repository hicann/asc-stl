# asc::device_memory_resource::properties

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

`asc::device_memory_resource::properties` returns the device memory resource properties: not directly accessible from the Host, accessible from the device, with a maximum alignment of 32 bytes.

## Function Prototype

Member of: [`asc::device_memory_resource`](device_memory_resource.md).

```cpp
// Excerpt of the declaration inside class asc::device_memory_resource; template parameters and other members are provided by the owning class.
static constexpr asc::memory_resource_properties properties() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::memory_resource_properties` | Returns the device memory resource properties: not directly accessible from the Host, accessible from the device, with a maximum alignment of 32 bytes. |

## Constraints

- This operation synchronously observes or stores resource properties on the Host and does not submit allocations or releases.
- A resource reference does not own the referenced object; the resource object must still be valid when the allocate/deallocate members are used; comparison only determines whether the references are associated with the same object.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory_resource>

bool example()
{
    asc::device_memory_resource resource(0);
    auto properties = resource.properties();
    return resource.device_ordinal() == 0 && !properties.host_accessible() && properties.device_accessible() &&
        properties.maximum_alignment() == 32;
}
```

## Related APIs

- [`asc::device_memory_resource`](device_memory_resource.md)
- [API list for this header](asc_memory_resource.md)
