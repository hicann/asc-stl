# FP_LLOGBNAN

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

`FP_LLOGBNAN` is a compatibility numeric macro; the current header does not provide an llogb function.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Declaration

The concrete integer value of the macro is defined by the math implementation. Use the macro name to identify the corresponding NaN exponent result; do not rely on a fixed numeric value.

```cpp
#include <asc/std/cmath>

constexpr auto nan_exponent = FP_LLOGBNAN;
```

## Constraints

- This macro is provided as a compatibility numeric constant; it must not be taken to imply that the header also declares an llogb function.

- Always defined once `<asc/std/cmath>` is included.
- The macro value is LONG_MIN or LONG_MAX, as determined by the current math implementation.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cmath>
#include <asc/std/climits>

#ifndef FP_LLOGBNAN
#error "FP_LLOGBNAN is required by this public Header"
#endif
static_assert(FP_LLOGBNAN == LONG_MIN || FP_LLOGBNAN == LONG_MAX);
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
