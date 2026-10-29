# asc::std::allocator_traits::max_size

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

`asc::std::allocator_traits::max_size` returns the theoretical maximum number of elements allowed by the container or allocator.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

Member of: [`asc::std::allocator_traits`](allocator_traits.md).

```cpp
// Declaration excerpt from inside the asc::std::allocator_traits class; template parameters and other members are provided by the enclosing class.
static constexpr size_type max_size(const allocator_type& allocator) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `allocator` | Input | The allocator responsible for allocating and releasing object storage. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_type` | Returns the theoretical maximum number of elements allowed by the container or allocator. |

## Constraints

- Uses the allocator's `max_size()` when available; otherwise returns `numeric_limits<size_type>::max() / sizeof(value_type)`.
- The result is a theoretical upper bound on the number of elements; it does not guarantee that many objects can currently be allocated; this function allocates no storage.

## Example

The following Host snippet uses an explicitly provided allocator and fully releases the storage; on the device side, an allocator callable at the target location must be used instead.

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

bool verify_example()
{
    example_allocator<int> allocator;
    return asc::std::allocator_traits<example_allocator<int>>::max_size(allocator) >= 1;
}
```

## Related APIs

- [`asc::std::allocator_traits`](allocator_traits.md)
- [API list for this header](asc_std_memory.md)
