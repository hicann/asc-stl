# asc::std::mdspan::`operator()`

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

`asc::std::mdspan::operator()` accesses an element with multidimensional subscripts; the number of subscripts must equal the number of dimensions, and each must be convertible to the index type.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

```cpp
// Declaration summary inside the asc::std::mdspan<Element, Extents, Layout, Accessor> class.
// Internal SFINAE omitted: every type in Indices... must be convertible to index_type.
template<class... Indices>
[[nodiscard]] constexpr reference operator()(Indices... indices) const;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Indices` | The argument type of the subscript for each dimension; it must be convertible to index_type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `indices` | Input | Per-dimension subscripts; the count must be rank(), and dimension r must satisfy 0 <= index < extent(r). |

## Return Value

| Return type | Description |
| --- | --- |
| `reference` | The result of computing the offset through mapping and letting accessor perform the access; the concrete reference or proxy value type is determined by Accessor::reference. |

## Constraints

- The number of subscripts equals the number of dimensions, and each subscript is explicitly convertible to the index type.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::mdspan<int, asc::std::extents<int, 2, 2>> view(values);
    view(1, 0) = 7;
    return values[2] == 7 && view(0, 1) == 2;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
