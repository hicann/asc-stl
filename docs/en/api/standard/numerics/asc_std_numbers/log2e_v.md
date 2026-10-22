# asc::std::log2e_v

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

Header: `<asc/std/numbers>`.

`asc::std::log2e_v` provides the compile-time value of the base-2 logarithm of e.

Standard semantics reference: [cppreference `numbers`](https://en.cppreference.com/w/cpp/header/numbers).

## Declaration

```cpp
namespace asc::std {
template<class Tp> inline constexpr Tp log2e_v = __numbers<Tp>::__log2e();
}
```

## Constraints

- Provides a float variable template.

## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/std/numbers>

inline constexpr auto example = asc::std::log2e_v<float>;
```

## Related APIs

- [API list for this header](asc_std_numbers.md)
