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
| `T` | The same type as `asc::std::uint32_t` or `asc::std::uint64_t`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Unsigned integer value whose bit field is to be extracted. |
| `start` | Input | Bit index of the start of the bit field within `value` (the lowest bit is bit 0); invalid parameters follow the rules below. |
| `width` | Input | Number of consecutive bits to extract; invalid parameters follow the rules below. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the bit field value extracted from the specified start bit and right-aligned. |

## Constraints

- `T` must be the same type as `asc::std::uint32_t` or `asc::std::uint64_t`. Equivalent aliases match; a different type with the same width does not. Unsupported types are excluded from overload resolution.
- Value deduction removes top-level cv qualifiers; an explicitly specified cv/ref type is excluded.
- Supports C++17/C++20, Host, SIMT threads, and ordinary scalar code in SIMD kernels. Constant evaluation and runtime calls have identical results and do not throw.
- Bit 0 is the least significant bit. Numbering describes the integer value, independently of memory byte order or C++ bit-field layout.
- For width `W`, a valid window satisfies `0 <= start && start <= W && 0 <= width && width <= W - start`.
- Bits in a nonempty valid interval `[start, start + width)` are right-aligned with zero-filled upper bits.
- Zero width (including `(W, 0)`) or an invalid window returns `T{0}`; `(0, W)` returns the input. `(W - 1, 1)` selects the highest bit.
- Negative, oversized, and crossing windows, including any extreme `int` parameters, follow the invalid-window rule. Windows are neither shortened nor reduced modulo the width.

## Example

```cpp
#include <asc/bit>
#include <asc/std/cstdint>

using u32 = asc::std::uint32_t;
constexpr auto field = asc::bitfield_extract(u32{0xA5A50AB0}, 4, 8);
static_assert(field == u32{0xAB});
static_assert(asc::bitfield_extract(u32{1}, 32, 0) == u32{0});

bool verify_example()
{
    return asc::bitfield_extract(u32{0xFFFFFFFF}, 31, 2) == u32{0};
}
```

## Related APIs

- [API list for this header](asc_bit.md)
