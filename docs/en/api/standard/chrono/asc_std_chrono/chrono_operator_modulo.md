# asc::std::chrono::`operator%`

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

Header: `<asc/std/chrono>`.

`asc::std::chrono::operator%` takes the remainder of duration counts, returning the remainder duration at the common timekeeping precision.

Duration semantics are described in [`duration`](chrono_duration.md).

## Function Prototype

Called as `left % right`; hidden friends participate through argument-dependent lookup and must not be relied on via qualified namespace lookup.

### Prototype 1

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type. The declaration summary omits implementation parameters used only for overload selection: `Rep2` must not be a `duration`, and `const Rep2&` must be convertible to `common_type_t<Rep, Rep2>`.

```cpp
template <class Rep2>
[[nodiscard]] friend constexpr duration<common_type_t<Rep, Rep2>, Period> operator%(const duration& left, const Rep2& right);
```

### Prototype 2

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<duration, duration<Rep2, Period2>> operator%(const duration& left, const duration<Rep2, Period2>& right);
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |
| `right` | Input | The divisor; it must be convertible to the common count type, and modulo additionally requires support for the remainder operation. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |
| `Period2` | The tick period of the other duration, a ratio type based on seconds. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |
| `right` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `duration<common_type_t<Rep, Rep2>, Period>` | Takes the remainder of the common count and returns a duration; the two-duration form first converts to the common period. |
| Prototype 2 | `common_type_t<duration, duration<Rep2, Period2>>` | Takes the remainder of the common count and returns a duration; the two-duration form first converts to the common period. |

## Constraints

- The count and intermediate operations must be representable.
- For integer counts, the current implementation treats a divisor that converts to 0 as 1; this is not the standard chrono guarantee for zero divisors. Use a non-zero divisor when standard portable semantics are required; must not be called when the signed minimum value divided by -1 is not representable.
- The count or common count type must support `%`; built-in floating-point counts do not support modulo.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

bool example()
{
    const asc::std::chrono::seconds value{7};
    return (value % 3).count() == 1 && (value % asc::std::chrono::seconds{3}).count() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
