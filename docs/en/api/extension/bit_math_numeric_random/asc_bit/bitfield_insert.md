# asc::bitfield_insert

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

Header: `<asc/bit>`.

`asc::bitfield_insert` replaces the bit field starting at bit `start` of `destination` with the low `width` bits of `source`, keeping the remaining bits of the destination value.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr T bitfield_insert(T destination, T source, int start, int width) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Unsigned integer type; must be uint32_t or uint64_t. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Input | Target integer value containing the bit field to be replaced; passed by value, the replacement result is returned, with no storage lifetime involved. |
| `source` | Input | Source integer value supplying the replacement bits for the bit field; passed by value, with no storage lifetime involved. |
| `start` | Input | Bit index of the start of the bit field to be replaced within `destination` (the lowest bit is bit 0); must not be negative. |
| `width` | Input | Number of bits in the bit field to be replaced; must not be negative. |
## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the integer value after the specified bit field is replaced. |

## Constraints

- T must be uint32_t or uint64_t.
- `start` and `width` must be non-negative, with `start <= bit width` and `width <= bit width - start`; zero width and full width are handled under this window constraint.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bitfield_insert(0u, 3u, 1, 2);
}

bool verify_example()
{
    return example() == 6u;
}
```

## Related APIs

- [API list for this header](asc_bit.md)
