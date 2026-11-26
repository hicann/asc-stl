# asc::std::bitset::to_ullong

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

`asc::std::bitset::to_ullong` converts the bitset to unsigned long long and fails when the value is outside the representable range.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

The following is the declaration inside class `bitset<Size>`.

```cpp
template<size_t Width = Size, enable_if_t<(Size <= sizeof(unsigned long long) * CHAR_BIT && Width <= sizeof(unsigned long long) * CHAR_BIT), int> = 0>
constexpr unsigned long long to_ullong() const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Width` | Defaults to `Size` of the owning bitset; used for the compile-time check of the target integer width; a normal call does not need to specify it explicitly. |

No function parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned long long` | Returns the unsigned integer converted from the current bitset; values outside the target type's range are handled according to the constraints. |

## Constraints

- The default Width equals `Size`, and `Size` must not exceed the number of binary digits of the target unsigned integer type; the range is limited by the bit count, not merely by the currently set bit values. This subset does not provide the runtime overflow_error conversion.

- When Size is 0, the result is 0 regardless of the value supplied to the integer constructor.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/bitset>

bool example()
{
    asc::std::bitset<8> bits(5);
    asc::std::bitset<0> empty(~0ULL);
    return bits.to_ullong() == 5 && empty.to_ullong() == 0;
}
```

## Related APIs

- [`asc::std::bitset`](bitset.md)
- [API list for this header](asc_std_bitset.md)
