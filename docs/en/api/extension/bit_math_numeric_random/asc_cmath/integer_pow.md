# asc::integer_pow

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

`asc::integer_pow` computes `base` raised to the power of `exponent` using integer arithmetic.

## Function Prototype

```cpp
namespace asc {
template <class T, class E>
[[nodiscard]] constexpr T integer_pow(T base, E exponent) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Integer or enumeration type of the base and the power result. |
| `E` | Integer or enumeration type of the exponent. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input | Base of the integer power operation. |
| `exponent` | Input | Exponent of the integer power operation; takes a non-negative integer. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the numeric result of the operation on the input values as specified by this interface. |

## Constraints

- T and E must be integer or enumeration types other than bool.
- A signed exponent must not be negative.
- The result must be representable.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/cmath>

bool example()
{
    const auto result = asc::integer_pow(2, 3);
    return result == 8;
}
```

## Related APIs

- [API list for this header](asc_cmath.md)
