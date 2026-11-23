# asc::always_false

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

Header: `<asc/functional>`. Accept zero or more arguments and return false.

## Declaration

```cpp
namespace asc {
struct always_false;
}  // namespace asc
```

## Constraints

The object is stateless and its call is unconditionally noexcept. The body does not read, copy, or retain arguments. Caller argument expressions are still evaluated and can have effects or throw.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>

bool example()
{
    int evaluations = 0;
    const bool result = asc::always_false{}(++evaluations);
    return !result && evaluations == 1;
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
