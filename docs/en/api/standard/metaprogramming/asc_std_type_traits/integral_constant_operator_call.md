# asc::std::integral_constant::`operator()`

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

Header: `<asc/std/type_traits>`.

`asc::std::integral_constant::operator()` returns the compile-time constant held by this specialization by value.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Function Prototype

Member of: [`asc::std::integral_constant`](integral_constant.md).

```cpp
// Excerpt of the declaration inside asc::std::integral_constant; template parameters and other members are provided by the owning class.
constexpr value_type operator()() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `value_type` | Returns the value held by this compile-time constant wrapper. |

## Constraints

- The call takes no parameters, does not modify the object, and returns the template argument `V` by value as `value_type`; it can be used in constant expressions.

## Example

The following Host snippet checks the invocation result of the constant wrapper against an independent expected value.

```cpp
#include <asc/std/type_traits>

constexpr auto example()
{
    return asc::std::integral_constant<int, 3>{}();
}
static_assert(example() == 3);
```

## Related APIs

- [`asc::std::integral_constant`](integral_constant.md)
- [API list for this header](asc_std_type_traits.md)
