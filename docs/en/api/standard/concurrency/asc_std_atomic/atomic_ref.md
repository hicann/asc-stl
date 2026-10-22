# asc::std::atomic_ref

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

`asc::std::atomic_ref` performs atomic operations on an existing object in a non-owning way.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

```cpp
namespace asc::std {
template<class T> class atomic_ref;
} // namespace asc::std
```

## Constraints

- `T` only supports 32-bit or 64-bit signed or unsigned integers without cv qualification; bool, floating-point, or arbitrary trivially copyable types are not accepted.

- The type, address space, scope, and memory order of the atomic object must match.
- 64-bit objects in the device scope are located in GM, and UB atomic operations only use memory_order_relaxed.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/atomic>

bool example()
{
    int value = 1;
    asc::std::atomic_ref<int> reference(value);
    reference.store(4);
    return value == 4;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
