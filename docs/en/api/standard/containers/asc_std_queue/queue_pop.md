# asc::std::queue::pop

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

`asc::std::queue::pop` removes the current first element of the container adaptor.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Function Prototype

Member of: [`asc::std::queue`](queue.md).

```cpp
// Excerpt of the declaration inside class asc::std::queue; template parameters and other members are provided by the owning class.
constexpr void pop();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- The container must be non-empty before the call.
- Erases the element at the front of the queue, the end of the stack, or the top of the heap; the removed element is not returned.
- For device-side use, the Container, element operations, and Compare must be callable at the corresponding execution location and satisfy its non-throwing requirements; the exception behavior on Host follows the objects being called, and freedom from throwing is not promised unless noexcept is additionally declared.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <deque>
#include <asc/std/queue>

bool example()
{
    asc::std::queue<int, ::std::deque<int>> values;
    values.push(1);
    values.push(3);
    values.pop();
    return values.front() == 3;
}
```

## Related APIs

- [`asc::std::queue`](queue.md)
- [API list for this header](asc_std_queue.md)
