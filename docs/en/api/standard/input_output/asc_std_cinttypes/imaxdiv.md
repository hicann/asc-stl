# asc::std::imaxdiv

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

Header: `<asc/std/cinttypes>`.

`asc::std::imaxdiv` computes both the quotient and the remainder of maximum-width integers.

Standard semantics reference: [cppreference `cinttypes`](https://en.cppreference.com/w/cpp/header/cinttypes).

## Function Prototype

```cpp
namespace asc::std {
constexpr imaxdiv_t imaxdiv(intmax_t numerator, intmax_t denominator) noexcept;
}  // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `numerator` | Input | The dividend (intmax_t signed integer); the quot and rem of the return value are respectively the quotient and the remainder of dividing it by denominator. |
| `denominator` | Input | The divisor (intmax_t signed integer); when it is 0, the divide-by-zero guard replaces it with 1 for the computation, in which case quot equals numerator and rem is 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `imaxdiv_t` | Returns the structure containing the quotient and remainder of the maximum-width integers. |

## Constraints

- When the numerator is the `intmax_t` minimum value, the denominator must not be `-1`; otherwise the quotient cannot be represented. This interface does not return an overflow status for this combination.

- Provides pure integer type operations and format macros.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cinttypes>

decltype(auto) example(asc::std::intmax_t numerator, asc::std::intmax_t denominator)
{
    return asc::std::imaxdiv(numerator, denominator);
}

bool verify_example()
{
    const auto result = example(17, 5);
    return result.quot == 3 && result.rem == 2;
}
```

## Related APIs

- [API list for this header](asc_std_cinttypes.md)
