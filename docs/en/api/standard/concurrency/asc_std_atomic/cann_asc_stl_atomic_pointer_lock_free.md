# CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE

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

Header: `<asc/std/atomic>`.

`CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE` reports the capability level of whether the corresponding atomic type always uses a lock-free implementation.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

```cpp
#define CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE 0
```

## Constraints

- This macro is fixed to `0`; the current [atomic](atomic.md) does not support pointer-type specializations.
- This macro is a compile-time constant and performs no atomic operation; reading the macro value does not depend on the object's address space.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

static_assert(CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE == 0);
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
