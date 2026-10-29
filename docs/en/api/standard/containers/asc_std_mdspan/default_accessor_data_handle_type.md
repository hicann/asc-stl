# asc::std::default_accessor::data_handle_type

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

`asc::std::default_accessor::data_handle_type` identifies the underlying data handle type held by the accessor.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

Member of: [`asc::std::default_accessor`](default_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::default_accessor class; template parameters and other members are provided by the owning class.
using data_handle_type = Element*;
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::default_accessor<int>::data_handle_type;
static_assert(::std::is_same_v<alias_type, int*>);
```

## Related APIs

- [`asc::std::default_accessor`](default_accessor.md)
- [API list for this header](asc_std_mdspan.md)
