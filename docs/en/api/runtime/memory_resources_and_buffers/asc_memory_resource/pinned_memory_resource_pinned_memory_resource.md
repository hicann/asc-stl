# asc::pinned_memory_resource::pinned_memory_resource

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

The `asc::pinned_memory_resource` default constructor creates a stateless page-locked Host memory resource object.

## Function Prototype

Member of: [`asc::pinned_memory_resource`](pinned_memory_resource.md).

```cpp
// Excerpt of the declaration inside class asc::pinned_memory_resource; template parameters and other members are provided by the owning class.
constexpr pinned_memory_resource() noexcept;
```

## Parameters

No parameters.

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
    asc::pinned_memory_resource resource;
    auto properties = resource.properties();
    return properties.host_accessible() && !properties.device_accessible() &&
        properties.maximum_alignment() == alignof(asc::std::max_align_t);
}
```

## Related APIs

- [`asc::pinned_memory_resource`](pinned_memory_resource.md)
- [API list for this header](asc_memory_resource.md)
