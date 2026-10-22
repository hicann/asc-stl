# asc::std::layout_left::mapping::`operator!=`

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

`asc::std::layout_left::mapping::operator!=` is the negation of the equality comparison: two mappings are equal when they have the same number of dimensions and equal per-dimension extents and offsets.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: `layout_left`::`mapping`<`Extents`>. The following is a declaration summary of the hidden friend, omitting implementation parameters used only for participation selection; it is called with operator syntax.

### Prototype 1

```cpp
template<class OtherExtents>
friend constexpr bool operator!=(const mapping& left, const mapping<OtherExtents>& right) noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherExtents` | The dimension type of the other mapping; the ranks must be the same. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left layout mapping; its dimensions and the applicable stride information are compared. |
| `right` | Input | The right layout mapping; no underlying elements are read. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the two mappings are unequal. |

## Constraints

- The ranks of both `mapping` sides must be the same.
- The explicit inequality function above is provided only for C++17; in C++20, inequality calls are rewritten by the equality operator.
- Compares the dimensions and the corresponding layout information; it does not access or compare underlying elements.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    using shape_type = asc::std::extents<asc::std::size_t, 2, 3>;
    using mapping_type = asc::std::layout_left::mapping<shape_type>;
    const mapping_type first(shape_type{});
    const mapping_type second(shape_type{});
    return !(first != second);
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
