# asc::std::numeric_limits

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

Header: `<asc/std/limits>`.

`asc::std::numeric_limits` provides the representable range, precision, and numeric properties of types.

Standard semantics reference: [cppreference `limits`](https://en.cppreference.com/w/cpp/header/limits).

## Declaration

```cpp
namespace asc::std {
template<class T> class numeric_limits;
} // namespace asc::std
```

## Constraints

- Supports all standard arithmetic types and their cv-qualified forms.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/limits>

bool example()
{
    static_assert(asc::std::numeric_limits<int>::is_integer);
    static_assert(asc::std::numeric_limits<int>::min() < 0);
    static_assert(asc::std::numeric_limits<unsigned>::min() == 0);
    return asc::std::numeric_limits<int>::max() > 0;
}
```

## Related APIs

- [API list for this header](asc_std_limits.md)
