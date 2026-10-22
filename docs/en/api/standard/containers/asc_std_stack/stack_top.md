# asc::std::stack::top

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

`asc::std::stack::top` returns a reference to the top-of-stack element, that is, the most recently pushed element that has not yet been popped; the stack must be guaranteed non-empty before the call.

Standard semantics reference: [cppreference `stack`](https://en.cppreference.com/w/cpp/header/stack).

## Function Prototype

Member of: [`asc::std::stack`](stack.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::stack; template parameters and other members are provided by the owning class.
constexpr const_reference top() const;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::stack; template parameters and other members are provided by the owning class.
constexpr reference top();
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

No parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const_reference` | Returns a const reference to the top-of-stack element; the stack must be non-empty. |
| Prototype 2 | `reference` | Returns a reference to the top-of-stack element; the stack must be non-empty. |

## Constraints

- The container must be non-empty before the call.
- The returned reference borrows the underlying element; the original container and element must cover the lifetime of the reference, and modification invalidation rules follow Container.
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
    return values.top() == 3;
}
```

## Related APIs

- [`asc::std::stack`](stack.md)
- [API list for this header](asc_std_stack.md)
