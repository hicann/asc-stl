# asc::integer_sqrt

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

`asc::integer_sqrt` returns the largest integer `r` satisfying `r * r <= value`.

## Function Prototype

```cpp
namespace asc {
template <class T>
[[nodiscard]] constexpr auto integer_sqrt(T value) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Integer or enumeration type of the input (excluding bool); an enumeration is operated on as its underlying integer, and that underlying integer type is returned. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Integer value whose integer square root is to be computed; must not be negative for signed types. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns the largest integer `r` satisfying `r * r <= value`. |

## Constraints

- T must be an integer or enumeration type other than bool.
- value of a signed type must not be negative.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/cmath>

decltype(auto) example()
{
    return asc::integer_sqrt(9u);
}
```

## Related APIs

- [API list for this header](asc_cmath.md)
