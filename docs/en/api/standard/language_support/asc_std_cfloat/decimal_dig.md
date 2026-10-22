# DECIMAL_DIG

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

Header: `<asc/std/cfloat>`.

`DECIMAL_DIG` gives the number of decimal significant digits required for round-trip conversion of floating-point values.

Standard semantics reference: [cppreference `cfloat`](https://en.cppreference.com/w/cpp/header/cfloat).

## Declaration

`DECIMAL_DIG` is an integer constant macro provided by the platform `<float.h>` introduced by `<asc/std/cfloat>`. Its concrete value is determined by the floating-point format of the target platform and must not be written as a fixed replacement identifier.

## Constraints

- Only macros actually supported by the compiler ABI are provided.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/cfloat>

#ifndef DECIMAL_DIG
#error "DECIMAL_DIG must be provided by asc/std/cfloat"
#endif

static_assert(DECIMAL_DIG > 0);
```

## Related APIs

- [API list for this header](asc_std_cfloat.md)
