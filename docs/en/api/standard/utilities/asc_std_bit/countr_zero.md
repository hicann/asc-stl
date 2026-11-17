# asc::std::countr_zero

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

Header: `<asc/std/bit>`.

`asc::std::countr_zero` counts the number of consecutive zero bits starting from the least significant bit.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Function Prototype

The following is the template declaration constrained by the unsigned integer selection condition; the result-selection alias only controls which legal types participate.

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr __unsigned_integer_result_t<T, int> countr_zero(T value) noexcept;
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Supported cv-unqualified unsigned integer type; bool and ordinary character encoding types are not accepted. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The unsigned integer being queried; returns the number of binary digits of `T` when it is 0. |

## Return Value

| Type | Meaning |
| --- | --- |
| `int` | Number of consecutive zero bits starting from the least significant bit; the number of bits in T when the input is 0. |

## Constraints

- The standard unsigned integer type requirements apply. When using the result as a sparse-mask bit index, first check that the input is nonzero: the result for zero is the bit width, not a valid index.

## Example

The following snippet shows the call on this page with concrete values.

```cpp
#include <asc/std/bit>

bool example()
{
    unsigned long long mask = (1ULL << 31) | (1ULL << 63);
    unsigned positions[2] = {};
    unsigned count = 0;
    while (mask != 0) {
        positions[count++] = asc::std::countr_zero(mask);
        mask &= mask - 1;
    }
    return count == 2 && positions[0] == 31 && positions[1] == 63;
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
