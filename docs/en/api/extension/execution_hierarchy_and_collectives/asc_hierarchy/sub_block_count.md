# asc::sub_block_count

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

Header: `<asc/hierarchy>`.

`asc::sub_block_count` returns the number of sub blocks available in the current AI Core.

## Function Prototype

```cpp
namespace asc {
unsigned int sub_block_count() noexcept;
} // namespace asc
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the number of units in the enclosing execution hierarchy level. |

## Constraints

- Can only be called in AI Core SIMD programming.
- The parameter types, address spaces, value ranges, and object lifetimes must satisfy the declaration on this page.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/hierarchy>

__aicore__ decltype(auto) example()
{
    return asc::sub_block_count();
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
