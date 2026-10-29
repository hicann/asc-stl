# asc::std::bitset::`operator<<`

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

`asc::std::bitset::operator<<` processes the current object and the operand according to the operators available for `bitset`.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

Member of: [`asc::std::bitset`](bitset.md).

```cpp
// Excerpt of the declaration inside class asc::std::bitset; template parameters and other members are provided by the owning class.
constexpr bitset<Size> operator<<(size_t shift) const noexcept;
```


## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `shift` | Input | The number of bits to shift left; returns a new bitset after the shift, the original object is unchanged, and the vacated low bits are filled with 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `bitset<Size>` | Returns the new bitset after the shift or bitwise inversion. |

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. The shift count is a size_t; when the count is greater than or equal to `Size`, all bits of the result are 0.

## Example

The following Host snippet demonstrates a concrete call with an 8-bit bitset; indices must be within the valid range.

```cpp
#include <asc/std/bitset>

decltype(auto) example(asc::std::bitset<8>& bits)
{
    return (bits << 1);
}

bool verify_example()
{
    asc::std::bitset<8> bits(3u);
    return example(bits).to_ulong() == 6u;
}
```

## Related APIs

- [`asc::std::bitset`](bitset.md)
- [API list for this header](asc_std_bitset.md)
