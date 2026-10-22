# asc::std::weak_ordering

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

Header: `<asc/std/compare>`.

`asc::std::weak_ordering` represents the comparison result of a weak ordering relation.

Standard semantics reference: [cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare).

## Declaration

```cpp
namespace asc::std {
class weak_ordering;
} // namespace asc::std
```

## Constraints

- ASC comparison category constants, comparison with zero, and standard category conversions are supported.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/compare>

bool example()
{
    auto result = asc::std::weak_ordering::equivalent;
    return result == 0;
}
```

## Related APIs

- [API list for this header](asc_std_compare.md)
