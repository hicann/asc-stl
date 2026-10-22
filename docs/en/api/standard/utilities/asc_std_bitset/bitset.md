# asc::std::bitset

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

Header: `<asc/std/bitset>`.

`asc::std::bitset` stores a fixed number of bits inside the object and provides queries and bit operations.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Declaration

```cpp
namespace asc::std {
template<size_t Size> class bitset;
} // namespace asc::std
```

## Constraints

- Default construction and construction from unsigned long long are supported.
- `operator[]` performs no bounds checking.
- Provides the full set of set, reset, flip, bitwise operations, shifts, state checks, counting, and capacity queries.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/bitset>

bool example()
{
    asc::std::bitset<8> bits(5ULL);
    bits[1] = true;
    return bits.count() == 3 && bits[0] && bits[1] && bits[2] && !bits[3];
}
```

## Related APIs

- [API list for this header](asc_std_bitset.md)
