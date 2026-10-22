# asc::aligned_size

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

Header: `<asc/memory>`.

`asc::aligned_size` rounds `size` up to a multiple of `alignment`; when `alignment == 0`, `size` is returned unchanged.

## Function Prototype

```cpp
namespace asc {
template<class Integer> constexpr Integer aligned_size(Integer size, Integer alignment) noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Integer` | Integer type shared by the size and the alignment multiple; intermediate results of addition, division, and multiplication must be representable in this type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `size` | Input | Non-negative integer size to round up, in the same unit as alignment. |
| `alignment` | Input | Non-negative integer multiple to round to; 0 keeps the original size, and a positive value is not required to be a power of two. |

## Return Value

| Return type | Description |
| --- | --- |
| `Integer` | Returns `size` when `alignment == 0`; otherwise returns the smallest multiple of alignment that is not less than `size`. |

## Constraints

- `size >= 0` and `alignment >= 0`; a positive `alignment` may be a non-power-of-two value such as 7; this does not mean that memory allocation interfaces also accept that alignment value.
- When `alignment > 0`, `size + alignment - 1` and the final result must be representable in `Integer`; the interface does not detect arithmetic overflow. When `alignment == 0`, these intermediate expressions are not evaluated.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/memory>

bool example()
{
    return asc::aligned_size(10, 7) == 14 && asc::aligned_size(10, 0) == 10;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
