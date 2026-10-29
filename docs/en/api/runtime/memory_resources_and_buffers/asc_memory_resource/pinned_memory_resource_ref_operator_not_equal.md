# asc::pinned_memory_resource_ref::`operator!=`

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

`asc::pinned_memory_resource_ref::operator!=` determines whether two references are not associated with the same `pinned_memory_resource` object.

## Function Prototype

Member of: [`asc::pinned_memory_resource_ref`](pinned_memory_resource_ref.md).

```cpp
// Excerpt of the declaration inside class asc::pinned_memory_resource_ref; template parameters and other members are provided by the owning class.
constexpr bool operator!=(const asc::pinned_memory_resource_ref& other) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The other operand of the comparison; this comparison does not modify the object. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- This operation synchronously observes or stores resource properties on the Host and does not submit allocations or releases.
- A resource reference does not own the referenced object; the resource object must still be valid when the allocate/deallocate members are used; comparison only determines whether the references are associated with the same object.

## Example

This Host example submits no Runtime work and checks configuration or resource-reference results using concrete values.

```cpp
#include <asc/memory_resource>

bool example()
{
    asc::pinned_memory_resource first;
    asc::pinned_memory_resource second;
    const asc::pinned_memory_resource_ref a(first);
    const asc::pinned_memory_resource_ref same(first);
    const asc::pinned_memory_resource_ref different(second);
    const asc::pinned_memory_resource_ref empty;
    const asc::pinned_memory_resource_ref another_empty;
    return !(a != same) && a != different && !(empty != another_empty);
}
```

## Related APIs

- [`asc::pinned_memory_resource_ref`](pinned_memory_resource_ref.md)
- [API list for this header](asc_memory_resource.md)
