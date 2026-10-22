# asc::std::stack::size

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

`asc::std::stack::size` returns the number of elements in the current object.

Standard semantics reference: [cppreference `stack`](https://en.cppreference.com/w/cpp/header/stack).

## Function Prototype

Member of: [`asc::std::stack`](stack.md).

```cpp
// Excerpt of the declaration inside class asc::std::stack; template parameters and other members are provided by the owning class.
constexpr size_type size() const;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `size_type` | Returns the number of elements in the current object. |

## Constraints

- Performs the corresponding query on the initialized underlying Container; it does not access or pop elements.
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

- [`asc::std::stack`](stack.md)
- [API list for this header](asc_std_stack.md)
