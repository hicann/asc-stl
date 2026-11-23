# asc::absorbing_element

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

Header: `<asc/functional>`. Return the registered two-sided absorbing element as T.

## Declaration

```cpp
namespace asc {
template<class Operator, class T,
    asc::std::enable_if_t<has_absorbing_element_v<Operator, T>, int> = 0>
constexpr T absorbing_element() noexcept;
}  // namespace asc
```

## Constraints

The overload participates only when has_absorbing_element_v is true, and detection must reject false cases. An identity satisfies F(e,x)=F(x,e)=x; an absorbing element satisfies F(z,x)=F(x,z)=z. F converts every node back to T. The guarantee covers values and does not change argument evaluation or effect requirements.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>
#include <asc/std/limits>

bool example()
{
    return asc::absorbing_element<asc::maximum<int>, int>() ==
        (asc::std::numeric_limits<int>::max)();
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
