# asc::std::allocator_traits::propagate_on_container_swap

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

`asc::std::allocator_traits::propagate_on_container_swap` identifies whether the corresponding container copy, move, or swap operation propagates the allocator.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

`asc::std::allocator_traits<Allocator>::propagate_on_container_swap` prefers Allocator's own member type of the same name; otherwise it is false_type.

```cpp
template<class Allocator>
using selected = typename asc::std::allocator_traits<Allocator>::propagate_on_container_swap;
```

## Constraints

- This page is a compile-time type query on allocator traits; it allocates no storage and constructs no objects.
- The extraction and fallback rules for the corresponding member are described in [`allocator_traits`](allocator_traits.md); a concrete allocator must satisfy the queried member or rebind form requirements.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/memory>
#include <asc/std/type_traits>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

using selected = typename asc::std::allocator_traits<example_allocator<int>>::propagate_on_container_swap;

static_assert(selected::value == false);
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [allocator_traits.cpp](../../../../../../examples/standard/allocator_traits/main.cpp).

## Related APIs

- [API list for this header](asc_std_memory.md)
