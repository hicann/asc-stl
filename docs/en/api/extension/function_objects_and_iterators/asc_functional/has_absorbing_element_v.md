# asc::has_absorbing_element_v

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

Header: `<asc/functional>`. Whether the operation/value-type pair has a registered two-sided absorbing element.

## Declaration

```cpp
namespace asc {
template<class Operator, class T>
inline constexpr bool has_absorbing_element_v = /* library registration */;
}  // namespace asc
```

## Constraints

Operator and T are exact unqualified non-reference types. Invoke on const T lvalues and convert every binary node back to T; equivalence is built-in value equality over the full T domain. Associativity and commutativity are registered separately. false means no guarantee, including all unregistered pairs. See the header overview for the complete table.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>

bool example()
{
    static_assert(asc::has_absorbing_element_v<asc::minimum<unsigned>, unsigned>);
    static_assert(!asc::has_absorbing_element_v<asc::std::plus<int>, int>);
    return true;
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
