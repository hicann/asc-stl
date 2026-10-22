# asc::memory_resource_properties::memory_resource_properties

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

The `asc::memory_resource_properties` constructor stores three resource properties: Host accessibility, device accessibility, and maximum byte alignment.

## Function Prototype

Member of: [`asc::memory_resource_properties`](memory_resource_properties.md).

```cpp
// Excerpt of the declaration inside class asc::memory_resource_properties; template parameters and other members are provided by the owning class.
constexpr memory_resource_properties(
    bool host_accessible, bool device_accessible, asc::std::size_t maximum_alignment) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `host_accessible` | Input | Whether the resource is Host accessible: whether memory allocated by this resource can be read and written directly by the Host. |
| `device_accessible` | Input | Whether the resource is device accessible: whether memory allocated by this resource can be read and written directly by the device (AI Core). |
| `maximum_alignment` | Input | Maximum byte alignment supported by the resource (for example 64): the alignment requested by allocate must not exceed this value. |

## Return Value

No return value.

## Constraints

- This operation synchronously observes or stores resource properties on the Host and does not submit allocations or releases.
- A resource reference does not own the referenced object; the resource object must still be valid when the allocate/deallocate members are used; comparison only determines whether the references are associated with the same object.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory_resource>

bool example()
{
    asc::memory_resource_properties properties(true, false, 64);
    return properties.host_accessible() && !properties.device_accessible() && properties.maximum_alignment() == 64;
}
```

## Related APIs

- [`asc::memory_resource_properties`](memory_resource_properties.md)
- [API list for this header](asc_memory_resource.md)
