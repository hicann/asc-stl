# asc::std::allocator_traits::destroy

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

`asc::std::allocator_traits::destroy` ends the lifetime of a single object at the specified address: the allocator's `destroy` member is called preferentially, and when the allocator does not provide that member, it falls back to calling the destructor of the object pointed to by the pointer (equivalent to `pointer->~T()`).

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

Member of: [`asc::std::allocator_traits`](allocator_traits.md).

```cpp
// Declaration excerpt from inside the asc::std::allocator_traits class; template parameters and other members are provided by the enclosing class.
template<class T> static constexpr void destroy(allocator_type& allocator, T* pointer);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of object being constructed, destroyed, or managed. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `allocator` | Input/Output | The allocator responsible for allocating and releasing object storage. |
| `pointer` | Input/Output | Points to an object whose lifetime has not yet ended; the call ends its lifetime and does not release the underlying storage. |

## Return Value

No return value.

## Constraints

- `pointer` must point to a single `T` object still alive; after destruction the object is no longer accessed, and the storage is not released.
- The allocator's `destroy` member is called preferentially when available; otherwise the object is destroyed directly; the wrapper function has no `noexcept` declaration.
- Device-side use must ensure the actual destruction path does not throw.

## Example

The following Host snippet uses an explicitly provided allocator and fully releases the storage; on the device side, an allocator callable at the target location must be used instead.

```cpp
#include <asc/std/memory>
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

void example(example_allocator<int>& allocator)
{
    int* pointer = asc::std::allocator_traits<example_allocator<int>>::allocate(allocator, 1);
    asc::std::allocator_traits<example_allocator<int>>::construct(allocator, pointer, 7);
    asc::std::allocator_traits<example_allocator<int>>::destroy(allocator, pointer);
    asc::std::allocator_traits<example_allocator<int>>::deallocate(allocator, pointer, 1);
}
```

## Related APIs

- [`asc::std::allocator_traits`](allocator_traits.md)
- [API list for this header](asc_std_memory.md)
