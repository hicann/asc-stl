# asc::std::copysignl

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

`asc::std::copysignl` is provided by `<asc/std/cmath>`; it combines a magnitude with a sign bit to produce a signed long double floating-point value. The interface follows the semantics of the corresponding C++ standard facility; the language modes and call locations of ASC-STL are subject to the declarations on this page.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double copysignl(long double x, long double y) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Scalar value controlling this operation; valid values are determined jointly by the declaration and the constraints. |
| `y` | Input | Scalar value controlling this operation; valid values are determined jointly by the declaration and the constraints. |

## Return Value

The return type is determined per prototype (`long double`). Returns the value combining the absolute value of x with the sign of y; standard floating-point types keep their original type, and Host integer inputs return double.

## Constraints

- Standard integer inputs on Host are promoted to double; the device-side integer promotion branch is rejected by a static assertion. Instantiations of float, double, long double, and extended types must also be supported by the target compilation mode.

- Copies the sign bit of the second argument onto the magnitude of the first argument and returns a long double result.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::copysignl(2.0L, -1.0L);
    return result == -2.0L;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
