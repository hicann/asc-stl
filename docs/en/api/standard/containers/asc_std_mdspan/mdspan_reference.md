# asc::std::mdspan::reference

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

Header: `<asc/std/mdspan>`.

`asc::std::mdspan::reference` identifies the writable element reference type.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

Member of: [`asc::std::mdspan`](mdspan.md).

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
using reference = typename Accessor::reference;
```

## Constraints

- This type alias is provided starting from C++17; for the access forms and language conditions of the owning type, see [`mdspan`](mdspan.md#constraints).

- This public alias is determined by the selected `Element`, `Extents`, `Layout`, or `Accessor`; the type query does not access underlying elements.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

void use_type()
{
    using alias_type = typename asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>::reference;
}
```

## Related APIs

- [`asc::std::mdspan`](mdspan.md)
- [API list for this header](asc_std_mdspan.md)
