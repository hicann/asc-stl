# asc::std::allocation_result

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

Header: `<asc/std/memory>`.

`asc::std::allocation_result` holds both the allocated pointer and the actual number of elements.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

```cpp
namespace asc::std {
template<class Pointer, class SizeType = asc::std::size_t> struct allocation_result;
} // namespace asc::std
```

## Constraints

- The aggregate stores the allocated address and the actual element capacity; this type does not take ownership and does not automatically construct, destroy, or release elements.
- `count` is measured in the number of elements of the type `Pointer` points to; release must follow the rules of the corresponding allocator.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/memory>

bool example()
{
    int values[3] = {};
    asc::std::allocation_result<int*> result{values, 3};
    return result.ptr == values && result.count == 3;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
