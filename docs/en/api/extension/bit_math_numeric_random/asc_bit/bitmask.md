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
| `T` | The same type as `asc::std::uint32_t` or `asc::std::uint64_t`; defaults to `asc::std::uint32_t`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `start` | Input | Bit index of the start of the mask (the lowest bit is bit 0); invalid parameters follow the rules below. |
| `width` | Input | Number of consecutive bits set to 1 in the mask, extending from bit `start` toward higher bits; invalid parameters follow the rules below. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns a 32-bit or 64-bit unsigned integer mask that sets `width` consecutive bits starting from bit `start` to 1, with all other bits 0. |

## Constraints

- `T` must be the same type as `asc::std::uint32_t` or `asc::std::uint64_t`. Equivalent aliases match; a different type with the same width does not. Unsupported types are excluded from overload resolution.
- Value deduction removes top-level cv qualifiers; an explicitly specified cv/ref type is excluded.
- Supports C++17/C++20, Host, SIMT threads, and ordinary scalar code in SIMD kernels. Constant evaluation and runtime calls have identical results and do not throw.
- `T` defaults to `asc::std::uint32_t`; specify `asc::std::uint64_t` explicitly for a 64-bit result.
- Bit 0 is the least significant bit. Numbering describes the integer value, independently of memory byte order or C++ bit-field layout.
- For width `W`, a valid window satisfies `0 <= start && start <= W && 0 <= width && width <= W - start`.
- Bits in `[start, start + width)` are one; all other bits are zero.
- Zero width (including `(W, 0)`) or an invalid window returns `T{0}`; `(0, W)` returns all `W` bits set.
- Negative, oversized, and crossing windows, including any extreme `int` parameters, follow the invalid-window rule. Windows are neither shortened nor reduced modulo the width.

## Example

```cpp
#include <asc/bit>
#include <asc/std/cstdint>

using u64 = asc::std::uint64_t;
static_assert(asc::bitmask(4, 8) == asc::std::uint32_t{0xFF0});
static_assert(asc::bitmask<u64>(0, 64) == u64{0xFFFFFFFFFFFFFFFF});

bool verify_example()
{
    return asc::bitmask<u64>(64, 0) == u64{0} && asc::bitmask(-1, 4) == asc::std::uint32_t{0};
}
```

## Related APIs

- [API list for this header](asc_bit.md)
