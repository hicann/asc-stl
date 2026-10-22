# asc::std::saturating_cast

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

`asc::std::saturating_cast` converts an integer to the target integer type; when the value is outside the representable range of the target type, it returns the corresponding minimum or maximum value.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

```cpp
namespace asc::std {
template<class U, class T> constexpr U saturating_cast(T value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The target integer type of the conversion. |
| `T` | The source integer type of the value to convert. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The integer value to convert; when the result is outside the representable range of the target type U, it is clamped to the boundaries of U. |

## Return Value

| Return type | Description |
| --- | --- |
| `U` | The integer result clamped to the boundaries of the target type. |

## Constraints

- The standard integer types `signed char`, `unsigned char`, `short`, `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `long long`, and `unsigned long long` can be used; `bool`, plain `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t`, and floating-point types are not accepted.
- Both the source type and the target type must satisfy the integer type requirements above; the conversion preserves the original value within the range of the target type.
- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; the interface is `constexpr` and does not throw.

## Example

The following example converts 300 to `unsigned char`; the maximum value of that type on the current target is 255, and the result saturates to 255.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::saturating_cast<unsigned char>(300);
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
