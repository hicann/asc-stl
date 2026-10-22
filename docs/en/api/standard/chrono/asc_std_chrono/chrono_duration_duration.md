# asc::std::chrono::duration::duration

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

`asc::std::chrono::duration::duration` initializes a `duration` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr duration();
```

### Prototype 2

```cpp
template<class Rep2, class Period2> constexpr duration(const duration<Rep2, Period2>& count);
```

### Prototype 3

```cpp
template<class Rep2> explicit constexpr duration(const Rep2& count);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The representation type of the source count; it must satisfy the conversion conditions of the target duration. |
| `Period2` | The timekeeping unit of the source duration, expressed as a ratio. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `count` | Input | The source duration; the unit of its count is determined by its Period2, and it is converted to the target Period for initialization. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The representation type of the source count; it must satisfy the conversion conditions of the target duration. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `count` | Input | The initial count value; one tick represents Period::num / Period::den seconds. |

## Return Value

No return value.

## Constraints

- Provides value operations and the six explicit relational operators.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::duration<int> value{7};
    return value.count() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
