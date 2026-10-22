# asc::std::ranges::range_common_reference_t

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

Header: `<asc/std/ranges>`.

`asc::std::ranges::range_common_reference_t` computes the result type according to the range or iterator property indicated by the name.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

```cpp
namespace asc::std::ranges {
template<class Rp> using range_common_reference_t = iter_common_reference_t<iterator_t<Rp>>;
} // namespace asc::std::ranges
```

## Constraints

- Supports arrays and user-defined ranges; does not support initializer_list expressions formed only of braces.

## Example

The following snippet selects concrete template arguments to show the alias type.

```cpp
#include <asc/std/ranges>

void use_type()
{
    using selected = asc::std::ranges::range_common_reference_t<int (&)[4]>;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
