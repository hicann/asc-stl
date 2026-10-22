# asc::std::float_t

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

`asc::std::float_t` designates the evaluation type of floating-point expressions and does not extend the precision of device-side math functions in this release.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Declaration

```cpp
namespace asc::std {
using float_t = float;
} // namespace asc::std
```

## Constraints

- Provides the float function overloads, evaluation-type aliases, comparison functions, nanf, and classification macros.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cmath>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_floating_point_v<asc::std::float_t>);
    asc::std::float_t half = 0.5;
    return half + half == 1.0;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
