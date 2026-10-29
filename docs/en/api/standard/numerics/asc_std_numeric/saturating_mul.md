# asc::std::saturating_mul

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

Header: `<asc/std/numeric>`.

`asc::std::saturating_mul` computes the product of two integers of the same type and returns the corresponding boundary value when the result is outside the representable range of `T`.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

```cpp
namespace asc::std {
template<class T> constexpr T saturating_mul(T left, T right) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The integer type participating in the saturating multiplication. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left integer operand of the saturating multiplication. |
| `right` | Input | The right integer operand of the saturating multiplication. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | The integer result clamped to the boundaries of the target type. |

## Constraints

- The standard integer types `signed char`, `unsigned char`, `short`, `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `long long`, and `unsigned long long` can be used; `bool`, plain `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t`, and floating-point types are not accepted.
- When template arguments are not explicitly specified, the two inputs must deduce the same `T`; the integral promotion usually applied in arithmetic operations is not performed.
- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; the interface is `constexpr` and does not throw.

## Example

The following example computes 8 times 2 and returns 16.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::saturating_mul(8, 2);
}

bool verify_example()
{
    return example() == 16;
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
