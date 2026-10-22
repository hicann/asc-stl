# asc::std::unexpected

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

Header: `<asc/std/expected>`.

`asc::std::unexpected` wraps an error value for use by expected.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Declaration

```cpp
namespace asc::std {
template<class Error> class unexpected;
} // namespace asc::std
```

## Constraints

- Error must be a cv-unqualified non-array object type and not an unexpected specialization; each construction, access, or swap operation must also satisfy the requirements of the prototype on this page.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::unexpected<int> failure(7);
    return failure.error() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
