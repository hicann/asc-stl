# asc::std::isunordered

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

`asc::std::isunordered` compares the input values by the floating-point comparison relation designated by the name, and follows the unordered rules for NaN.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] bool isunordered(float x, float y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Left operand of the x-versus-y unordered comparison (dimensionless); the result is true and no floating-point exception is raised when either operand is NaN. |
| `y` | Input | Right operand of the x-versus-y unordered comparison (dimensionless). |

## Return Value

The return type is determined per prototype (`bool`). Returns true when at least one input is NaN.

## Constraints

- Provides float function overloads, evaluation type aliases, comparison functions, nanf, and classification macros.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::isunordered(1.0F, 2.0F);
    return result == false;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
