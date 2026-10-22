# asc::std::abs

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

Headers: `<asc/std/cmath>`, `<asc/std/complex>`, `<asc/std/cstdlib>`.

`asc::std::abs` returns the absolute value of the argument; the applicable device-side scope is governed by the float and execution-location constraints on this page.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float abs(float x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
[[nodiscard]] constexpr double abs(double x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double abs(long double x) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 4

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] T abs(const complex<T>& value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. This complex overload requires including `<asc/std/complex>`; ASC complex components currently support only float.

### Standard Integer Overloads

The following forms require including `<asc/std/cstdlib>` and can be used on Host and in applicable Device modes.

```cpp
namespace asc::std {
constexpr int abs(int value) noexcept;
}
```

```cpp
namespace asc::std {
constexpr long abs(long value) noexcept;
}
```

```cpp
namespace asc::std {
constexpr long long abs(long long value) noexcept;
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Complex component type; ASC complex currently supports only float. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Input value whose floating-point absolute value is to be computed (dimensionless). |
| `value` | Input | Complex operand whose magnitude (absolute value) is to be computed; the magnitude is the length of the vector formed by the real and imaginary parts. |

## Return Value

The return type is determined per prototype (`float`, `double`, `long double`, `T`). Returns the absolute value of a real number or the magnitude of a complex number.

## Constraints

- Integer overloads and the corresponding result types are provided.
- The standard integer overloads require the absolute value of the argument to be representable by the return type; for example, `abs(INT_MIN)` does not satisfy this requirement and the behavior is undefined.
- Scalar precision and execution location are determined per prototype; complex input supports only complex<float>.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::abs(-2.0F) == 2.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
