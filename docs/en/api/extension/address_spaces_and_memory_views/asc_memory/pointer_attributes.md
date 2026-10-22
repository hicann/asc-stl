# asc::pointer_attributes

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

Header: `<asc/memory>`.

`asc::pointer_attributes` stores the memory space a pointer resides in, Host/Device accessibility, and the byte count of the owning allocation.

## Declaration

```cpp
namespace asc {
class pointer_attributes;
} // namespace asc
```

## Constraints

- The attributes object only describes the query result; it does not own or extend the lifetime of the pointer or its underlying allocation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>

bool example()
{
    asc::pointer_attributes attributes;
    return attributes.space == asc::memory_space::local;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
