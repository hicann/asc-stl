# asc::std::vector::push_back

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

Header: `<asc/std/vector>`.

`asc::std::vector::push_back` appends an element to the end of the container.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
void push_back(T&& value);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
void push_back(const T& value);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input (may be moved) | Provides the element to be appended to the end of the container; the function may move this argument, leaving it in a valid but unspecified state after the move. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Element value to be appended to the end of the container; the new element is constructed by copying, and the source object remains unchanged. |

## Return Value

No return value.

## Constraints

- The lvalue overload requires `T` to be constructible from `const T&`, and the rvalue overload requires `T` to be constructible from `T&&`; both overloads currently also require `T` to be constructible from `T&&` to satisfy the compilation requirements of the capacity-growth path, and reserving capacity in advance does not waive this requirement.
- When capacity is insufficient, the container grows and moves the original elements; after growth, the original pointers, references, and iterators are invalidated. After a successful insertion, `size()` increases by `1`.
- Arguments may refer to elements or subobjects in this container; on growth, the new element is constructed before existing elements are moved. Pointers and references to the old storage are still invalidated, including any such pointers or references retained by the new element.
- When called on the device side, the allocator and the related element operations must be available in the corresponding programming mode and must not throw, and allocation must be guaranteed to succeed or sufficient capacity must be reserved beforehand.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/vector>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};

bool example()
{
    using sequence = asc::std::vector<int, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.push_back(7);
    values.push_back(9);
    return values.size() == 2 && values.front() == 7 && values.back() == 9;
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../../examples/standard/explicit_allocator_vector/main.cpp).

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
