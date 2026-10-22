# asc::std::ranges::random_access_range

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

`asc::std::ranges::random_access_range` checks the following range condition: satisfies bidirectional_range, and iterator_t<T> satisfies random_access_iterator.

C++17 provides a same-named `inline constexpr bool` variable template; C++20 and above with concepts enabled provide a native concept. Both forms can be used in `static_assert`, and in C++17 it can also be used together with `enable_if`. Constrained template parameters, `requires`, and partial ordering of constraints still require C++20 language support.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

In C++17 this public name is an inline constexpr bool variable template; in C++20 with concepts enabled it is a native concept. The following queries its Boolean value through the same public name and is not a redeclaration of this interface; satisfies_random_access_range is only an example query name.

```cpp
template<class T>
inline constexpr bool satisfies_random_access_range = asc::std::ranges::random_access_range<T>;
```

## Constraints

- Satisfies bidirectional_range, and iterator_t<T> satisfies random_access_iterator.
- The same-named C++17 Boolean template can be used in static_assert or SFINAE; native concept syntax and constraint subsumption require the corresponding C++20 language capabilities.
- A compile-time condition holding still requires users to observe iterator validity, complexity, and the corresponding semantic requirements.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::random_access_range<int[3]>);
static_assert(!asc::std::ranges::random_access_range<int>);
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
