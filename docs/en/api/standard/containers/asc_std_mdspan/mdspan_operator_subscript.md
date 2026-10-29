# asc::std::mdspan::`operator[]`

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

`asc::std::mdspan::operator[]` accesses the specified element when the caller guarantees the index is valid.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::mdspan`](mdspan.md).

### Prototype 1

```cpp
// Declaration summary inside the class for the one-dimensional call; internal SFINAE omitted.
// rank()==1; OtherIndexType must be convertible and able to construct index_type without throwing.
template<class OtherIndexType>
constexpr reference operator[](OtherIndexType index) const;
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
// Declaration summary inside the class for the multidimensional call; internal SFINAE omitted.
// The number of subscripts must equal rank(), and each subscript must be convertible to index_type.
template<class... OtherIndexTypes>
[[nodiscard]] constexpr reference operator[](OtherIndexTypes... indices) const;
```

Provided only when the language mode is higher than C++20 and the compiler defines `__cpp_multidimensional_subscript >= 202110L`; in C++17 and C++20, the one-dimensional scalar or `array`/`span` subscript forms can be used.

### Prototype 3

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
template<class OtherIndexType> constexpr reference operator[](const array<OtherIndexType, Extents::rank()>& indices) const;
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 4

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
template<class OtherIndexType> constexpr reference operator[](span<OtherIndexType, Extents::rank()> indices) const;
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The type of the one-dimensional subscript argument; it must be convertible to `index_type` and able to construct that type without throwing. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The element subscript; applicable to views of rank 1, it must satisfy 0 <= subscript < extent(0), and out-of-range values violate the call precondition; optional debug assertions do not constitute a bounds-checking guarantee. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexTypes` | The pack of subscript types arranged in dimension order; the count must equal the rank, and each type must be convertible to `index_type`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `indices` | Input | The pack of element subscripts given in dimension order; the count must equal the rank, each subscript must fall within the extent of the corresponding dimension, and out-of-range values violate the call precondition; optional debug assertions do not constitute a bounds-checking guarantee. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The type of the subscripts in the `array`; it must be convertible to `index_type`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `indices` | Input | The `array` holding the subscript of each dimension in dimension order; its length must equal the rank, each subscript must fall within the extent of the corresponding dimension, and out-of-range values violate the call precondition; optional debug assertions do not constitute a bounds-checking guarantee. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherIndexType` | The type of the subscripts in the `span`; it must be convertible to `index_type`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `indices` | Input | The `span` holding the subscript of each dimension in dimension order; its length must equal the rank, each subscript must fall within the extent of the corresponding dimension, and out-of-range values violate the call precondition; optional debug assertions do not constitute a bounds-checking guarantee. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `reference` | Returns the element reference or proxy value at the specified index; the index must be valid. |
| Prototype 2 | `reference` | Returns the element reference or proxy value at the specified index; the index must be valid. |
| Prototype 3 | `reference` | Returns the element reference or proxy value at the specified index; the index must be valid. |
| Prototype 4 | `reference` | Returns the element reference or proxy value at the specified index; the index must be valid. |

## Constraints

- When the multidimensional subscript feature is not enabled, the one-dimensional scalar form is provided starting from C++17 and requires `rank()`==1.
- When the multidimensional subscript feature is enabled, the variadic scalar form requires the number of subscripts to equal `rank()` and also handles one-dimensional calls.
- Both the `array` form and the fixed-extent `span` form are provided starting from C++17; the container length equals `rank()`.
- Each subscript must be convertible and able to construct `index_type` without throwing and must be within the valid range of the corresponding dimension.
- The data handle and address space are determined by `Accessor`; this interface performs no additional GM/UB pointer conversion.

## Example

The following Host snippet demonstrates the call with concrete capacities or dimensions; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>
#include <cstddef>
#include <type_traits>

bool example()
{
    int data[4] = {1, 2, 3, 4};
    asc::std::mdspan<int, asc::std::extents<::std::size_t, 4>> value(data);
    value[1] = 9;
    const auto& observed = value;
    return data[1] == 9 && observed[0] == 1;
}
```

## Related APIs

- [`asc::std::mdspan`](mdspan.md)
- [API list for this header](asc_std_mdspan.md)
