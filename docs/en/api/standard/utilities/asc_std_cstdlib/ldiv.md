# asc::std::ldiv

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

Header: `<asc/std/cstdlib>`.

`asc::std::ldiv` computes both the integer quotient and remainder and returns the corresponding result structure.

Standard semantics reference: [cppreference `cstdlib`](https://en.cppreference.com/w/cpp/header/cstdlib).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] constexpr ldiv_t ldiv(long numerator, long denominator) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `numerator` | Input | The dividend (numerator), of type long. |
| `denominator` | Input | The divisor (denominator), of type long; must not be 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `ldiv_t` | Returns the corresponding result structure. |

## Constraints

- The divisor must be non-zero, and the quotient must be representable by the returned integer type; the signed minimum value divided by -1 does not satisfy this premise and cannot be used as a normal input.

- Provides integer overloads and the corresponding result types.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cstdlib>

decltype(auto) example(long numerator, long denominator)
{
    return asc::std::ldiv(numerator, denominator);
}

bool verify_example()
{
    const auto result = example(17, 5);
    return result.quot == 3 && result.rem == 2;
}
```

## Related APIs

- [API list for this header](asc_std_cstdlib.md)
