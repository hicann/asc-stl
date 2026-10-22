# asc::std::variant_alternative::type

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

Header: `<asc/std/variant>`.

`asc::std::variant_alternative::type` provides the member type computed by this type trait, mapping, or adaptor.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Declaration

`asc::std::variant_alternative<Index, Variant>::type` is the Index-th alternative type of Variant; Variant's cv qualification is applied to the resulting type. Index must be less than variant_size_v<Variant>.

```cpp
using Variant = const asc::std::variant<int, float>;
using Alternative = asc::std::variant_alternative<1, Variant>::type; // const float
```

## Constraints

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example defines the required aliases independently and checks the alternative type at index 0.

```cpp
#include <asc/std/variant>
#include <asc/std/type_traits>

using Variant = asc::std::variant<int, float>;
using First = typename asc::std::variant_alternative<0, Variant>::type;
static_assert(asc::std::is_same_v<First, int>);
```

## Related APIs

- [API list for this header](asc_std_variant.md)
