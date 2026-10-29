# asc::std::allocator_traits::construct

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

`asc::std::allocator_traits::construct` constructs an object in allocated storage with the given arguments.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

Member of: [`asc::std::allocator_traits`](allocator_traits.md).

```cpp
// Declaration excerpt from inside the asc::std::allocator_traits class; template parameters and other members are provided by the enclosing class.
template<class T, class ...Args> static constexpr void construct(allocator_type& allocator, T* pointer, Args&&... args);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of object being constructed, destroyed, or managed. |
| `Args` | The list of argument types passed to the constructor or callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `allocator` | Input/Output | The allocator responsible for allocating and releasing object storage. |
| `pointer` | Output | The address of uninitialized storage satisfying the target object's size and alignment; the call starts the object's lifetime there, and the construction arguments determine its initial value. |
| `args` | Input | The list of arguments forwarded to the object construction or function call. |

## Return Value

No return value.

## Constraints

- `pointer` must provide sufficient, correctly aligned uninitialized storage. The arguments are forwarded with their original value categories.
- The allocator's `construct` member is called preferentially when available; otherwise `T` is constructed directly at that address; no uses-allocator argument injection is performed on its own.
- Device-side use must guarantee that the corresponding construction and allocator operations are callable at that location and do not throw.

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
