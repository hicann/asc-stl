# asc::std::vector::vector

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

`asc::std::vector::vector` initializes a `vector` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

### Prototype 1

```cpp
explicit vector(const Allocator& allocator) noexcept;
```

### Prototype 2

```cpp
vector(vector<T, Allocator>&& other) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `allocator` | Input | Allocator responsible for allocating and freeing the object storage. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | Source object for construction; this object is initialized from its corresponding members or underlying state, and the rvalue form may move that state. |

## Return Value

No return value.

## Constraints

- Plain construction requires an explicit `Allocator` object, and the allocator must be able to provide and free contiguous storage for `T`; the initial container is empty.
- Move construction copies the source allocator and takes over the source storage, leaving the source container empty; copy construction is deleted. Allocator copy operations must not throw.
- When constructing on the device side, the allocator operations being called must be available in the corresponding programming mode.

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
    return values.size() == 1 && values[0] == 7;
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [API list for this header](asc_std_vector.md)
