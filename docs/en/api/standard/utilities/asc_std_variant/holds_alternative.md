# asc::std::holds_alternative

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

`asc::std::holds_alternative` determines whether the current active alternative is the specified unique type.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

```cpp
namespace asc::std {
template<class T, class ...Types> [[nodiscard]] constexpr bool holds_alternative(const variant<Types...>& value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The alternative type to check for; it must occur exactly once in Types.... |
| `Types` | The list of alternative types of the variant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The variant object being checked; determines whether its current active alternative is T. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, `false` otherwise. |

## Constraints

- Returns `false` when the object has no active alternative.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/variant>

decltype(auto) example()
{
    asc::std::variant<int, float> value{7};
    return asc::std::holds_alternative<int>(value);
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
