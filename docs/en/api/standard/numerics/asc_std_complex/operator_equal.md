# asc::std::operator== (complex)

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

Equality compares the real part and the imaginary part; when comparing with a scalar, the scalar is treated as a complex number with a zero imaginary part. Inequality is the negation of equality.

## Function Prototype

The following declarations apply to C++17 and C++20:

```cpp
namespace asc::std {
template<class T>
constexpr bool operator==(const complex<T>& left, const complex<T>& right) noexcept;
}
```

```cpp
namespace asc::std {
template<class T>
constexpr bool operator==(const complex<T>& left, const T& right) noexcept;
}
```

The following additional declaration is provided only in C++17:

```cpp
namespace asc::std {
template<class T>
constexpr bool operator==(const T& left, const complex<T>& right) noexcept;
}
```

C++20 reversed or inequality comparison expressions are obtained through the language's operator rewriting rules; do not equate expression availability with the existence of an explicit function declaration of the same name.

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the comparison; the comparison does not modify it. |
| `right` | Input | Right operand of the comparison; the comparison does not modify it. |

`T` is the complex element type supported by this product.

## Return Value

Returns `bool`: `true` when the comparison relation holds, `false` otherwise.

## Constraints

- Complex computation currently supports `float`.
- No dynamic allocation is performed; NaN components follow the floating-point comparison rules.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/complex>

bool example()
{
    asc::std::complex<float> left(2.0f, 0.0f);
    asc::std::complex<float> right(2.0f, 0.0f);
    return (left == right) && (left == 2.0f) && (2.0f == right);
}
```

## Related Comparison Interfaces

The other type overloads formerly on the mixed page are now documented respectively in: [variant](../../utilities/asc_std_variant/operator_equal.md), [array](../../containers/asc_std_array/operator_equal.md), [string_view](../../strings/asc_std_string_view/operator_equal.md), [optional](../../utilities/asc_std_optional/operator_equal.md), [pair](../../utilities/asc_std_utility/pair_operator_equal.md), [scoped_allocator](../../memory_management/asc_std_scoped_allocator/operator_equal.md), [philox_engine](../asc_std_random/philox_engine_operator_equal.md), [uniform_real_distribution](../asc_std_random/uniform_real_distribution_operator_equal.md), [uniform_real_distribution_param_type](../asc_std_random/uniform_real_distribution_param_type_operator_equal.md).
