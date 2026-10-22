# asc::std::chrono::time_point::time_point

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

`asc::std::chrono::time_point::time_point` initializes a `time_point` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr time_point();
```

### Prototype 2

```cpp
explicit constexpr time_point(const duration& duration);
```

### Prototype 3

```cpp
template<class Duration2> constexpr time_point(const time_point<clock, Duration2>& duration);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `duration` | Input | Provides the object reference used to "initialize a `time_point` object according to the construction forms listed on this page"; the referenced object must be valid for the duration of the call. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Duration2` | The duration type of the source time_point; it must be convertible to the target duration type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `duration` | Input | Provides the object reference used to "initialize a `time_point` object according to the construction forms listed on this page"; the referenced object must be valid for the duration of the call. |

## Return Value

No return value.

## Constraints

- Supports user-defined clocks, value arithmetic, and the six explicit relational operators.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds> value{asc::std::chrono::seconds{7}};
    return value.time_since_epoch().count() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
