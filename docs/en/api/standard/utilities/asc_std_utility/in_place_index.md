# asc::std::in_place_index

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

Header: `<asc/std/utility>`.

`asc::std::in_place_index` marks in-place construction for the corresponding type or index.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Declaration

```cpp
namespace asc::std {
template<size_t Idx> inline constexpr const in_place_index_t<Idx> in_place_index;
} // namespace asc::std
```

## Constraints

- Provides the complete standard form.

## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/std/type_traits>
#include <asc/std/utility>

inline constexpr auto example = asc::std::in_place_index<0>;

static_assert(asc::std::is_same_v<asc::std::remove_cv_t<decltype(example)>, asc::std::in_place_index_t<0>>);
```

## Related APIs

- [API list for this header](asc_std_utility.md)
