# asc::std::atomic_long

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

`asc::std::atomic_long` binds the specified fundamental integer or boolean type to the atomic type alias delivered in the current release.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

```cpp
namespace asc::std {
using atomic_long = atomic<long>;
} // namespace asc::std
```

## Constraints

- This alias denotes an [atomic](atomic.md) object of the corresponding integer or character type; construction of the object and atomic operations can be performed in Host or AI Core SIMT programming.
- Atomic objects shared by SIMT threads must be placed in GM and initialized before concurrent access; declaring the alias alone does not access storage.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_long cell{};
    cell.store(1, asc::std::memory_order_relaxed);
    return cell.load(asc::std::memory_order_relaxed) == 1;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
