# asc::std::acosl

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

`asc::std::acosl` computes the arc cosine on Host with long double precision; the result is expressed in radians and lies in the range [0, π]. The actual precision of long double is determined by the Host platform and toolchain and is not guaranteed to be higher than double.

The Host alias family with the `l` suffix in cmath (such as `sinl`, `fabsl`, and `sqrtl`) is now fully delivered: each alias is Host-lane-only like `acosl`, routed through the corresponding `__builtin_*l` entry, and this library does not expose long double on the device lane.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double acosl(long double value) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | long double value to compute; the valid domain is [-1, 1]. |

## Return Value

The return type is determined per prototype (`long double`). Returns the arc cosine; real results lie in [0, π], in radians.

## Constraints

- May only be called on Host.
- Uses the floating-point precision corresponding to the argument.
- The valid real input range is [-1, 1].

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::acosl(1.0L);
    return result == 0.0L;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
