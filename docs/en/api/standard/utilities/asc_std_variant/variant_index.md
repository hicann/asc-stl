# asc::std::variant::index

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

Header: `<asc/std/variant>`.

`asc::std::variant::index` returns the index of the active alternative; returns `variant_npos` when there is no active alternative.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

Member of: [`asc::std::variant`](variant.md).

```cpp
// Excerpt of the declaration inside class asc::std::variant; template parameters and other members are provided by the owning class.
[[nodiscard]] constexpr size_t index() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the index of the active alternative; returns `variant_npos` when there is no active alternative. |

## Constraints

- Returns `variant_npos` when there is no active alternative, otherwise the zero-based index of the active alternative.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    return value.index() == 0 && !value.valueless_by_exception() && asc::std::get<0>(value) == 7;
}
```

## Related APIs

- [`asc::std::variant`](variant.md)
- [API list for this header](asc_std_variant.md)
