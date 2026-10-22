# asc::std::bit_floor

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

`asc::std::bit_floor` returns the largest power of two not greater than the input.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Function Prototype

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr T bit_floor(T value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Unsigned integer type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The unsigned integer to be rounded down to a power of two; returns the largest power of two not greater than it, and returns 0 when the input is 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the largest power of two not greater than the input. |

## Constraints

- Follows the standard unsigned integer type constraints.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/bit>

bool example()
{
    const auto result = asc::std::bit_floor(5u);
    return result == 4u;
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
