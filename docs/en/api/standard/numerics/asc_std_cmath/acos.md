# asc::std::acos (function)

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

Headers: `<asc/std/cmath>`, `<asc/std/complex>`.

`asc::std::acos` computes the arc cosine; real results are expressed in radians and lie in the range [0, π]. The float overload can be called on Host and in AI Core SIMT programming, while the double and long double overloads can only be called on Host and keep the corresponding precision; the complex overload supports only `complex<float>`.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float acos(
    float value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp acos(Tp value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time. Extended floating-point templates participate only when the corresponding type is available; numeric calls with half, bfloat16, and the supported FP8 types are for AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double acos(double value) noexcept;
}
```

Available locations: Host.

### Prototype 4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double acos(long double value) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double acos(Tp value) noexcept;
}
```

Available locations: Host.

### Prototype 6

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] complex<T> acos(const complex<T>& value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. This complex overload requires including `<asc/std/complex>`; ASC complex components currently support only float.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |
| `T` | Complex component type; ASC complex currently supports only float. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Real or complex value to compute; the valid real domain is [-1, 1]. |

## Return Value

The return type is determined per prototype (`float`, `Tp`, `double`, `long double`, `complex<T>`). Returns the arc cosine; real results lie in [0, π], in radians.

## Constraints

- Whether an extended type can be instantiated depends on target type support; ordinary transcendental functions are computed in float and converted back to the original format, and the rules for integer rounding and adjacent values are given in the dedicated notes on this page.

- The float and `complex<float>` overloads can be called on Host and in AI Core SIMT programming.
- The double and long double overloads are limited to Host calls.
- For the complex overload, T supports only float.
- The valid real domain is [-1, 1]; handling of out-of-domain inputs and NaN follows the corresponding math backend.
- The actual precision of Host long double is determined by the platform and toolchain and is not guaranteed to be higher than double.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::acos(1.0F);
    return result == 0.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
