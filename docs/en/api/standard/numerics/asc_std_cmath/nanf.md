# asc::std::nanf

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

Header: `<asc/std/cmath>`.

`asc::std::nanf` constructs a quiet NaN value; the applicable device-side scope is governed by the float and execution-location constraints on this page.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] float nanf(const char* tag) noexcept;
}
```

Available locations: Host, AI Core SIMT programming.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `tag` | Input | Payload tag used to generate the quiet NaN (a null-terminated string); its content is mapped to the mantissa bits of the returned NaN, and an empty string means no specific payload. |

## Return Value

The return type is determined per prototype (`float`). Returns a quiet NaN of type float.

## Constraints

- Provides float function overloads, evaluation type aliases, comparison functions, nanf, and classification macros.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::isnan(asc::std::nanf(""));
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
