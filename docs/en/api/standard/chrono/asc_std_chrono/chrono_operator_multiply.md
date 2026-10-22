# asc::std::chrono::`operator*`

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

`asc::std::chrono::operator*` scales the count of a duration by a scalar, keeping the timekeeping period. Both commuted forms of the two operands are provided.

Duration semantics are described in [`duration`](chrono_duration.md).

## Function Prototype

Called as `left * right`; hidden friends participate through argument-dependent lookup and must not be relied on via qualified namespace lookup.

### Prototype 1

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type. The declaration summary omits the default overload-selection parameter; it participates only when `const Rep2` is convertible to `common_type_t<Rep, Rep2>`.

```cpp
template <class Rep2>
[[nodiscard]] friend constexpr duration<common_type_t<Rep, Rep2>, Period> operator*(const duration& left, const Rep2& right);
```

### Prototype 2

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type. The declaration summary omits the default overload-selection parameter; it participates only when `const Rep2&` is convertible to `common_type_t<Rep, Rep2>`.

```cpp
template <class Rep2>
[[nodiscard]] friend constexpr duration<common_type_t<Rep, Rep2>, Period> operator*(const Rep2& left, const duration& right);
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
| `right` | Input | The scaling factor; it must satisfy the listed convertibility conditions. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The scaling factor; it must satisfy the listed convertibility conditions. |
| `right` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `duration<common_type_t<Rep, Rep2>, Period>` | Multiplies the count by the scalar; period is unchanged and rep uses the common count type. |
| Prototype 2 | `duration<common_type_t<Rep, Rep2>, Period>` | Multiplies the count by the scalar; period is unchanged and rep uses the common count type. |

## Constraints

- The count and intermediate operations must be representable.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

bool example()
{
    const asc::std::chrono::seconds value{3};
    return (value * 2).count() == 6 && (2 * value).count() == 6;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
