# asc::std::priority_queue::emplace

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

`asc::std::priority_queue::emplace` constructs an element directly in place at the specified position.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Function Prototype

Member of: [`asc::std::priority_queue`](priority_queue.md).

```cpp
// Excerpt of the declaration inside class asc::std::priority_queue; template parameters and other members are provided by the owning class.
template<class ...Args> constexpr void emplace(Args&&... args);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | The list of argument types passed to the constructor or callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `args` | Input/Output | The list of arguments forwarded to object construction or the function call. |

## Return Value

No return value.

## Constraints

- Container must support the push_back or emplace_back being used; capacity and element construction requirements follow Container.
- Compare must preserve strict weak ordering; the heap order is re-adjusted after insertion.
- For device-side use, the Container, element operations, and Compare must be callable at the corresponding execution location and satisfy its non-throwing requirements; the exception behavior on Host follows the objects being called, and freedom from throwing is not promised unless noexcept is additionally declared.

## Example

The following Host snippet explicitly provides a standard container as the underlying storage; on the device side, a container callable at the target location must be provided.

```cpp
#include <asc/std/queue>
#include <deque>
#include <functional>
#include <vector>

void example(asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>& object)
{
    object.emplace(7);
}
```

## Related APIs

- [`asc::std::priority_queue`](priority_queue.md)
- [API list for this header](asc_std_queue.md)
