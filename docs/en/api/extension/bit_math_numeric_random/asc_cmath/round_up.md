# asc::round_up

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

`asc::round_up` rounds the integer `a` up to the smallest multiple of `b` that is not less than it.

## Function Prototype

```cpp
namespace asc {
template <class T, class U>
[[nodiscard]] constexpr auto round_up(T a, U b) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Integer or enumeration type of the value to round. |
| `U` | Integer or enumeration type of the rounding granularity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Value to round up. |
| `b` | Input | Rounding granularity (alignment step); must not be 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns the numeric result of the operation on the input values as specified by this interface. |

## Constraints

- Signed inputs must satisfy `a >= 0` and `b > 0`; the intermediate multiplication and the result must be representable. This interface does not promise mathematical round-up for a negative dividend.

- T and U must be integer or enumeration types other than bool.
- b must be positive.
- The result must be representable.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/cmath>

decltype(auto) example()
{
    return asc::round_up(5u, 4u);
}
```

## Related APIs

- [API list for this header](asc_cmath.md)
