# asc::std::layout_stride::mapping::`operator==`

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

`asc::std::layout_stride::mapping::operator==` determines whether two strided mappings are equivalent: the number of dimensions, the per-dimension extents, and the strides are all equal, and the offset of the other mapping at the all-zero subscript is 0.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: `layout_stride`::`mapping`<`Extents`>. The following is a declaration summary of the hidden friend, omitting implementation parameters used only for participation selection; it is called with operator syntax.

### Prototype 1

```cpp
template<class OtherMapping>
friend constexpr bool operator==(const mapping& left, const OtherMapping& right) noexcept;
```

### Prototype 2

```cpp
template<class OtherMapping>
friend constexpr bool operator==(const OtherMapping& left, const mapping& right) noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherMapping` | The other mapping type; it must satisfy the layout mapping conditions below. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left layout mapping; its dimensions and the applicable stride information are compared. |
| `right` | Input | The right layout mapping; no underlying elements are read. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the two mappings are equivalent. |

## Constraints

- `OtherMapping` must satisfy the layout mapping requirements, have the same rank, and have `is_always_strided()` equal to true. The explicit swapped-direction form is provided only for C++17, and `OtherMapping` must not be a `layout_stride` mapping itself.
- Compares the dimensions and the corresponding layout information; it does not access or compare underlying elements.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    using shape_type = asc::std::extents<asc::std::size_t, 2, 3>;
    using mapping_type = asc::std::layout_stride::mapping<shape_type>;
    const asc::std::array<asc::std::size_t, 2> strides{{3, 1}};
    const mapping_type first(shape_type{}, strides);
    const mapping_type second(shape_type{}, strides);
    return first == second;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
