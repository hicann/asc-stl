# asc::std::allocator_traits

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

`asc::std::allocator_traits` provides uniform access to an allocator's types, allocation, and object construction operations.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

```cpp
namespace asc::std {
template<class Allocator> struct allocator_traits;
} // namespace asc::std
```

## Constraints

- `Allocator` must provide `value_type`; the other associated types and traits are obtained through the detection and fallback rules of the corresponding members.
- The static allocation, construction, destruction, and release operations use the explicitly passed allocator; the execution location, allocatable address space, and exception requirements are determined by the specific operation.
- There is currently no `allocator_traits::allocate_at_least` member; at-least-capacity allocation uses the separate [`allocate_at_least`](allocate_at_least.md).

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <memory>
#include <asc/std/memory>

bool example()
{
    using Allocator = ::std::allocator<int>;
    using Traits = asc::std::allocator_traits<Allocator>;
    Allocator allocator;
    int* pointer = Traits::allocate(allocator, 1);
    Traits::construct(allocator, pointer, 7);
    const bool passed = *pointer == 7;
    Traits::destroy(allocator, pointer);
    Traits::deallocate(allocator, pointer, 1);
    return passed;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
