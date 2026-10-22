# asc::std::scoped_allocator_adaptor::size_type

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

Header: `<asc/std/scoped_allocator>`.

`asc::std::scoped_allocator_adaptor::size_type` identifies the unsigned type for container sizes.

Standard semantics reference: [cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator).

## Declaration

Member of: [`scoped_allocator_adaptor`](scoped_allocator_adaptor.md). This member is taken directly from the outer allocator; OuterAllocator must provide a type of the same name, with no fallback through allocator_traits.

```cpp
using size_type = typename OuterAllocator::size_type;
```

## Constraints

- This alias denotes the unsigned integer type the owning type uses for element counts or sizes; reading the type itself allocates no memory and accesses no elements.
- For the runtime conditions of construction, allocation, and access, see the owning type [asc::std::scoped_allocator_adaptor](scoped_allocator_adaptor.md).

## Example

The following Host snippet explicitly provides an allocator with rebind capability; on the device side, an allocator callable at the target execution location must be used instead.

```cpp
#include <asc/std/scoped_allocator>
#include <functional>
#include <memory>
#include <string>
#include <utility>

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

void use_type()
{
    using alias_type = typename asc::std::scoped_allocator_adaptor<example_allocator<int>>::size_type;
}
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
