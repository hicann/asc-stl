# asc::std::vector

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

Header: `<asc/std/vector>`.

`asc::std::vector` holds a growable sequence of elements in contiguous storage.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Declaration

```cpp
namespace asc::std {
template<class T, class Allocator> class vector;
} // namespace asc::std
```

## Constraints

- Construction requires an explicit `Allocator` object; the allocator must be able to provide and free contiguous storage for `T`.
- The subscript passed to `operator[]` must be less than `size()`; the container must be non-empty before calling `front()`, `back()`, or `pop_back()`.
- Insertion may trigger capacity growth; the allocator and the element type must support the corresponding allocation, construction, and move operations. Capacity growth invalidates pointers, references, and iterators into the original storage.
- When used on the device side, the allocator and element operations being called must be available in the corresponding programming mode and must not throw; allocation must be guaranteed to succeed, or sufficient capacity must be reserved beforehand.
- The current move assignment frees the target's original storage, copies the source allocator, and takes over the source storage, leaving the source container empty; it does not select an element-by-element move path based on allocator propagation traits.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <memory>
#include <asc/std/vector>

bool example()
{
    asc::std::vector<int, ::std::allocator<int>> values(::std::allocator<int>{});
    values.push_back(1);
    values.push_back(3);
    values[1] = 7;
    return values.size() == 2 && values[0] == 1 && values[1] == 7;
}
```

## Related APIs

- [API list for this header](asc_std_vector.md)
