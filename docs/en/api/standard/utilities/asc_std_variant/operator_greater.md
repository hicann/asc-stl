# `asc::std::operator>` (variant)

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

Header: `<asc/std/variant>`.

Equality comparison requires both sides to have the same active alternative index and equal corresponding values. Order comparison compares the indices first and the values when the indices are equal; the valueless state precedes any state holding a value.

## Function Prototype

The following are function template declarations in the `asc::std` namespace; execution-space macros are omitted.

```cpp
template<class... Types>
constexpr bool operator>(const variant<Types...>& left, const variant<Types...>& right);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left operand of the comparison; the comparison does not modify it. |
| `right` | Input | The right operand of the comparison; the comparison does not modify it. |

`Types...` is the list of alternative types, identical on both sides.

## Return Value

Returns `bool`: `true` when the comparison relation holds, `false` otherwise.

## Constraints

- Each alternative must support the corresponding comparison expression, with a result convertible to `bool`.
- The comparison does not switch the active alternative and does not allocate memory.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> left(3);
    asc::std::variant<int, float> right(2);
    return left > right;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
