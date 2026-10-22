# asc::std::llabs

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

Header: `<asc/std/cstdlib>`.

`asc::std::llabs` returns the absolute value of a signed integer of the corresponding width.

Standard semantics reference: [cppreference `cstdlib`](https://en.cppreference.com/w/cpp/header/cstdlib).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] constexpr long long llabs(long long value) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The signed integer value whose absolute value is to be taken, of type long long; the result has no valid representation when it is the minimum negative value. |

## Return Value

| Return type | Description |
| --- | --- |
| `long long` | Returns the absolute value of a signed integer of the corresponding width. |

## Constraints

- Provides integer overloads and the corresponding result types.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cstdlib>

decltype(auto) example(long long value)
{
    return asc::std::llabs(value);
}
```

## Related APIs

- [API list for this header](asc_std_cstdlib.md)
