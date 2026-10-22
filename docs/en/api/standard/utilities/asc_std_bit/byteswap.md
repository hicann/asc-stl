# asc::std::byteswap

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

`asc::std::byteswap` rearranges the object representation of an integer in reverse byte order.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Function Prototype

```cpp
namespace asc::std {
template<class Integer> [[nodiscard]] constexpr Integer byteswap(Integer value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Integer` | Integer type (signed or unsigned). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The integer value to be rearranged in reverse byte order; only the byte order of the object representation is rearranged, and the bit values are unchanged. |

## Return Value

| Return type | Description |
| --- | --- |
| `Integer` | Returns the integer value after its bytes are reversed. |

## Constraints

- Follows the standard unsigned/integer constraints.
- byteswap does not support bool, and supports standard integer widths.

## Example

The following snippet shows the call on this page with concrete values.

```cpp
#include <asc/std/bit>

decltype(auto) example()
{
    return asc::std::byteswap(0x1234u);
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
