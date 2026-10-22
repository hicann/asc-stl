# asc::equal_to_value::`operator()`

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

Header: `<asc/functional>`.

`asc::equal_to_value::operator()` compares the input value with the value stored in the object for equality.

## Function Prototype

Member of: [`asc::equal_to_value`](equal_to_value.md).

```cpp
// Excerpt of the declaration inside asc::equal_to_value; template parameters and other members are provided by the enclosing class.
constexpr bool operator()(const T& value) const noexcept(noexcept(value == value_));
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The operand compared against the value stored in the object; it must support equality comparison. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- The object on this page only performs the described predicate, comparison, or compile-time property query; it does not perform any Runtime submission.
- Comparison operands must support the corresponding operation; transparent min/max may return a reference, and the selected object must remain valid for the duration of use.
- A copyable-arguments declaration only states the caller's copying promise; it does not extend the lifetime of captured references and does not replace callability checks.

## Example

The following Host snippet demonstrates the call with concrete values; inputs must satisfy the constraints on this page.

```cpp
#include <asc/functional>

decltype(auto) example()
{
    asc::equal_to_value<int> equals_seven(7);
    return equals_seven(7);
}
```

## Related APIs

- [`asc::equal_to_value`](equal_to_value.md)
- [API list for this header](asc_functional.md)
