# asc::std::bitset::bitset

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

`asc::std::bitset::bitset` initializes a `bitset` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

### Prototype 1

```cpp
bitset() noexcept;
```

### Prototype 2

```cpp
bitset(unsigned long long value) noexcept;
```


## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The unsigned integer value used to initialize the bits; its low `min(Size, 64)` binary bits are taken as the initial value, and the excess bits are ignored. |

## Return Value

No return value.

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. Default construction sets all bits to 0; integer construction reads the low bits of the input and clears the bits beyond `Size`.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/bitset>

bool example()
{
    asc::std::bitset<8> bits(5);
    return bits.size() == 8 && bits.count() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_bitset.md)
