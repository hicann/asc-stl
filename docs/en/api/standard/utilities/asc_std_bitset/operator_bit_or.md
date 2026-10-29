# asc::std::operator| (bitset overload) (function template)

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

`asc::std::operator|` returns the bitwise OR result of two equal-length bitsets.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

```cpp
namespace asc::std {
template<size_t Size> bitset<Size> operator|(const bitset<Size>& lhs, const bitset<Size>& rhs) noexcept;
} // namespace asc::std
```


## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Size` | The type or compile-time value representing the number of elements, dimension, bit width, or index, as determined by the declaration. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Provides the object reference used to "query the bitwise OR result of two equal-length bitsets"; the referenced object must be valid for the duration of the call. |
| `rhs` | Input | Provides the object reference used to "query the bitwise OR result of two equal-length bitsets"; the referenced object must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `bitset<Size>` | Returns the bitwise OR result of two equal-length bitsets. |

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. The two operands must have the same `Size`; the binary bitwise operation combines bits bit by bit and does not involve the construction-source state.

## Example

The following snippet shows the call with concrete types; declval is used only in unevaluated type expressions.

```cpp
#include <asc/std/bitset>

decltype(auto) example()
{
    asc::std::bitset<8> left(3u);
    asc::std::bitset<8> right(5u);
    return asc::std::operator|(left, right);
}

bool verify_example()
{
    return example().to_ulong() == 7u;
}
```

## Related APIs

- [API list for this header](asc_std_bitset.md)
