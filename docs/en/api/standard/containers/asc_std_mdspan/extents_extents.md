# asc::std::extents::extents

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

`asc::std::extents::extents` initializes an `extents` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`extents<IndexType, Extents...>`](extents.md). The declaration summaries below are grouped by mutually exclusive participation conditions, omitting parameters used only for SFINAE; all listed constructors are `noexcept`.

### Prototype 1

```cpp
constexpr extents() noexcept = default;
```

The static dimensions are fixed by the template arguments, and the dynamic dimensions default to 0.

### Prototype 2

```cpp
template<class... OtherIndexTypes>
explicit constexpr extents(OtherIndexTypes... dynvals) noexcept;
```

The number of arguments must be `rank_dynamic()` or `rank()`; each argument must be convertible and able to construct `index_type` without throwing.

### Prototype 3

```cpp
template<class OtherIndexType, size_t Size>
constexpr extents(const array<OtherIndexType, Size>& exts) noexcept;
```

This non-explicit overload is selected when `Size`==`rank_dynamic()`; the elements must be convertible and able to construct `index_type` without throwing.

### Prototype 4

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr extents(const array<OtherIndexType, Size>& exts) noexcept;
```

This explicit overload is selected when `Size`==`rank()` and `Size`!=`rank_dynamic()`; the element conditions are the same as in the previous prototype.

### Prototype 5

```cpp
template<class OtherIndexType, size_t Size>
constexpr extents(span<OtherIndexType, Size> exts) noexcept;
```

This non-explicit overload is selected when `Size`==`rank_dynamic()`; the element conditions are the same as for the `array` form.

### Prototype 6

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr extents(span<OtherIndexType, Size> exts) noexcept;
```

This explicit overload is selected when `Size`==`rank()` and `Size`!=`rank_dynamic()`; the element conditions are the same as for the `array` form.

### Prototype 7

```cpp
template<class OtherIndexType, size_t... OtherStaticExtents>
constexpr extents(const extents<OtherIndexType, OtherStaticExtents...>& other) noexcept;
```

The ranks on both sides are the same, and the static dimensions must not conflict. This non-explicit overload is selected when neither a source dynamic dimension is converted into a target static dimension nor is the maximum value of `index_type` narrowed.

### Prototype 8

```cpp
template<class OtherIndexType, size_t... OtherStaticExtents>
explicit constexpr extents(const extents<OtherIndexType, OtherStaticExtents...>& other) noexcept;
```

The ranks on both sides are the same, and the static dimensions must not conflict. This explicit overload is selected when the target has a static dimension that is dynamic in the source, or the maximum value of the target `index_type` is smaller than the maximum value of the source type.

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexTypes` | The pack of per-dimension extent types. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `dynvals` | Input | The dynamic extents provided in dimension order, or the full extents including the static dimensions. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The integer type of the source extent elements. |
| `Size` | The fixed number of elements of the `array` or `span`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The integer type of the source extent elements. |
| `Size` | The fixed number of elements of the `array` or `span`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The integer type of the source extent elements. |
| `Size` | The fixed number of elements of the `array` or `span`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 6

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The integer type of the source extent elements. |
| `Size` | The fixed number of elements of the `array` or `span`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 7

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The source `index_type`. |
| `OtherStaticExtents` | The static extent or `dynamic_extent` marker of each source dimension. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source dimension values; after conversion, each value must be representable and agree with the target static dimensions. |

### Parameters of Prototype 8

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The source `index_type`. |
| `OtherStaticExtents` | The static extent or `dynamic_extent` marker of each source dimension. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source dimension values; after conversion, each value must be representable and agree with the target static dimensions. |

## Return Value

No return value.

## Constraints

- All runtime dimension extents must be non-negative and representable by `index_type`.
- The full-rank input form must supply the same values as the static dimensions; the dynamic-dimension-count form supplies only the dynamic positions.
- The `Size` of the `array`/`span` must equal `rank_dynamic()` or `rank()`; explicitness is distinguished as described in the prototypes.
- `extents` only stores the dimension values; it does not borrow the storage of the input `array`/`span`, and does not allocate or access element data.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    using dynamic_shape = asc::std::extents<int, asc::std::dynamic_extent, 3>;
    const asc::std::array<int, 1> dynamic_counts{{2}};
    const dynamic_shape from_array(dynamic_counts);
    const asc::std::extents<int, 2, 3> fixed(from_array);
    return from_array.extent(0) == 2 && from_array.extent(1) == 3
        && fixed.extent(0) == 2 && fixed.extent(1) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
