# asc::std::expected::operator bool

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

Header: `<asc/std/expected>`.

`asc::std::expected::operator bool` processes the current object and the operand according to the operators available for `expected`.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is inside the corresponding expected or optional class.

```cpp
constexpr explicit operator bool() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the current object is in the valid or value state, and `false` otherwise. |

## Constraints

- Supports all cv/ref-qualified forms.
- Callable objects and result construction on the device side must not throw exceptions.

## Example

The following Host snippet demonstrates the call with concrete types; confirm the object is in the value state before accessing the value.

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(7);
    const bool present = static_cast<bool>(value);
    return present;
}

bool verify_example()
{
    return example() == true;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
