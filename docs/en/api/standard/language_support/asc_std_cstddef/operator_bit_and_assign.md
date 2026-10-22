# asc::std::operator&=

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

Header: `<asc/std/cstddef>`.

`asc::std::operator&=` performs the corresponding bitwise or shift operation on std::byte values.

Standard semantics reference: [cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef).

## Function Prototype

```cpp
namespace asc::std {
constexpr byte& operator&=(byte& lhs, byte rhs) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input/Output | The byte object updated by the bitwise AND; it is updated to the result of the bitwise AND with rhs, and a reference to it is returned. |
| `rhs` | Input | The right byte operand participating in the bitwise AND. |

## Return Value

| Return type | Description |
| --- | --- |
| `byte &` | Returns a reference to the updated current object, which can continue to be used in assignment or compound operations. |

## Constraints

- The standard declaration is provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cstddef>

decltype(auto) example(asc::std::byte & lhs, asc::std::byte rhs)
{
    return asc::std::operator&=(lhs, rhs);
}
```

## Related APIs

- [API list for this header](asc_std_cstddef.md)
