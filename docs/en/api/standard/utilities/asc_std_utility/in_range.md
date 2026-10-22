# asc::std::in_range

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

Header: `<asc/std/utility>`.

`asc::std::in_range` determines whether an integer value can be represented by the given target integer type.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
template<class T, class U> constexpr bool in_range(U value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target integer type; determines whether the value of value can be represented by this type. |
| `U` | The integer type of the value being checked; it must be a standard signed or unsigned integer type (excluding bool, char, and other character encoding types). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The integer value whose representability is checked. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, `false` otherwise. |

## Constraints

- The type domain includes signed char, unsigned char, and the standard signed/unsigned integer types; bool, char, wchar_t, char8_t, char16_t, and char32_t are excluded.

- Follows the standard integer constraints.

## Example

The following snippet demonstrates the call on this page with concrete values.

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    return asc::std::in_range<unsigned int>(3);
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
