# `asc::std::operator>=` (optional)

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

Header: `<asc/std/optional>`.

Compares optionals, plain values, or the empty-state tag. Two empty values are equal; an empty value is less than any object holding a value. The stored values are compared only when both sides hold a value, and a plain value is treated as the engaged side.

## Function Prototype

The following are function template declarations in the `asc::std` namespace; execution-space macros are omitted.

```cpp
template<class T, class U>
constexpr bool operator>=(const optional<T>& left, const optional<U>& right);

template<class T, class U>
constexpr bool operator>=(const optional<T>& left, const U& right);

template<class T, class U>
constexpr bool operator>=(const T& left, const optional<U>& right);

template<class T>
constexpr bool operator>=(const optional<T>& left, nullopt_t right) noexcept;

template<class T>
constexpr bool operator>=(nullopt_t left, const optional<T>& right) noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left operand of the comparison; the comparison does not modify it. |
| `right` | Input | The right operand of the comparison; the comparison does not modify it. |

`T` and `U` are the element types of the optionals or the type of the plain value on the other side; `nullopt_t` denotes the empty state.

## Return Value

Returns `bool`: `true` when the comparison relation holds, `false` otherwise.

## Constraints

- The corresponding comparison expression of the stored values must be valid and its result convertible to `bool`.
- The overloads on this page belong to optional; the variant and string_view overloads are in their respective modules.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> left(2);
    asc::std::optional<int> right(2);
    return (left >= right) && (left >= 2) && (2 >= right);
}
```

## Related Comparison Interfaces

The other type overloads from the original combined page are now collected in: [variant](../asc_std_variant/operator_greater_equal.md), [array](../../containers/asc_std_array/operator_greater_equal.md), [string_view](../../strings/asc_std_string_view/operator_greater_equal.md).
