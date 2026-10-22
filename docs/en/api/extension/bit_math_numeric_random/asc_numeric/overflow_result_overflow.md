# asc::overflow_result::overflow

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

Header: `<asc/numeric>`.

`asc::overflow_result::overflow` flags whether an overflow occurred in the corresponding arithmetic result.

## Declaration

Member of: [`asc::overflow_result`](overflow_result.md).

```cpp
// Excerpt of the declaration inside the asc::overflow_result class; template parameters and other members are provided by the enclosing class.
bool overflow;
```

## Constraints

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `T` must be a standard non-bool integer of no more than 64 bits; querying the result members performs no additional computation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/numeric>

bool example()
{
    auto result = asc::add_overflow(2, 3);
    return !result.overflow && result.value == 5;
}
```

## Related APIs

- [`asc::overflow_result`](overflow_result.md)
- [API list for this header](asc_numeric.md)
