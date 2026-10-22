# asc::std::ranges::viewable_range

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

`asc::std::ranges::viewable_range` checks the following range conditions: satisfies range; if the type after removing cv/ref is a view, that view must be constructible from the original input; other ranges must be lvalues, or movable rvalue objects. Host excludes rvalue std::initializer_list, and Device does not introduce the Host initializer_list type.

In C++17, an `inline constexpr bool` variable template of the same name is provided; in C++20 and above with concepts enabled, a native concept is provided. Both forms can be used in `static_assert`, and in C++17 it can also be used with `enable_if`. Constrained template parameters, `requires`, and constraint subsumption still require C++20 language support.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

In C++17, this public name is an inline constexpr bool variable template; in C++20 with concepts enabled, it is a native concept. The following queries its boolean value under the same public name and does not redeclare the interface; satisfies_viewable_range is only an example query name.

```cpp
template<class T>
inline constexpr bool satisfies_viewable_range = asc::std::ranges::viewable_range<T>;
```

## Constraints

- Satisfies range; if the type after removing cv/ref is a view, that view must be constructible from the original input; other ranges must be lvalues, or movable rvalue objects. Host excludes rvalue std::initializer_list, and Device does not introduce the Host initializer_list type.
- The same-named boolean template in C++17 can be used in static_assert or SFINAE; native concept syntax and constraint subsumption require the corresponding C++20 language capabilities.
- The compile-time condition being satisfied still requires users to comply with iterator validity, complexity, and the corresponding semantic requirements.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::viewable_range<int (&)[3]>);
static_assert(!asc::std::ranges::viewable_range<int>);
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
