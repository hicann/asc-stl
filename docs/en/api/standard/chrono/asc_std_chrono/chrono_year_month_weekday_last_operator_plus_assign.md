# asc::std::chrono::year_month_weekday_last::`operator+=`

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

`asc::std::chrono::year_month_weekday_last::operator+=` updates the current value by the given distance or operand.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_weekday_last; template parameters and other members are provided by the owning class.
constexpr year_month_weekday_last& operator+=(const months& offset) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_weekday_last; template parameters and other members are provided by the owning class.
constexpr year_month_weekday_last& operator+=(const years& offset) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `offset` | Input | A signed month offset, in units of months; when crossing a year boundary it carries into the year. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `offset` | Input | The signed number of years to add, in units of years; the month remains unchanged. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `year_month_weekday_last &` | Returns a reference to the current object after the update, which can continue to be used for assignment or compound operations. |
| Prototype 2 | `year_month_weekday_last &` | Returns a reference to the current object after the update, which can continue to be used for assignment or compound operations. |

## Constraints

- The weekday and its index or month-end tag are preserved; the 5th date with the same weekday may not fall within the resulting month and must be checked with ok().
- Operations and intermediate values must be representable.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

void example(asc::std::chrono::year_month_weekday_last& value)
{
    value += asc::std::chrono::months{1};
}
```

## Related APIs

- [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md)
- [API list for this header](asc_std_chrono.md)
