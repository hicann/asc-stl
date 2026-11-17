# asc::std::queue::swap

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

Header: `<asc/std/queue>`.

`asc::std::queue::swap` exchanges the state or elements held by two objects.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Function Prototype

Member of: [`asc::std::queue`](queue.md).

```cpp
// Excerpt of the declaration inside class asc::std::queue; template parameters and other members are provided by the owning class.
constexpr void swap(queue<T, Container>& other) noexcept(noexcept(this->c.swap(other.c)));
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The other object whose state is exchanged with the current object; after the swap both hold the other's original state. |

## Return Value

No return value.

## Constraints

- Container must support swap; the exception specification matches the swap of the selected Container.
- Generic code may inspect `noexcept(a.swap(b))` without executing a swap. The result follows the underlying container even in C++17 on GCC 9; it must not always be assumed true. For a breadth-first graph traversal, swapping an emptied current frontier with the next frontier avoids copying the queued vertices.
- For device-side use, the Container, element operations, and Compare must be callable at the corresponding execution location and satisfy its non-throwing requirements; the exception behavior on Host follows the objects being called, and freedom from throwing is not promised unless noexcept is additionally declared.

## Example

The following Host snippet explicitly provides a standard container as the underlying storage; on the device side, a container callable at the target location must be provided.

```cpp
#include <asc/std/queue>
#include <memory>
#include <deque>

bool example()
{
    using sequence = asc::std::queue<int, ::std::deque<int>>;
    sequence values;
    values.push(7);
    sequence other;
    other.push(9);
    values.swap(other);
    return values.front() == 9 && other.front() == 7;
}
```

## Related APIs

- [`asc::std::queue`](queue.md)
- [API list for this header](asc_std_queue.md)
