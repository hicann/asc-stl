# asc::std::bitset::base

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

`asc::std::bitset::base` identifies the underlying storage type used by the bitset.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Declaration

`asc::std::bitset<Size>::base` is the underlying storage type alias exposed by the current implementation; the concrete type is an implementation detail, and the existence of public types/parameters named Bitset or Nwords must not be assumed. General code should use the public members of bitset.

```cpp
using Storage = asc::std::bitset<8>::base;
```

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. base is a public alias of the storage implementation type; users usually manipulate bits through the public members of bitset.

## Example

The following Host example uses concrete types and an independent expectation to check an alias or marker result.

```cpp
#include <asc/std/bitset>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = typename asc::std::bitset<8>::base;
    static_assert(asc::std::is_base_of_v<alias_type, asc::std::bitset<8>>);
}
```

## Related APIs

- [API list for this header](asc_std_bitset.md)
