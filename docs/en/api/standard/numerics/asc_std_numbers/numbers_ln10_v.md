# asc::std::numbers::ln10_v

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

`asc::std::numbers::ln10_v` is provided by `<asc/std/numbers>` and provides the `ln10_v` constant or variable. The interface follows the semantics of the corresponding C++ standard facility; ASC-STL's language modes and call locations are governed by the declaration on this page.

Standard semantics reference: [cppreference `numbers`](https://en.cppreference.com/w/cpp/header/numbers).

## Declaration

```cpp
namespace asc::std::numbers {
template<class Tp> inline constexpr Tp ln10_v = __numbers<Tp>::__ln10();
}
```

## Constraints

- Provides a float variable template.
- ln(10) variable template, with the same bounds as above.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/numbers>

constexpr float value = asc::std::numbers::ln10_v<float>;
static_assert(value > 2.3f && value < 2.31f);
```

## Related APIs

- [API list for this header](asc_std_numbers.md)
