# asc::std::scoped_allocator_adaptor::`operator=`

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

`asc::std::scoped_allocator_adaptor::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator).

## Function Prototype

Member of: [`scoped_allocator_adaptor`](scoped_allocator_adaptor.md). The following describes only the implicitly declared assignment forms; whether they are defined as deleted, whether they are constexpr, and their exception specifications are all determined by the C++ special-member rules of the outer and inner allocators.

```cpp
scoped_allocator_adaptor& operator=(const scoped_allocator_adaptor& other);
scoped_allocator_adaptor& operator=(scoped_allocator_adaptor&& other);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source adaptor; its outer and inner allocator states are copied or moved, while the element storage itself is not relocated in this operation. |

## Return Value

| Return type | Description |
| --- | --- |
| `scoped_allocator_adaptor&` | Returns `*this`. |

## Constraints

- The assignment special members assign item by item from the outer base class and the inner allocators according to the C++ implicit declaration rules; availability, constant evaluation, and exception specifications depend on these members.
- This operation does not read propagation traits to select the container element allocator, and does not move or copy any allocated elements.

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

void example(asc::std::scoped_allocator_adaptor<example_allocator<int>>& target, const asc::std::scoped_allocator_adaptor<example_allocator<int>>& source)
{
    target = source;
}
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
