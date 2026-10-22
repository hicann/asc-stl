# asc::bit_reverse

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

`asc::bit_reverse` reverses all binary bits of a 32-bit or 64-bit unsigned integer, swapping the lowest bit with the highest bit, the second-lowest bit with the second-highest bit, and so on.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr T bit_reverse(T value) noexcept;
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
| `value` | Input | Unsigned integer value whose binary bits are all to be reversed. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the integer with all binary bits in reverse order. |

## Constraints

- T must be uint32_t or uint64_t.
- Reverses the bit order of the entire input type; this function has no start or width parameters.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bit_reverse(0x12u);
}
```

## Related APIs

- [API list for this header](asc_bit.md)
