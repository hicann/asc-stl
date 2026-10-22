# asc::std::deque::push_back

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

`asc::std::deque::push_back` appends an element to the end of the container.

Standard semantics reference: [cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque).

## Function Prototype

Member of: [`asc::std::deque`](deque.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
void push_back(T&& value);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
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

void example(asc::std::deque<int, example_allocator<int>>& values)
{
    values.push_back(7);
}
```

## Related APIs

- [`asc::std::deque`](deque.md)
- [API list for this header](asc_std_deque.md)
