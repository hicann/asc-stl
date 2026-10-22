# asc::overflow_cast

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

`asc::overflow_cast` converts between integer types and returns both the result and the out-of-range flag.

## Function Prototype

```cpp
namespace asc {
template <class To, class From>
constexpr asc::overflow_result<To> overflow_cast(From value) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `To` | Target integer type of the conversion. |
| `From` | Source integer type of the conversion. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Integer value to convert; the result is returned together with whether it is out of range (including a sign change or an inconsistent round trip). |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::overflow_result<To>` | Returns the result and the out-of-range flag. |

## Constraints

- When `overflow == true`, the value of integer addition, subtraction, and multiplication stores the result converted to the target bit width; division by zero stores 0, and a signed minimum value divided by -1 stores that minimum value. `overflow_cast` stores the converted value; it must not be treated as an exact mathematical result while ignoring the flag.

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `To` and `From` must be standard non-bool integers of no more than 64 bits; for checking or saturating semantics, see the return value on this page.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::overflow_cast<unsigned char>(300);
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
