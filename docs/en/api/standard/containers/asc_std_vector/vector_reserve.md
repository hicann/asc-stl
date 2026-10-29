# asc::std::vector::reserve

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

`asc::std::vector::reserve` requests storage capacity for at least the specified number of elements.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
void reserve(size_type requested);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `requested` | Input | Requested minimum capacity in elements; when greater than the current capacity(), the storage is reallocated so that capacity is not less than this value, otherwise the capacity is unchanged; must not exceed max_size(). |

## Return Value

No return value.

## Constraints

- `T` must be constructible from `T&&` and destructible to satisfy the compilation requirements of the current implementation's element relocation; this type requirement applies even when no growth occurs this time.
- No allocation happens when `requested <= capacity()`; otherwise new storage is allocated and the original elements are relocated element by element.
- A successful growth does not change `size()`, but it invalidates pointers, references, and iterators into the original storage.
- On Host, `std::bad_alloc` is thrown when the allocator returns a null pointer; exceptions thrown by the allocator or by element move construction propagate. On the device side, the related operations must be callable and must not throw, allocation must be guaranteed to succeed, and allocation failure terminates execution.

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
    values.reserve(16);
    return values.capacity() >= 16 && values.size() == 1 && values[0] == 7;
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
