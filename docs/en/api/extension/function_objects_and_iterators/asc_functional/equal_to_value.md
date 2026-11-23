# asc::equal_to_value

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

Header: `<asc/functional>`. Own a value used as the target of equality comparisons.

## Declaration

```cpp
namespace asc {
template<class T> class equal_to_value;
}  // namespace asc
```

## Constraints

T is a complete, destructible, unqualified non-array object type, excluding references. Copy/move support and exception specifications follow T. Stored pointers, views, and reference_wrapper objects keep their borrowing semantics. Character arrays deduce a pointer type and use pointer equality.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>

bool example()
{
    auto equal = asc::equal_to_value{7};
    return equal(7L) && !equal(8);
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
