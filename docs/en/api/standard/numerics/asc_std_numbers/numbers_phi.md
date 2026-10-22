# asc::std::numbers::phi

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

Header: `<asc/std/numbers>`.

`asc::std::numbers::phi` provides the compile-time value of the golden ratio.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `numbers`](https://en.cppreference.com/w/cpp/header/numbers).

## Declaration

```cpp
namespace asc::std::numbers {
inline constexpr double phi = 0x1.9e3779b97f4a7c15f39cc0605ceep+0;
}
```

## Constraints

- 13 standard named double constants.
- Usable on Host and in AI Core SIMT programming; objects participating in the operation and their storage must be valid at the corresponding execution location.
- On a regular AI Core, only uses that involve no runtime double after constant folding.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/numbers>

auto value = asc::std::numbers::phi;
```

## Related APIs

- [API list for this header](asc_std_numbers.md)
