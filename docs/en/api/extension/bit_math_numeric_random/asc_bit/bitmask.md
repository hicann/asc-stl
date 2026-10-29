# asc::bitmask

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

`asc::bitmask` generates a 32-bit or 64-bit unsigned integer mask that sets `width` consecutive bits starting from bit `start` to 1, with all other bits 0.

## Function Prototype

```cpp
namespace asc {
template<class T = asc::std::uint32_t> constexpr T bitmask(int start, int width) noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Unsigned integer type of the mask; must be uint32_t or uint64_t, and defaults to uint32_t when omitted. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `start` | Input | Bit index of the start of the mask (the lowest bit is bit 0); must not be negative. |
| `width` | Input | Number of consecutive bits set to 1 in the mask, extending from bit `start` toward higher bits; must not be negative. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns a 32-bit or 64-bit unsigned integer mask that sets `width` consecutive bits starting from bit `start` to 1, with all other bits 0. |

## Constraints

- T must be uint32_t or uint64_t.
- When start/width is out of range (negative, exceeding the bit width, or start+width extending past the type's bit-width window), the result is clamped to T{0} instead of causing undefined behavior; zero width likewise returns T{0}, a full-width window normally generates an all-ones mask, and no valid input produces an undefined shift.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bitmask<unsigned int>(2, 3);
}

bool verify_example()
{
    return example() == 28u;
}
```

## Related APIs

- [API list for this header](asc_bit.md)
