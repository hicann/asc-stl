# asc::is_gm_mdspan_v

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

`asc::is_gm_mdspan_v` indicates whether a type is an mdspan that uses a GM accessor.

## Declaration

```cpp
namespace asc {
template <class T>
inline constexpr bool is_gm_mdspan_v = false;
}  // namespace asc
```

## Constraints

- This is a compile-time type query; it does not read or write elements, query the Runtime, or establish device synchronization. The usable types are still gated by the corresponding execution location.

- The declaration shows the primary template; the corresponding wrapper or mdspan types are recognized by specializations in the header. Type matching does not automatically remove cv/ref qualifiers, and the query does not access actual data or the device.


## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/mdspan>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

inline constexpr auto example = asc::is_gm_mdspan_v<asc::gm_mdspan<int, asc::std::extents<asc::std::size_t, 4>>>;
static_assert(example, "the selected documented type has this capability");
```

## Related APIs

- [API list for this header](asc_mdspan.md)
