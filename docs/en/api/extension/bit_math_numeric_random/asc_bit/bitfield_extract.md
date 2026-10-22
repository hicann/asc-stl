# asc::bitfield_extract

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

Header: `<asc/bit>`.

`asc::bitfield_extract` extracts `width` consecutive bits starting from bit `start` of an unsigned integer and returns the result right-aligned.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr T bitfield_extract(T value, int start, int width) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Unsigned integer type; must be uint32_t or uint64_t. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Unsigned integer value whose bit field is to be extracted. |
| `start` | Input | Bit index of the start of the bit field within `value` (the lowest bit is bit 0); must not be negative. |
| `width` | Input | Number of consecutive bits to extract; must not be negative. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the bit field value extracted from the specified start bit and right-aligned. |

## Constraints

- T must be uint32_t or uint64_t.
- `start` and `width` must be non-negative, with `start <= bit width` and `width <= bit width - start`; zero width and full width are handled under this window constraint.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bitfield_extract(0x3fu, 1, 3);
}
```

## Related APIs

- [API list for this header](asc_bit.md)
