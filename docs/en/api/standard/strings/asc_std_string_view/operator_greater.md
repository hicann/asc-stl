# `asc::std::operator>` (string_view)

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

Header: `<asc/std/string_view>`.

Compares character sequence contents and lengths according to the character traits `T`. Ordered comparison uses lexicographic order. The three forms accept two views, and values implicitly convertible to a view on either side; pointer addresses are not compared.

## Function Prototype

The following are function template declarations in the `asc::std` namespace; execution-space macros are omitted.

```cpp
template<class C, class T>
constexpr bool operator>(basic_string_view<C, T> left, basic_string_view<C, T> right) noexcept;

template<class C, class T, int = 1>
constexpr bool operator>(basic_string_view<C, T> left, type_identity_t<basic_string_view<C, T>> right) noexcept;

template<class C, class T, unsigned int = 2>
constexpr bool operator>(type_identity_t<basic_string_view<C, T>> left, basic_string_view<C, T> right) noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the comparison; the comparison does not modify it. |
| `right` | Input | Right operand of the comparison; the comparison does not modify it. |

`C` is the character type and `T` is the character traits type. The unnamed integer template parameter only distinguishes overloads and does not need to be passed explicitly.

## Return Value

Returns `bool`, which is `true` when the comparison relation holds and `false` otherwise.

## Constraints

- The character range referenced by the view must be readable and remain alive for the duration of the call; a string literal conversion determines the length by its terminator.
- In AI Core SIMD programming, plain character pointers apply to the local or generic address space.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/string_view>

bool example()
{
    asc::std::string_view left("3");
    asc::std::string_view right("2");
    return (left > right) && (left > "2") && ("3" > right);
}
```

## Related Comparison Interfaces

Other type overloads from the original combined page are now covered separately in: [variant](../../utilities/asc_std_variant/operator_greater.md), [array](../../containers/asc_std_array/operator_greater.md), [optional](../../utilities/asc_std_optional/operator_greater.md).
