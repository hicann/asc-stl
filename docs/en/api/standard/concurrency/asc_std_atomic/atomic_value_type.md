# asc::std::atomic::value_type

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

`asc::std::atomic::value_type` identifies the value type of the element or result.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

Member of: [`asc::std::atomic`](atomic.md).

```cpp
// Excerpt of the declaration inside the asc::std::atomic class; template parameters and other members are provided by the enclosing class.
using value_type = T;
```

## Constraints

- This alias is exactly the atomic template parameter `T`; `T` must be an integer or character type supported by [atomic](atomic.md), including `bool`.
- Reading this alias does not access the atomic object and does not require GM storage.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

void use_type()
{
    using alias_type = typename asc::std::atomic<int>::value_type;
}
```

## Related APIs

- [`asc::std::atomic`](atomic.md)
- [API list for this header](asc_std_atomic.md)
