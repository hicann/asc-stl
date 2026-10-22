# asc::std::ranges::range_size_t

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

`asc::std::ranges::range_size_t` computes the result type according to the range or iterator property indicated by the name.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

The following is a declaration summary expressing the type result with public CPOs and type traits; R must satisfy range, and range_size_t additionally requires sized_range.

```cpp
namespace asc::std::ranges {
template<class R>
using range_size_t = decltype(::asc::std::ranges::size(::asc::std::declval<R&>()));
}
```

## Constraints

- This is a compile-time query of the type obtained by accessing the range as an lvalue; it does not invoke runtime traversal and does not extend the lifetime of the range or elements.
- `R` must satisfy `range`; the size type query additionally requires `ranges::size` to be valid.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>

using result = asc::std::ranges::range_size_t<int (&)[3]>;
static_assert(asc::std::is_same_v<result, asc::std::size_t>);
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
