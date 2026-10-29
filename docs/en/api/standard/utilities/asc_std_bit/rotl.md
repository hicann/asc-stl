# asc::std::rotl

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

`asc::std::rotl` rotates an unsigned value left by its bit width.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Function Prototype

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr T rotl(const T value, const int count) noexcept;
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
| `value` | Input | The unsigned integer value to be rotated left; the shifted-out high bits wrap around into the low bits. |
| `count` | Input | The number of bits to rotate left; it takes effect modulo the bit width of `T` and may be a value not less than the bit width. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the unsigned integer value after the rotation by the bit width. |

## Constraints

- Follows the standard unsigned integer type constraints.

## Example

The following snippet shows the call on this page with concrete values.

```cpp
#include <asc/std/bit>

decltype(auto) example()
{
    return asc::std::rotl(1u, 2);
}

bool verify_example()
{
    return example() == 4u;
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
