# asc::std::from_range

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

Header: `<asc/std/ranges>`.

`asc::std::from_range` marks that container construction reads elements from the input range.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

```cpp
namespace asc::std {
inline constexpr const from_range_t from_range;
} // namespace asc::std
```

## Constraints

- Seven names are listed.
- Bounded repeat, two-way random-access+sized zip reference write-back, and single range|closure application.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/type_traits>
#include <asc/std/ranges>

auto value = asc::std::from_range;

static_assert(asc::std::is_same_v<decltype(value), asc::std::from_range_t>);
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
