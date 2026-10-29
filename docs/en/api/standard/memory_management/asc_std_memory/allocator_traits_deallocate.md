# asc::std::allocator_traits::deallocate

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

`asc::std::allocator_traits::deallocate` releases previously requested storage through the corresponding allocator.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

Member of: [`asc::std::allocator_traits`](allocator_traits.md).

```cpp
// Declaration excerpt from inside the asc::std::allocator_traits class; template parameters and other members are provided by the enclosing class.
static constexpr void deallocate(allocator_type& allocator, pointer pointer, size_type count) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `allocator` | Input/Output | The allocator responsible for allocating and releasing object storage. |
| `pointer` | Input | The storage address previously returned by the same allocator's allocate and not yet released. |
| `count` | Input | The number of elements the storage to be released can hold; must match the element count passed at allocation. |

## Return Value

No return value.

## Constraints

- The storage must come from an allocation that the current allocator can release and must not have been released yet; the quantity must satisfy that allocator's release conventions.
- This function does not destroy objects; the lifetime of any object requiring destruction must be ended before release.
- The wrapper function is `noexcept`; the underlying release must not throw.

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
    using traits = asc::std::allocator_traits<example_allocator<int>>;
    int* pointer = traits::allocate(allocator, 1);
    if (pointer == nullptr) return false;
    traits::construct(allocator, pointer, 7);
    const bool correct = *pointer == 7;
    traits::destroy(allocator, pointer);
    traits::deallocate(allocator, pointer, 1);
    return correct;
}
```

## Related APIs

- [`asc::std::allocator_traits`](allocator_traits.md)
- [API list for this header](asc_std_memory.md)
