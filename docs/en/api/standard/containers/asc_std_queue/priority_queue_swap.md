# asc::std::priority_queue::swap

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

`asc::std::priority_queue::swap` exchanges the state or elements held by two objects.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Function Prototype

Member of: [`priority_queue<T, Container, Compare>`](priority_queue.md). This member has no noexcept specification.

```cpp
constexpr void swap(priority_queue& other);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The other object whose state is exchanged with the current object; after the swap both hold the other's original state. |

## Return Value

No return value.

## Constraints

- Container must support swap; priority_queue additionally move-swaps Compare.
- For device-side use, the Container, element operations, and Compare must be callable at the corresponding execution location and satisfy its non-throwing requirements; the exception behavior on Host follows the objects being called, and freedom from throwing is not promised unless noexcept is additionally declared.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/queue>
#include <functional>
#include <vector>

bool example()
{
    using queue_type = asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>;
    queue_type first;
    queue_type second;
    first.push(3);
    second.push(1);
    static_assert(!noexcept(first.swap(second)));
    first.swap(second);
    return first.top() == 1 && second.top() == 3;
}
```

## Related APIs

- [`asc::std::priority_queue`](priority_queue.md)
- [API list for this header](asc_std_queue.md)
