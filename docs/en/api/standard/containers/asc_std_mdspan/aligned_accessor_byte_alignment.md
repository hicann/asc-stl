# asc::std::aligned_accessor::byte_alignment

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

`asc::std::aligned_accessor::byte_alignment` gives the number of alignment bytes required by the accessor for the starting address of the data.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

Member of: [`aligned_accessor<Element, ByteAlignment>`](aligned_accessor.md).

```cpp
static constexpr size_t byte_alignment = ByteAlignment;
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    asc::std::aligned_accessor<int, 16> accessor;
    static_assert(decltype(accessor)::byte_alignment == 16);
    return accessor.access(values, 1) == 2;
}
```

## Related APIs

- [`asc::std::aligned_accessor`](aligned_accessor.md)
- [API list for this header](asc_std_mdspan.md)
