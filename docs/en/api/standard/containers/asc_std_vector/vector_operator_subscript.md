# asc::std::vector::`operator[]`

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

`asc::std::vector::operator[]` accesses the specified element when the caller guarantees the index is valid.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
const_reference operator[](size_type index) const noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
reference operator[](size_type index) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | Subscript of the element to access, starting from 0; this interface performs no bounds checking, and the caller must guarantee index < size(). |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | Subscript of the element to access, starting from 0; this interface performs no bounds checking, and the caller must guarantee index < size(). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const_reference` | Returns a reference or proxy value to the element at the specified index; the index must be valid. |
| Prototype 2 | `reference` | Returns a reference or proxy value to the element at the specified index; the index must be valid. |

## Constraints

- The subscript must satisfy `index < size()`; this interface performs no bounds checking, and out-of-range access has undefined behavior.
- The returned reference does not extend the element's lifetime; the original reference is invalidated after the storage is freed or reallocated or the corresponding element is destroyed.

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
    values[0] = 9;
    const sequence& observed = values;
    return observed[0] == 9 && values.front() == 9;
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
