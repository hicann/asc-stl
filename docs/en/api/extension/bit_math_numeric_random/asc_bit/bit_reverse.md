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
| `T` | The same type as `asc::std::uint32_t` or `asc::std::uint64_t`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Unsigned integer value whose binary bits are all to be reversed. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the integer with all binary bits in reverse order. |

## Constraints

- `T` must be the same type as `asc::std::uint32_t` or `asc::std::uint64_t`. Equivalent aliases match; a different type with the same width does not. Unsupported types are excluded from overload resolution.
- Value deduction removes top-level cv qualifiers; an explicitly specified cv/ref type is excluded.
- Supports C++17/C++20, Host, SIMT threads, and ordinary scalar code in SIMD kernels. Constant evaluation and runtime calls have identical results and do not throw.
- For width `W`, result bit `W - 1 - i` equals input bit `i`. Zero and all-one values are unchanged.
- Reversal mirrors individual bits; byte swapping reorders bytes, while rotation preserves cyclic bit order.

## Example

```cpp
#include <asc/bit>
#include <asc/std/cstdint>

using u32 = asc::std::uint32_t;
using u64 = asc::std::uint64_t;
static_assert(asc::bit_reverse(u32{0x0000000D}) == u32{0xB0000000});

bool verify_example()
{
    return asc::bit_reverse(u64{1}) == u64{0x8000000000000000};
}
```

## Related APIs

- [API list for this header](asc_bit.md)
