# asc::std::atomic

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

`asc::std::atomic` reads and updates the stored atomic value according to the specified memory order.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

```cpp
namespace asc::std {
template<class T> class atomic;
} // namespace asc::std
```

## Constraints

- `T` must be an integer or character type supported by the current implementation, including `bool`; do not treat this template as a general-purpose atomic wrapper for arbitrary trivially copyable types.
- It can be called in Host and AI Core SIMT programming; calling atomic operations in AI Core SIMD programming is not supported.
- Atomic objects shared by the participating threads in SIMT must be placed in GM and initialized before concurrent access; GM atomic operations must not be performed on objects local to individual threads.
- `load`, `store`, and compare-exchange each have valid memory order requirements; see the individual member pages; construction and destruction of the object provide no concurrent synchronization.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> counter(1);
    const int previous = counter.fetch_add(2);
    return previous == 1 && counter.load() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
