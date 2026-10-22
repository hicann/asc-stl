# asc::std::ranges::enable_borrowed_range

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

`enable_borrowed_range<T>` indicates whether a temporary range of type `T` allows safely returning its iterators; users specialize it only for types satisfying borrowing semantics.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This is the default value of the primary template; specializations allowed for the library and users can change the value for specific types.

```cpp
namespace asc::std::ranges {
template<class T>
inline constexpr bool enable_borrowed_range = false;
}
```

## Constraints

- The primary template defaults to false; only types satisfying the corresponding semantics should be specialized.
- Enabling borrowing requires that after the range object is destroyed, its valid iterators are not thereby invalidated; this does not extend the lifetime of external element storage.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::enable_borrowed_range<asc::std::ranges::ref_view<int[3]>>);
static_assert(!asc::std::ranges::enable_borrowed_range<int[3]>);
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
