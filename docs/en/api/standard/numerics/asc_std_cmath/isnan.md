# asc::std::isnan

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

`asc::std::isnan` determines whether the input is NaN; floating-point inputs are classified by the corresponding type, and integer inputs return false.

For availability of the different types, see the individual prototypes and the constraints.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(float x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(double x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(long double x) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 4

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(__float128 x) noexcept;
}
```

Available locations: Host; this declaration requires Host extended floating-point type support to be enabled.

### Prototype 5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr bool isnan(Tp x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming. Extended floating-point templates participate only when the corresponding type is available; the execution locations of classification and sign queries follow this prototype.

### Prototype 6

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr bool isnan(Tp) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Input value (dimensionless) to be checked for being NaN. |

## Return Value

The return type is determined per prototype (`bool`). Returns true for NaN, and false otherwise.

## Constraints

- Both Host and Device instantiations require the target to support the type used; extended floating-point templates participate only when the corresponding type is enabled.
- The long double and __float128 overloads are provided only when the corresponding Host type support is enabled; see the individual prototypes for the specific gating.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::isnan(1.0F);
    return result == false;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
