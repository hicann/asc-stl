# asc::std::lcm

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

`asc::std::lcm` computes the least common multiple of two integers.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

```cpp
namespace asc::std {
template<class T, class U> constexpr common_type_t<T, U> lcm(T left, U right);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The integer type of the left operand; excludes bool. |
| `U` | The integer type of the right operand; excludes bool. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left integer operand for computing the least common multiple. |
| `right` | Input | The right integer operand for computing the least common multiple. |

## Return Value

| Return type | Description |
| --- | --- |
| `common_type_t<T, U>` | The computed least common multiple of the two integers. |

## Constraints

- The template parameters `T` and `U` must be integer types and not `bool`; otherwise a compile-time assertion is triggered.
- The absolute values of both parameters and the least common multiple result must all be representable by the common result type `common_type_t<T, U>`; when this precondition is violated, the result is not guaranteed.

## Example

The following example computes the least common multiple of 12 and 18 and returns 36.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::lcm(12, 18);
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
