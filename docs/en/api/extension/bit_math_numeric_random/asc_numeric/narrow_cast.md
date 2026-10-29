# asc::narrow_cast

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

`asc::narrow_cast` explicitly performs a narrowing type conversion without any runtime check.

## Function Prototype

```cpp
namespace asc {
template <class To, class From>
constexpr To narrow_cast(From value);
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
| `value` | Input | Integer value to convert; this interface performs no runtime range check. |

## Return Value

| Return type | Description |
| --- | --- |
| `To` | Returns the converted value of the target type; checking and failure behavior follow the constraints of the selected interface. |

## Constraints

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `To` and `From` must be standard non-bool integers of no more than 64 bits; this is a direct static_cast that does not check for information loss and does not report failure.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::narrow_cast<unsigned char>(3);
}

bool verify_example()
{
    return example() == 3;
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
