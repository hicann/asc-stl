# asc::std::imaxabs

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

Header: `<asc/std/cinttypes>`.

`asc::std::imaxabs` returns the absolute value of a signed integer of the corresponding width.

Standard semantics reference: [cppreference `cinttypes`](https://en.cppreference.com/w/cpp/header/cinttypes).

## Function Prototype

```cpp
namespace asc::std {
constexpr intmax_t imaxabs(intmax_t value) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The intmax_t signed integer whose absolute value is to be taken; when it is the minimum negative value INTMAX_MIN, its absolute value cannot be represented as intmax_t. |

## Return Value

| Return type | Description |
| --- | --- |
| `intmax_t` | Returns the absolute value of a signed integer of the corresponding width. |

## Constraints

- Provides pure integer type operations and format macros.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cinttypes>

decltype(auto) example(asc::std::intmax_t value)
{
    return asc::std::imaxabs(value);
}

bool verify_example()
{
    return example(-7) == 7;
}
```

## Related APIs

- [API list for this header](asc_std_cinttypes.md)
