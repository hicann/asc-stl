# asc::std::bitset::`operator==`

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

`asc::std::bitset::operator==` compares whether two objects satisfy the equality relation.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

Member of: [`asc::std::bitset`](bitset.md).

```cpp
// Excerpt of the declaration inside class asc::std::bitset; template parameters and other members are provided by the owning class.
constexpr bool operator==(const bitset<Size>& other) const noexcept;
```


## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The other operand of the comparison; this comparison does not modify the object. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. The two operands must have the same `Size`; the binary bitwise operation combines bits bit by bit and does not involve the construction-source state.

## Example

The following Host snippet demonstrates a concrete call with an 8-bit bitset; indices must be within the valid range.

```cpp
#include <asc/std/bitset>

decltype(auto) example(asc::std::bitset<8>& left, const asc::std::bitset<8>& right)
{
    return (left == right);
}
```

## Related APIs

- [`asc::std::bitset`](bitset.md)
- [API list for this header](asc_std_bitset.md)
