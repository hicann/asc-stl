# asc::std::ranges::enable_view

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

`asc::std::ranges::enable_view` marks a type as usable as a range view.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

enable_view is an initialized inline constexpr bool variable template: it recognizes views through public inheritance of view_base or a matching view_interface, and it can also be designated according to the allowed specialization rules. The following queries the provided public variable; is_enabled_view is only an example name.

```cpp
template<class T>
inline constexpr bool is_enabled_view = asc::std::ranges::enable_view<T>;
```

## Constraints

- Enabled through public and convertible view_base inheritance, or a recognizable view_interface derivation relationship.
- enable_view being true does not by itself guarantee the range and movable conditions, nor does it guarantee owning elements; the view concept also checks these conditions.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::enable_view<asc::std::ranges::single_view<int>>);
static_assert(!asc::std::ranges::enable_view<int[3]>);
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
