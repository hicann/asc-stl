# asc::mul_hi

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

`asc::mul_hi` returns the high half of the product of two unsigned integers of the same type.

## Function Prototype

```cpp
namespace asc {
template <class T>
[[nodiscard]] constexpr T mul_hi(T left, T right) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Unsigned integer type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Unsigned integer left operand of the multiplication. |
| `right` | Input | Unsigned integer right operand of the multiplication. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the high half of the product of two unsigned integers of the same type. |

## Constraints

- T must be an unsigned integer type other than bool, and the two operands must have the same type.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/cmath>

decltype(auto) example()
{
    return asc::mul_hi(0x10000u, 0x10000u);
}
```

## Related APIs

- [API list for this header](asc_cmath.md)
