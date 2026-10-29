# INFINITY

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

Header: `<asc/std/cmath>`.

`INFINITY` provides the positive infinity constant of type float (macro).

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Declaration

```cpp
#define INFINITY (__builtin_huge_valf())
```

This macro produces positive `float` infinity; when a system header already provides the macro, the system definition is kept.

## Constraints

- Provides the float function overloads, evaluation-type aliases, comparison functions, nanf, and classification macros.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cmath>

#ifndef INFINITY
#error "INFINITY is required by this public Header"
#endif

bool verify_example()
{
    const float value = INFINITY;
    return value > 0.0f && asc::std::isinf(value);
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
