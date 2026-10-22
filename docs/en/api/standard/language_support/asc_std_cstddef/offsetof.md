# offsetof

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

Header: `<asc/std/cstddef>`.

`offsetof` computes the byte offset of a given member relative to the start address of a standard-layout type object.

Standard semantics reference: [cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef).

## Declaration

```cpp
#define offsetof(type, member) __builtin_offsetof(type, member)
```

## Constraints

- The standard declaration is provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cstddef>

#ifndef offsetof
#error "offsetof is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_std_cstddef.md)
