# asc::std::priority_queue::priority_queue

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

`asc::std::priority_queue::priority_queue` initializes a `priority_queue` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Function Prototype

Member of: [`priority_queue`](priority_queue.md). Availability of the compiler-generated copy/move special members depends on Container and the comparator; there is no allocator or iterator-range construction entry.

### Prototype 1

```cpp
constexpr priority_queue() = default;
```

### Prototype 2

```cpp
constexpr explicit priority_queue(const Compare& compare);
```

### Prototype 3

```cpp
constexpr priority_queue(const Compare& compare, const Container& container);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `compare` | Input | The strict-weak-order comparator to be stored; this form default-constructs the underlying Container. |

### Parameters of Prototype 3

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `compare` | Input | The strict-weak-order comparator to be stored. |
| `container` | Input | The container copied as the underlying storage; the heap order is re-established with compare during construction. |

## Return Value

No return value.

## Constraints

- The default form requires Container and Compare to be default-constructible; the Compare form requires Container to be default-constructible.
- The Compare-and-Container form copies both and rebuilds the heap; the comparator must satisfy strict weak ordering.
- For device-side use, the Container, element operations, and Compare must be callable at the corresponding execution location and satisfy its non-throwing requirements; the exception behavior on Host follows the objects being called, and freedom from throwing is not promised unless noexcept is additionally declared.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <vector>
#include <functional>
#include <asc/std/queue>

bool example()
{
    asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>> values;
    values.push(1);
    values.push(3);
    values.push(2);
    return values.size() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_queue.md)
