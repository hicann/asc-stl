# asc::std::float_round_style

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

Header: `<asc/std/limits>`.

`asc::std::float_round_style` lists the rounding categories used by floating-point operations.

Standard semantics reference: [cppreference `limits`](https://en.cppreference.com/w/cpp/header/limits).

## Declaration

```cpp
namespace asc::std {
enum float_round_style {
    round_indeterminate = -1, round_toward_zero = 0, round_to_nearest = 1,
    round_toward_infinity = 2, round_toward_neg_infinity = 3
};
}
```

## Constraints

- This is an unscoped enum with the complete set of enumerator definitions; the enumeration constants are in the asc::std namespace.
- numeric_limits reports the representation or rounding characteristics of the queried type; the enumeration values themselves do not change the hardware floating-point state.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/limits>

bool example()
{
    // Query the representation and rounding characteristics of the float type for the current target.
    const auto style = asc::std::numeric_limits<float>::round_style;
    return style == asc::std::round_to_nearest || style == asc::std::round_toward_zero || style == asc::std::round_toward_infinity || style == asc::std::round_toward_neg_infinity || style == asc::std::round_indeterminate;
}
```

## Related APIs

- [API list for this header](asc_std_limits.md)
