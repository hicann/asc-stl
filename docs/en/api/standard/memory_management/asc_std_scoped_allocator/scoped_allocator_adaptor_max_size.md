# asc::std::scoped_allocator_adaptor::max_size

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

`asc::std::scoped_allocator_adaptor::max_size` returns the theoretical maximum number of elements allowed by the container or allocator.

Standard semantics reference: [cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator).

## Function Prototype

Member of: [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md).

```cpp
// Declaration excerpt from inside the asc::std::scoped_allocator_adaptor class; template parameters and other members are provided by the enclosing class.
size_type max_size() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `size_type` | Returns the theoretical maximum number of elements allowed by the container or allocator. |

## Constraints

- Directly calls the outer allocator's `max_size()`; that member must exist and the call must not throw.
- Returns the theoretically allocatable number of elements and requests no storage.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <memory>
#include <limits>

template<class T>
struct example_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<class U> struct rebind { using other = example_allocator<U>; };
    int identity = 0;
    T* allocate(size_type count) { return std::allocator<T>{}.allocate(count); }
    void deallocate(T* address, size_type count) { std::allocator<T>{}.deallocate(address, count); }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

bool example()
{
    using adaptor = asc::std::scoped_allocator_adaptor<example_allocator<int>>;
    adaptor allocator(example_allocator<int>{7});
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 9);
    const bool valid = allocator.max_size() == std::numeric_limits<std::size_t>::max() / sizeof(int) && *pointer == 9;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return valid;
}
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
