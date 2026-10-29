# asc::narrow

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

`asc::narrow` performs a narrowing conversion and calls `__builtin_trap()` to terminate when the result cannot round-trip losslessly; it returns no status and throws no exception.

## Function Prototype

```cpp
namespace asc {
template <class To, class From>
constexpr To narrow(From value);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `To` | Target integer type of the narrowing conversion. |
| `From` | Source integer type of the narrowing conversion. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Integer value to convert with narrowing; when the result cannot round-trip losslessly, `__builtin_trap()` is called to terminate, with no status returned and no exception thrown. |

## Return Value

| Return type | Description |
| --- | --- |
| `To` | Returns the converted value of the target type; checking and failure behavior follow the constraints of the selected interface. |

## Constraints

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `To` and `From` must be standard non-bool integers of no more than 64 bits; for checking or saturating semantics, see the return value on this page.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::narrow<unsigned char>(3);
}

bool verify_example()
{
    return example() == 3;
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
