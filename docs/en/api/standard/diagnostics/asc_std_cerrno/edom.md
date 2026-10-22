# EDOM

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

Header: `<asc/std/cerrno>`.

`EDOM` indicates a domain error of a mathematical function.

This interface is available on Host (full interface) and Device (constant interfaces).

Standard semantics reference: [cppreference `cerrno`](https://en.cppreference.com/w/cpp/header/cerrno).

## Declaration

```cpp
#define EDOM 33
```

## Constraints

- Host fully delivers the standard modifiable errno state and EDOM/EILSEQ/ERANGE.
- Device delivers EDOM/EILSEQ/ERANGE as three positive int constant expressions, with the fixed product ABI values 33/84/34.
- Host provides the full interface, and the device side provides only the listed constants.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cerrno>

#ifndef EDOM
#error "EDOM is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_std_cerrno.md)
