# asc::std::mdspan::`operator=`

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

`asc::std::mdspan::operator=` updates the object with the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::mdspan`](mdspan.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
constexpr mdspan<Element, Extents, Layout, Accessor>& operator=(const mdspan<Element, Extents, Layout, Accessor>& other);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
constexpr mdspan<Element, Extents, Layout, Accessor>& operator=(mdspan<Element, Extents, Layout, Accessor>&& other);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers the state through the move operations of the corresponding members. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers the state through the move operations of the corresponding members. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `mdspan<Element, Extents, Layout, Accessor> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 2 | `mdspan<Element, Extents, Layout, Accessor> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |

## Constraints

- Starting from C++17, the one-dimensional `operator[]` can be used; the multi-argument `operator[]` is available according to the compiler's C++23 multidimensional subscript feature.
- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host snippet demonstrates the call with concrete capacities or dimensions; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

void example(asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>& target, const asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>& source)
{
    target = source;
}
```

## Related APIs

- [`asc::std::mdspan`](mdspan.md)
- [API list for this header](asc_std_mdspan.md)
