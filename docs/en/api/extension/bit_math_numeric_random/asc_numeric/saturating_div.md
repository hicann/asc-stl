# asc::saturating_div

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

Header: `<asc/numeric>`.

`asc::saturating_div` performs saturating division and handles the unrepresentable case of the minimum value divided by negative one.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr T saturating_div(T left, T right) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Standard integer type participating in the saturating division (not bool, no more than 64 bits). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left integer operand of the saturating division. |
| `right` | Input | Right integer operand of the saturating division. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the integer result clamped to the boundaries of the target type. |

## Constraints

- When the divisor is 0, the maximum value of `T` is returned; a signed minimum value divided by `-1` is likewise clamped to the maximum value. This is the explicit policy of this saturating interface.

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `T` must be a standard non-bool integer of no more than 64 bits; arithmetic is handled according to the corresponding checked or saturating rules.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::saturating_div(8, 2);
}

bool verify_example()
{
    return example() == 4;
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
