# asc::std::deque::`operator[]`

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

Header: `<asc/std/deque>`.

`asc::std::deque::operator[]` accesses the specified element when the caller guarantees that the index is valid.

Standard semantics reference: [cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque).

## Function Prototype

Member of: [`asc::std::deque`](deque.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
const_reference operator[](size_type index) const noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
reference operator[](size_type index) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The subscript of the element to be accessed, starting from 0; this interface does not check for out-of-range access, and the caller must guarantee index < size(). |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The subscript of the element to be accessed, starting from 0; this interface does not check for out-of-range access, and the caller must guarantee index < size(). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const_reference` | Returns a reference or proxy value for the element at the specified index; the index must be valid. |
| Prototype 2 | `reference` | Returns a reference or proxy value for the element at the specified index; the index must be valid. |

## Constraints

- Precondition: `index < size()`; `operator[]` performs no bounds checking, and out-of-range access has undefined consequences.
- Explicit-allocator construction of deque<T,A>.
- push/emplace/pop_front/back within a bounded block map.
- empty/size/front/back/`operator[]` and the random-access iteration core.
- References to existing elements remain stable when a new end block is allocated.
- clear/destruction.
- Only the domains where capacity is sufficient and exceptions are not thrown.

## Example

The following Host snippet uses an explicitly provided allocator; on the device side, an allocator callable at the target execution location must be used.

```cpp
#include <asc/std/deque>
#include <cstddef>
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

int read_first(const asc::std::deque<int, example_allocator<int>>& values)
{
    // Establish the non-empty precondition first: the empty-container path also returns, ensuring every execution path has a return value
    if (values.empty()) {
        return -1;
    }
    return values[0];  // Read the first element; returns a copy of the element value and does not let the container's internal reference escape the function
}

void write_first(asc::std::deque<int, example_allocator<int>>& values, int new_value)
{
    if (!values.empty()) {
        values[0] = new_value;  // Write through the non-const subscript under the non-empty precondition
    }
}
```

## Related APIs

- [`asc::std::deque`](deque.md)
- [API list for this header](asc_std_deque.md)
