# Header asc/bit

Provides bit reversal, mask generation, and bit field extraction and insertion for unsigned 32-bit and 64-bit integers

## Usage

```cpp
#include <asc/bit>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::bit_reverse](bit_reverse.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::bitfield_extract](bitfield_extract.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::bitfield_insert](bitfield_insert.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::bitmask](bitmask.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |

## Common Rules

Only `asc::std::uint32_t`, `asc::std::uint64_t`, and equivalent aliases participate in overload resolution. Bit numbering starts at the least significant bit 0 and is independent of byte order. Both insertion values deduce one type; explicitly selecting that type permits ordinary value-parameter conversions.

The three window operations share one validity rule. For zero-width or invalid windows, extraction and masks return zero and insertion returns the original destination. A valid full-width window returns the input, source, or all-one mask, respectively. Host, SIMT threads, and scalar code in SIMD kernels follow identical C++17/20 rules; all functions are `constexpr` and `noexcept`.

Bit reversal mirrors individual bit positions, byte swapping reorders bytes, and rotation preserves cyclic bit order.

[Boundary behavior and migration notes](../../../../../release/bit_changes.md)
