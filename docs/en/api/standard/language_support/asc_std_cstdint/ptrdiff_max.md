# PTRDIFF_MAX

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

Header: `<asc/std/cstdint>`.

`PTRDIFF_MAX` gives the bound of the integer type or size corresponding to `PTRDIFF`.

Standard semantics reference: [cppreference `cstdint`](https://en.cppreference.com/w/cpp/header/cstdint).

## Declaration

```cpp
#define PTRDIFF_MAX __PTRDIFF_MAX__
```

## Constraints

- Only the types and macros that actually exist in the Ascend 950 and Host ABIs are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cstdint>

#ifndef PTRDIFF_MAX
#error "PTRDIFF_MAX is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_std_cstdint.md)
