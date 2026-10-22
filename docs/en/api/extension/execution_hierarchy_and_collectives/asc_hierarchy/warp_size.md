# asc::warp_size

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

`asc::warp_size` defines the number of lanes in a warp, currently 32.

## Declaration

```cpp
namespace asc {
inline constexpr unsigned int warp_size = 32;
} // namespace asc
```

## Constraints

- Can be used on the Host, in AI Core SIMD programming, and in AI Core SIMT programming.
- The types, address spaces, value ranges, and object lifetimes of the selected overload must satisfy its public declaration.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/hierarchy>

auto value = asc::warp_size;
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
