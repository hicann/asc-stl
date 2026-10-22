# asc::floor_div

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

Header: `<asc/cmath>`.

`asc::floor_div` computes the integer quotient rounded toward negative infinity.

## Function Prototype

```cpp
namespace asc {
template <class T, class U>
[[nodiscard]] constexpr auto floor_div(T a, U b) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Integer or enumeration type of the dividend. |
| `U` | Integer or enumeration type of the divisor. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Dividend of the integer quotient. |
| `b` | Input | Divisor of the integer quotient; must not be 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns the computed integer quotient rounded toward negative infinity. |

## Constraints

- T and U must be integer or enumeration types other than bool.
- b must not be zero.
- The division result must be representable.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/cmath>

decltype(auto) example()
{
    return asc::floor_div(-5, 2);
}
```

## Related APIs

- [API list for this header](asc_cmath.md)
