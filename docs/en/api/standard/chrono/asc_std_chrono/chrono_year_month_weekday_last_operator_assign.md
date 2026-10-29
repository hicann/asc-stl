# asc::std::chrono::year_month_weekday_last::`operator=`

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

`asc::std::chrono::year_month_weekday_last::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_weekday_last; template parameters and other members are provided by the owning class.
constexpr year_month_weekday_last& operator=(const year_month_weekday_last& other);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_weekday_last; template parameters and other members are provided by the owning class.
constexpr year_month_weekday_last& operator=(year_month_weekday_last&& other) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the move operations of the corresponding members. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the move operations of the corresponding members. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `year_month_weekday_last &` | Returns a reference to the current object after the update, which can continue to be used for assignment or compound operations. |
| Prototype 2 | `year_month_weekday_last &` | Returns a reference to the current object after the update, which can continue to be used for assignment or compound operations. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::year_month_weekday_last value =
        chrono::year_month_weekday_last{chrono::year{2023}, chrono::month{4}, chrono::weekday{1}[chrono::last]};
    const auto source =
        chrono::year_month_weekday_last{chrono::year{2024}, chrono::month{5}, chrono::weekday{3}[chrono::last]};
    value = source;
    return static_cast<int>(value.year()) == 2024 && static_cast<unsigned>(value.month()) == 5;
}
```

## Related APIs

- [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md)
- [API list for this header](asc_std_chrono.md)
