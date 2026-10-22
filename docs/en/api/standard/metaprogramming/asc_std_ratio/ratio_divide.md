# asc::std::ratio_divide

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

Header: `<asc/std/ratio>`.

`asc::std::ratio_divide` combines two compile-time rational numbers according to the arithmetic or comparison relation indicated by the name.

Standard semantics reference: [cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio).

## Declaration

`asc::std::ratio_divide<R1, R2>` is the normalized ratio type obtained by applying the `/` operation to two compile-time rational numbers. Public usage does not depend on internal operation helper templates.

```cpp
using Result = asc::std::ratio_divide<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>;
```

## Constraints

- The denominator must not be zero; the normalized numerator and denominator must be representable by `intmax_t`.
- The numerator and denominator of the original template arguments must not be `INTMAX_MIN`; the denominator must be nonzero, and the intermediate and final results of the reduction and sign normalization must be representable by `intmax_t`.
- The numerator of the second ratio must be nonzero: dividing by a zero ratio is invalid. A nonzero denominator of the ratio does not substitute for this condition.

## Example

The following snippet selects concrete template arguments to demonstrate the alias type.

```cpp
#include <asc/std/ratio>

void use_type()
{
    using selected = asc::std::ratio_divide<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>;
    static_assert(selected::num == 3 && selected::den == 2);
}
```

## Related APIs

- [API list for this header](asc_std_ratio.md)
