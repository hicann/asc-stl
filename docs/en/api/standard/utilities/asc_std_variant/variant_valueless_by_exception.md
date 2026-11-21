# asc::std::variant::valueless_by_exception

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

`asc::std::variant::valueless_by_exception` determines whether the variant currently has no active alternative.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

Member of: [`asc::std::variant`](variant.md).

```cpp
// Excerpt of the declaration inside class asc::std::variant; template parameters and other members are provided by the owning class.
[[nodiscard]] constexpr bool valueless_by_exception() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when there is no active alternative, `false` otherwise. |

## Constraints

- On Host, a failure after the old alternative has been destroyed leaves `index() == variant_npos` and `get_if` returns a null pointer. When copy assignment prepares the new value before destroying the old one, a failed copy preserves the old index.
- An object with no active alternative can be destroyed and recovered through a successful construction or assignment; the presence of the corresponding active value must be confirmed before reading the value or calling `visit`.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example deliberately triggers a construction exception, checks the valueless state, and recovers to the integer alternative.

```cpp
#include <asc/std/variant>

struct construction_failure {};

struct throwing_value {
    explicit throwing_value(int)
    {
        throw construction_failure{};
    }
};

bool example()
{
    asc::std::variant<int, throwing_value> value(7);
    try {
        value.emplace<1>(3);
        return false;
    } catch (const construction_failure&) {
        const bool empty = value.valueless_by_exception() &&
            value.index() == asc::std::variant_npos && asc::std::get_if<0>(&value) == nullptr;
        value.emplace<0>(11);
        return empty && !value.valueless_by_exception() && asc::std::get<0>(value) == 11;
    }
}
```

## Related APIs

- [`asc::std::variant`](variant.md)
- [API list for this header](asc_std_variant.md)
