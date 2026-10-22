# asc::std::endian

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

Header: `<asc/std/bit>`.

`asc::std::endian` lists the big-endian, little-endian, and native byte order labels.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Declaration

```cpp
namespace asc::std {
enum class endian;
} // namespace asc::std
```

## Constraints

- `endian::native` equals either `endian::little` or `endian::big`; mixed byte orders are not supported.
- Both the Host and device environments of this product are little-endian, that is, `endian::native == endian::little`.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/bit>

bool example()
{
    static_assert(asc::std::endian::little != asc::std::endian::big);
    // The currently supported Host and Device use a purely big-endian or purely little-endian byte order.
    return asc::std::endian::native == asc::std::endian::little || asc::std::endian::native == asc::std::endian::big;
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
