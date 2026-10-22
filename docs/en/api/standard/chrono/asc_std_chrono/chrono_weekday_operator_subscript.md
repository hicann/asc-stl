# asc::std::chrono::weekday::`operator[]`

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

`asc::std::chrono::weekday::operator[]` constructs calendar helper types with subscript syntax: the indexed form constructs `weekday_indexed` from this weekday and an index (denoting which occurrence of this weekday in the month), and the `last_spec` form constructs `weekday_last` (denoting the last occurrence of this weekday in the month).

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::weekday`](chrono_weekday.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::chrono::weekday; template parameters and other members are provided by the owning class.
[[nodiscard]] constexpr weekday_indexed operator[](unsigned int index) const noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::chrono::weekday; template parameters and other members are provided by the owning class.
[[nodiscard]] constexpr weekday_last operator[](last_spec index) const noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | Which occurrence of the weekday in the month, ranging from 1 to 5; combined with the current weekday to form weekday_indexed. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The last tag (asc::std::chrono::last); denotes taking the last occurrence of the current weekday in the month. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `weekday_indexed` | Returns the `weekday_indexed` constructed from this weekday and the given index, denoting which occurrence of this weekday in the month. |
| Prototype 2 | `weekday_last` | Returns the `weekday_last` constructed from this weekday, denoting the last occurrence of this weekday in the month. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

decltype(auto) example(const asc::std::chrono::weekday& value)
{
    return value[1];
}
```

## Related APIs

- [`asc::std::chrono::weekday`](chrono_weekday.md)
- [API list for this header](asc_std_chrono.md)
