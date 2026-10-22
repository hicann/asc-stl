# asc::overflow_result

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

`asc::overflow_result` returns both the arithmetic result and the flag indicating whether an overflow occurred.

## Declaration

```cpp
namespace asc {
template <class T>
struct overflow_result;
}  // namespace asc
```

## Constraints

- When `overflow == true`, the value of integer addition, subtraction, and multiplication stores the result converted to the target bit width; division by zero stores 0, and a signed minimum value divided by -1 stores that minimum value. `overflow_cast` stores the converted value; it must not be treated as an exact mathematical result while ignoring the flag.

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `T` must be a standard non-bool integer of no more than 64 bits; querying the result members performs no additional computation.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/numeric>

bool example()
{
    const asc::overflow_result<int> result = asc::add_overflow(4, 5);
    return !result.overflow && result.value == 9;
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
