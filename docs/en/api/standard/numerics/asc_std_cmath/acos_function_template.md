# asc::std::acos (function template)

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

The Host integer-compatibility overload of `asc::std::acos` promotes the integer to double, computes the arc cosine, and returns double, consistent with the behavior of integer calls to the standard `<cmath>`. Integer arguments on the device side are still computed through the float overload and return float.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double acos(Tp value) noexcept;
}
```

Available locations: Host.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Integer input; the integers within the valid real domain are -1, 0, and 1. |

## Return Value

The return type is determined per prototype (`double`). Returns the arc cosine; real results lie in [0, π], in radians.

## Constraints

- May only be called on Host.
- Integer must be an integer type (including bool).
- Integer arguments are promoted to double, computed, and returned as double, aligning with the standard `<cmath>` behavior.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/cmath>
#include <asc/std/type_traits>
#include <cmath>

bool example()
{
    static_assert(asc::std::is_same_v<decltype(asc::std::acos(0)), double>);
    const double value = asc::std::acos(0);
    return ::std::abs(value - ::std::acos(0.0)) < 1e-14;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
