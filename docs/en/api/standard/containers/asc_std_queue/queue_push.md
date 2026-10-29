# asc::std::queue::push

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

`asc::std::queue::push` inserts one element into the container adaptor.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Function Prototype

Member of: [`asc::std::queue`](queue.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::queue; template parameters and other members are provided by the owning class.
constexpr void push(const value_type& value);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::queue; template parameters and other members are provided by the owning class.
constexpr void push(value_type&& value);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The element value to be enqueued; a new element is constructed at the end of the underlying container by copying. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The element value to be enqueued; a new element is constructed at the end of the underlying container by moving, and after the insertion the source object is in a valid but unspecified moved-from state. |

## Return Value

No return value.

## Constraints

- Container must support the push_back or emplace_back being used; capacity and element construction requirements follow Container.
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
    values.push(3);
    values.push(7);
    const bool first = values.size() == 2 && values.front() == 3;
    values.pop();
    return first && values.size() == 1 && values.front() == 7;
}
```

## Related APIs

- [`asc::std::queue`](queue.md)
- [API list for this header](asc_std_queue.md)
