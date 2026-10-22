# `asc::std::operator>` (array)

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

Header: `<asc/std/array>`.

Compares arrays element by element. Equality requires all corresponding elements to be equal; ordering is determined by the first unequal element, and when all elements are equal the arrays are equivalent.

## Function Prototype

The following is the function template declaration in the `asc::std` namespace; execution-space macros are omitted.

```cpp
template<class T, size_t Size>
constexpr bool operator>(const array<T, Size>& left, const array<T, Size>& right);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the comparison; the comparison does not modify it. |
| `right` | Input | Right operand of the comparison; the comparison does not modify it. |

`T` is the element type, and `Size` is the number of elements, identical for both sides.

## Return Value

Returns `bool`, which is `true` when the comparison relation holds and `false` otherwise.

## Constraints

- The elements must support the selected equality or ordering comparison; a zero-length array requires no element access.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/array>

bool example()
{
    asc::std::array<int, 2> left{1, 3};
    asc::std::array<int, 2> right{1, 2};
    return left > right;
}
```

## Related Comparison Interfaces

Other type overloads from the original combined page are now covered separately in: [variant](../../utilities/asc_std_variant/operator_greater.md), [string_view](../../strings/asc_std_string_view/operator_greater.md), [optional](../../utilities/asc_std_optional/operator_greater.md).
