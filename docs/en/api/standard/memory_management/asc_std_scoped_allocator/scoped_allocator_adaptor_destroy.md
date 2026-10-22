# asc::std::scoped_allocator_adaptor::destroy

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

`asc::std::scoped_allocator_adaptor::destroy` ends the lifetime of a constructed object.

Standard semantics reference: [cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator).

## Function Prototype

Member of: [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md).

```cpp
// Declaration excerpt from inside the asc::std::scoped_allocator_adaptor class; template parameters and other members are provided by the enclosing class.
template<class Type> void destroy(Type* pointer);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Type` | The type of object constructed or destroyed by the allocator. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input/Output | Points to an object whose lifetime has not yet ended; the call ends its lifetime and does not release the underlying storage. |

## Return Value

No return value.

## Constraints

- Directly ends the lifetime of the single live object at `pointer`; it does not release storage and does not call the outer allocator's destruction hook.
- The pointer must point to an object still alive; destruction on the device side must be callable and must not throw.

## Example

The following Host snippet uses an explicitly provided allocator and fully releases the storage; on the device side, an allocator callable at the target location must be used instead.

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

void example(asc::std::scoped_allocator_adaptor<example_allocator<int>>& allocator)
{
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 7);
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
}
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
