# asc::std::deque::size_type

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

Header: `<asc/std/deque>`.

`asc::std::deque::size_type` identifies the unsigned type for the container size.

Standard semantics reference: [cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque).

## Declaration

Member of: [`asc::std::deque`](deque.md).

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
using size_type = unsigned long;
```

## Constraints

- This alias is the unsigned integer type the owning type uses for element counts or sizes; reading the type itself neither allocates memory nor accesses elements.
- For the runtime conditions for construction, allocation, and access, see the owning type [asc::std::deque](deque.md).

## Example

The following Host snippet explicitly provides an allocator with rebinding capability; on the device side, an allocator callable at the target execution location must be used instead.

```cpp
#include <asc/std/deque>
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
    using alias_type = typename asc::std::deque<int, example_allocator<int>>::size_type;
}
```

## Related APIs

- [`asc::std::deque`](deque.md)
- [API list for this header](asc_std_deque.md)
