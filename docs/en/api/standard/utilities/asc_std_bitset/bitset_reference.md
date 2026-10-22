# asc::std::bitset::reference

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

`asc::std::bitset::reference` identifies the writable element reference type.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Declaration

Member of: [`asc::std::bitset`](bitset.md).

```cpp
// Excerpt of the declaration inside class asc::std::bitset; template parameters and other members are provided by the owning class.
using reference = typename base::reference;
```

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. reference is a writable bit proxy rather than bool&, and depends on the original object; const_reference is a bool returned by value.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/bitset>
#include <asc/std/type_traits>

bool example()
{
    asc::std::bitset<8> bits;
    using proxy = typename asc::std::bitset<8>::reference;
    proxy selected = bits[2];
    selected = true;
    if (!bits[2]) return false;
    selected.flip();
    return !bits[2];
}
```

## Related APIs

- [`asc::std::bitset`](bitset.md)
- [API list for this header](asc_std_bitset.md)
