# asc::std::chrono::month::`operator++`

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

`asc::std::chrono::month::operator++` increments the month: the month value advances cyclically between January and December, and incrementing December yields January; the prefix version adds one to the month and returns a reference to itself, and the postfix version likewise adds one to the month but returns a copy of the month value before the modification.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::month`](chrono_month.md).

### Prototype 1

```cpp
// Declaration excerpt from inside the asc::std::chrono::month class; template parameters and other members are provided by the enclosing class.
constexpr month& operator++() noexcept;
```

### Prototype 2

```cpp
// Declaration excerpt from inside the asc::std::chrono::month class; template parameters and other members are provided by the enclosing class.
constexpr month operator++(int unused) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `unused` | Input | Placeholder parameter used to distinguish the postfix increment or postfix decrement form; written as the integer 0 at the call site. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `month &` | Returns a reference to the month object after the increment. |
| Prototype 2 | `month` | Returns a copy of the month value before the modification. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::month value = chrono::month{5};
    ++value;
    return static_cast<unsigned>(value) == 6;
}
```

## Related APIs

- [`asc::std::chrono::month`](chrono_month.md)
- [API list for this header](asc_std_chrono.md)
