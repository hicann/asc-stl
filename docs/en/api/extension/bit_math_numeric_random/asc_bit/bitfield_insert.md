# asc::bitfield_insert

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

`asc::bitfield_insert` replaces the bit field starting at bit `start` of `destination` with the low `width` bits of `source`, keeping the remaining bits of the destination value.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr T bitfield_insert(T destination, T source, int start, int width) noexcept;
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
| `destination` | Input | Target integer value containing the bit field to be replaced; passed by value, the replacement result is returned, with no storage lifetime involved. |
| `source` | Input | Source integer value supplying the replacement bits for the bit field; passed by value, with no storage lifetime involved. |
| `start` | Input | Bit index of the start of the bit field to be replaced within `destination` (the lowest bit is bit 0); invalid parameters follow the rules below. |
| `width` | Input | Number of bits in the bit field to be replaced; invalid parameters follow the rules below. |
## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the integer value after the specified bit field is replaced. |

## Constraints

- `T` must be the same type as `asc::std::uint32_t` or `asc::std::uint64_t`. Equivalent aliases match; a different type with the same width does not. Unsupported types are excluded from overload resolution.
- Value deduction removes top-level cv qualifiers; an explicitly specified cv/ref type is excluded.
- Supports C++17/C++20, Host, SIMT threads, and ordinary scalar code in SIMD kernels. Constant evaluation and runtime calls have identical results and do not throw.
- Both value arguments deduce the same `T`; an explicitly specified supported `T` uses ordinary C++ value-parameter conversions.
- Bit 0 is the least significant bit. Numbering describes the integer value, independently of memory byte order or C++ bit-field layout.
- For width `W`, a valid window satisfies `0 <= start && start <= W && 0 <= width && width <= W - start`.
- Source bit `j` replaces destination bit `start + j`. Other source bits are ignored; destination bits outside the interval are preserved in the returned value.
- Zero width (including `(W, 0)`) or an invalid window returns `destination`; `(0, W)` returns `source`. `(W - 1, 1)` selects the highest bit.
- Negative, oversized, and crossing windows, including any extreme `int` parameters, follow the invalid-window rule. Windows are neither shortened nor reduced modulo the width.

## Example

```cpp
#include <asc/bit>
#include <asc/std/cstdint>

using u32 = asc::std::uint32_t;
constexpr auto word = asc::bitfield_insert(u32{0xA5A50000}, u32{0x1AB}, 4, 8);
static_assert(word == u32{0xA5A50AB0});
static_assert(asc::bitfield_insert(u32{7}, u32{0}, 32, 0) == u32{7});

bool verify_example()
{
    return asc::bitfield_insert(u32{7}, u32{0}, 31, 2) == u32{7};
}
```

## Related APIs

- [API list for this header](asc_bit.md)
