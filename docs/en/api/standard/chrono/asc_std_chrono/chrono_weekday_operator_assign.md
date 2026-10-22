# asc::std::chrono::weekday::`operator=`

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

`asc::std::chrono::weekday::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::weekday`](chrono_weekday.md).

### Prototype 1

```cpp
// Declaration excerpt from inside the asc::std::chrono::weekday class; template parameters and other members are provided by the enclosing class.
constexpr weekday& operator=(const weekday& other);
```

### Prototype 2

```cpp
// Declaration excerpt from inside the asc::std::chrono::weekday class; template parameters and other members are provided by the enclosing class.
constexpr weekday& operator=(weekday&& other) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The object assigned from; the lvalue form copies its state, and the rvalue form transfers the state through the move operations of the corresponding members. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The object assigned from; the lvalue form copies its state, and the rvalue form transfers the state through the move operations of the corresponding members. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `weekday &` | Returns a reference to the updated current object, which can continue to be used for assignment or compound operations. |
| Prototype 2 | `weekday &` | Returns a reference to the updated current object, which can continue to be used for assignment or compound operations. |

## Constraints

- Arithmetic on calendar fields and timekeeping values can be used on the Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

void example(asc::std::chrono::weekday& value, const asc::std::chrono::weekday& other)
{
    value = other;
}
```

## Related APIs

- [`asc::std::chrono::weekday`](chrono_weekday.md)
- [API list for this header](asc_std_chrono.md)
