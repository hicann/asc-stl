# asc::gm_mdspan

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

Header: `<asc/mdspan>`.

`asc::gm_mdspan` is an mdspan alias that uses gm_accessor to access GM data.

## Declaration

```cpp
namespace asc {
template <class Element, class Extents, class Layout = asc::std::layout_right,
    class Accessor = asc::std::default_accessor<Element>>
using gm_mdspan = asc::std::mdspan<Element, Extents, Layout, asc::gm_accessor<Accessor>>;
}  // namespace asc
```

## Constraints

- The view and the accessor do not own the storage; the SIMD handle keeps the GM address space, the Host representation does not mean the device address can be dereferenced on the Host, and the storage must cover all accesses.


## Example

The following snippet shows the alias type with concrete template arguments.

```cpp
#include <asc/mdspan>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

void use_type()
{
    using selected = asc::gm_mdspan<int, asc::std::extents<asc::std::size_t, 4>>;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
