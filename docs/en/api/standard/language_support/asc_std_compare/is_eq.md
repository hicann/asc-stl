# asc::std::is_eq

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

Header: `<asc/std/compare>`.

`asc::std::is_eq` determines whether a comparison category result satisfies the relation specified by the name.

Standard semantics reference: [cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare).

## Function Prototype

```cpp
namespace asc::std {
constexpr bool is_eq(partial_ordering value) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The comparison category value (partial_ordering) to test; determines whether it represents the "equal" relation. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- ASC comparison category constants, comparison with zero, and standard category conversions are supported.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/compare>

decltype(auto) example(asc::std::partial_ordering value)
{
    return asc::std::is_eq(value);
}
```

## Related APIs

- [API list for this header](asc_std_compare.md)
