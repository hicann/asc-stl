# asc::std::expected

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

`asc::std::expected` holds one active state between a success value and an error value.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Declaration

```cpp
namespace asc::std {
template<class Value, class Error> class expected;
} // namespace asc::std
```

## Constraints

- T must be a non-void type, and E must be an object type.
- The applicable operations must not throw exceptions.
- Provides construction, assignment, emplace, and swap.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> value(7);
    asc::std::expected<int, int> failure(asc::std::unexpect, 3);
    return value.has_value() && *value == 7 && !failure.has_value() && failure.error() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
