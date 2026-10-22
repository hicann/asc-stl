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

Header: `<asc/functional>`.

`asc::absorbing_element` returns the absorbing element registered for the given operator and value type; unregistered combinations must not be called.

## Function Prototype

```cpp
namespace asc {
template<class Operator, class T> constexpr T absorbing_element() noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Operator` | A registered `asc::std` standard function object type. |
| `T` | The value type matching the operator. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the absorbing element registered for the given operator and value type. |

## Constraints

- Only registered combinations of integer arithmetic, Boolean logic, or unsigned-integer bitwise operations are accepted.
- Floating-point addition is not registered.

## Example

The following snippet uses registered standard function objects and concrete integer types.

```cpp
#include <asc/functional>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

void example()
{
    static_assert(asc::absorbing_element<asc::std::multiplies<int>, int>() == 0);
}
```

## Related APIs

- [asc::has_absorbing_element_v](has_absorbing_element_v.md)
