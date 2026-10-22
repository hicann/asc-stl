# asc::std::mdspan::mdspan

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

`asc::std::mdspan::mdspan` initializes an `mdspan` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`mdspan<Element, Extents, Layout, Accessor>`](mdspan.md). The declaration summaries below are grouped by participation conditions, omitting implementation parameters used only for SFINAE selection; the explicit and non-explicit branch conditions are mutually exclusive.

### Prototype 1

```cpp
template<class Extents2 = Extents>
constexpr mdspan() noexcept(
    is_nothrow_default_constructible_v<data_handle_type>
    && is_nothrow_default_constructible_v<mapping_type>
    && is_nothrow_default_constructible_v<accessor_type>);
```

Participates only when `Extents2` contains at least one dynamic dimension and the data handle, the corresponding mapping, and the accessor are all default-constructible.

### Prototype 2

```cpp
constexpr mdspan(const mdspan& other) = default;
```

Copies the view metadata; validity follows the rules of the defaulted special members.

### Prototype 3

```cpp
constexpr mdspan(mdspan&& other) = default;
```

Moves the view metadata; the state of the source handle is determined by the move rules of its type.

### Prototype 4

```cpp
template<class... OtherIndexTypes>
explicit constexpr mdspan(data_handle_type pointer, OtherIndexTypes... exts);
```

The number of extents must equal `rank_dynamic()` or `rank()`; each value must be convertible and able to construct `index_type` without throwing, `mapping_type` must be constructible from `extents_type`, and `accessor_type` must be default-constructible.

### Prototype 5

```cpp
template<class OtherIndexType, size_t Size>
constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& exts);
```

This non-explicit branch is selected only when `Size`==`rank_dynamic()`. The elements must be convertible and able to construct `index_type` without throwing; the mapping must be constructible from `extents_type`, and the accessor must be default-constructible.

### Prototype 6

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& exts);
```

This explicit branch is selected only when `Size`==`rank()` and `Size`!=`rank_dynamic()`; the other construction conditions are the same as in the previous prototype.

### Prototype 7

```cpp
template<class OtherIndexType, size_t Size>
constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> exts);
```

This non-explicit branch is selected only when `Size`==`rank_dynamic()`; the element, mapping, and accessor conditions are the same as for the `array` form.

### Prototype 8

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> exts);
```

This explicit branch is selected only when `Size`==`rank()` and `Size`!=`rank_dynamic()`; the element, mapping, and accessor conditions are the same as above.

### Prototype 9

```cpp
template<class AccessorPolicy2 = Accessor, class Mapping2 = mapping_type>
constexpr mdspan(data_handle_type pointer, const extents_type& exts);
```

`AccessorPolicy2` must be default-constructible, and `Mapping2` must be constructible from const `extents_type`&.

### Prototype 10

```cpp
template<class AccessorPolicy2 = Accessor>
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping);
```

`AccessorPolicy2` must be default-constructible.

### Prototype 11

```cpp
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping, const accessor_type& accessor);
```

Stores the given handle, mapping, and accessor by value; the data handle must satisfy the access conditions of that accessor.

### Prototype 12

```cpp
template<class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor>
constexpr mdspan(
    const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other);
```

The target `mapping` and `accessor` must be constructible from const references to the source `mapping` and `accessor` respectively; this non-explicit branch is selected when both are implicitly convertible. The handle must be constructible from the source handle, and the dimensions must be convertible and satisfy the target static extents.

### Prototype 13

```cpp
template<class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor>
explicit constexpr mdspan(
    const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other);
```

The target `mapping` and `accessor` must be constructible from const references to the source `mapping` and `accessor` respectively; this explicit branch is selected when at least one of them is not implicitly convertible. The handle must be constructible from the source handle, and the dimensions must be convertible and satisfy the target static extents.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Extents2` | The dimension type used by the participation condition, defaulting to `Extents`. |

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source non-owning view; construction copies or moves the handle, mapping, and accessor without copying the underlying elements. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source non-owning view; construction copies or moves the handle, mapping, and accessor without copying the underlying elements. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexTypes` | The pack of per-dimension extent argument types. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
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
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
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
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 7

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The integer type of the source extent elements. |
| `Size` | The fixed number of elements of the `array` or `span`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 8

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The integer type of the source extent elements. |
| `Size` | The fixed number of elements of the `array` or `span`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 9

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `AccessorPolicy2` | The type used by the accessor condition, defaulting to `Accessor`. |
| `Mapping2` | The type used by the mapping condition, defaulting to `mapping_type`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
| `exts` | Input | The source dimension extents; a number of values equal to the dynamic-dimension count or the full rank may be provided, and each value must agree with the static dimensions and be representable by `index_type`. |

### Parameters of Prototype 10

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `AccessorPolicy2` | The type used by the accessor condition, defaulting to `Accessor`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
| `mapping` | Input | The stored layout mapping; it determines how logical indices are converted into data handle offsets. |

### Parameters of Prototype 11

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The data handle; the original storage must cover `mapping.required_span_size()` and the valid access range required by the accessor, and ownership is not acquired. |
| `mapping` | Input | The stored layout mapping; it determines how logical indices are converted into data handle offsets. |
| `accessor` | Input | The stored accessor; it determines the handle type, the element reference, and the address space or alignment requirements. |

### Parameters of Prototype 12

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherElement` | The source element type. |
| `OtherExtents` | The source dimension type; the rank and static dimensions must be compatible. |
| `OtherLayout` | The source layout policy. |
| `OtherAccessor` | The source accessor type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source non-owning view; construction copies or moves the handle, mapping, and accessor without copying the underlying elements. |

### Parameters of Prototype 13

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherElement` | The source element type. |
| `OtherExtents` | The source dimension type; the rank and static dimensions must be compatible. |
| `OtherLayout` | The source layout policy. |
| `OtherAccessor` | The source accessor type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source non-owning view; construction copies or moves the handle, mapping, and accessor without copying the underlying elements. |

## Return Value

No return value.

## Constraints

- The construction forms listed on this page are provided starting from C++17; for the element access forms and language conditions, see [`mdspan`](mdspan.md#constraints).

- The view does not own the underlying storage. The storage, accessor, and mapping must together guarantee that every valid index accesses a valid element.
- The storage range is determined by `mapping.required_span_size()` and the accessor requirements and must not be estimated from the product of the per-dimension extents alone; a mapping with stride gaps or padding may require more storage.
- All dimension extents must be non-negative and representable by `index_type`, and the full-extent form must agree with the static extents.
- The address space and alignment requirements of the data handle are defined by `Accessor`; this construction performs no additional GM/UB conversion.
- For the participation conditions and exception specification of the default constructor, see Prototype 1; for the template participation conditions of the other forms, see the descriptions of their respective prototypes.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    int storage[6] = {1, 2, 0, 0, 3, 4};
    using shape_type = asc::std::extents<asc::std::size_t, 2, 2>;
    const asc::std::array<asc::std::size_t, 2> strides{{4, 1}};
    const asc::std::layout_stride::mapping<shape_type> mapping(shape_type{}, strides);
    const asc::std::mdspan<int, shape_type, asc::std::layout_stride> view(storage, mapping);
    return view.size() == 4 && mapping.required_span_size() == 6 && view(1, 1) == 4;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
