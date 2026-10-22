# asc::std::bitset::count

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

`asc::std::bitset::count` returns the number of bits set to 1 in the current bitset; there is no key or lookup-target parameter.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

Member of: [`asc::std::bitset`](bitset.md).

```cpp
// Excerpt of the declaration inside class asc::std::bitset; template parameters and other members are provided by the owning class.
constexpr size_t count() const noexcept;
```


## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the number of bits set to 1 in the current bitset; there is no key or lookup-target parameter. |

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/bitset>

bool example()
{
    asc::std::bitset<8> bits(5);
    return bits.count() == 2;
}
```

## Related APIs

- [`asc::std::bitset`](bitset.md)
- [API list for this header](asc_std_bitset.md)
