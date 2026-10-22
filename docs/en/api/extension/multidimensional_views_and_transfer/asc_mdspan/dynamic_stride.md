# asc::dynamic_stride

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

Header: `<asc/mdspan>`.

`asc::dynamic_stride` is a marker value for a dynamic stride of an mdspan supplied at run time.

## Declaration

```cpp
namespace asc {
inline constexpr asc::std::ptrdiff_t dynamic_stride = (-__PTRDIFF_MAX__ - 1);
}  // namespace asc
```

## Constraints

- This compile-time marker equals the minimum value of ptrdiff_t; it identifies a run-time stride slot and is not an ordinary static stride value.


## Example

The following snippet shows the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/mdspan>

auto value = asc::dynamic_stride;
```

## Related APIs

- [API list for this header](asc_mdspan.md)
