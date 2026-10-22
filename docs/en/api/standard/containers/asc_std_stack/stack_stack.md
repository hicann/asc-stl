# asc::std::stack::stack

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

Header: `<asc/std/stack>`.

`asc::std::stack::stack` initializes a `stack` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `stack`](https://en.cppreference.com/w/cpp/header/stack).

## Function Prototype

Member of: [`stack`](stack.md). Whether the compiler-generated copy/move special members are available depends on Container and the comparator; there is no allocator or iterator-range construction entry.

### Prototype 1

```cpp
constexpr stack() = default;
```

### Prototype 2

```cpp
constexpr explicit stack(const Container& container);
```

### Prototype 3

```cpp
constexpr explicit stack(Container&& container);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `container` | Input | The Container object copied as the underlying storage. |

### Parameters of Prototype 3

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `container` | Input | The Container object moved as the underlying storage; the source state is determined by its move construction rules. |

## Return Value

No return value.

## Constraints

- The default form requires Container to be default-constructible; the Container-source forms require the corresponding copy or move construction to be valid.
- On the device side, the Container, element operations, and Compare used must be callable at the corresponding execution location and satisfy its non-throwing requirements; on Host, exception behavior follows the invoked object, and non-throwing is not promised unless noexcept is explicitly declared.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <deque>
#include <asc/std/stack>

bool example()
{
    asc::std::stack<int, ::std::deque<int>> values;
    values.push(1);
    values.push(3);
    return values.size() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_stack.md)
