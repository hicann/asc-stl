# UCHAR_MAX

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

Header: `<asc/std/climits>`.

`UCHAR_MAX` gives the limit value of the integer type or size corresponding to `UCHAR`.

Standard semantics reference: [cppreference `climits`](https://en.cppreference.com/w/cpp/header/climits).

## Declaration

```cpp
#define UCHAR_MAX 255
```

`unsigned char` is 8 bits on the current target; if the system header already defines this macro, the product keeps the system definition.

## Constraints

- Only macros actually supported by the compiler ABI are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/climits>

#ifndef UCHAR_MAX
#error "UCHAR_MAX is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_std_climits.md)
