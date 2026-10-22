# CANN_ASC_STL_ATOMIC_VAR_INIT

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

`CANN_ASC_STL_ATOMIC_VAR_INIT` provides the static initialization form for atomic objects.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

```cpp
#define CANN_ASC_STL_ATOMIC_VAR_INIT(value) {value}
```

## Constraints

- This macro expands to an initializer list containing the given value; the value type must be suitable for the [atomic](atomic.md) object being initialized.
- Initialization is available only in Host or AI Core SIMT programming and must complete before other threads access concurrently; SIMT-shared objects must be located in GM.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

#ifndef CANN_ASC_STL_ATOMIC_VAR_INIT
#error "CANN_ASC_STL_ATOMIC_VAR_INIT is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
