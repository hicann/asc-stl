# asc::std::bit_ceil

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

`asc::std::bit_ceil` returns the smallest power of two not less than the input.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Function Prototype

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr T bit_ceil(T value) noexcept;
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
| `value` | Input | The unsigned integer to be rounded up to a power of two; returns the smallest power of two not less than it. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the smallest power of two not less than the input. |

## Constraints

- The power of two obtained by rounding up must be representable by `T`; inputs 0 and 1 return 1. The highest representable power of two is itself a legal input; larger values do not satisfy the premise that the result is representable.

- Follows the standard unsigned integer type constraints.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/bit>

bool example()
{
    const auto result = asc::std::bit_ceil(5u);
    return result == 8u;
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
