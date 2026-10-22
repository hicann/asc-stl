# asc::std::extents::size_type

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

`asc::std::extents::size_type` identifies the unsigned type for the container size.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

Member of: [`extents`](extents.md). This type is the unsigned type corresponding to `index_type` and is not fixed to size_t.

```cpp
using size_type = make_unsigned_t<index_type>;
```

## Constraints

- This alias denotes the unsigned integer type used by the owning type for element counts or sizes; reading the type itself allocates no memory and accesses no elements.
- For the runtime conditions of construction, allocation, and access, see the owning type [asc::std::`extents`](extents.md).

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

using shape_type = asc::std::extents<int, 2, 3>;
static_assert(asc::std::is_same_v<shape_type::size_type, unsigned int>);
static_assert(asc::std::is_unsigned_v<shape_type::size_type>);
```

## Related APIs

- [`asc::std::extents`](extents.md)
- [API list for this header](asc_std_mdspan.md)
