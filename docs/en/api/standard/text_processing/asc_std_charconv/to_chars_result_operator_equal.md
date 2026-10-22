# asc::std::to_chars_result::`operator==`

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

Header: `<asc/std/charconv>`.

`asc::std::to_chars_result::operator==` compares two conversion results member by member: true when both the pointer and the error code are equal.

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Function Prototype

Member of: [`asc::std::to_chars_result`](to_chars_result.md).

```cpp
// Excerpt of the declaration inside the asc::std::to_chars_result class; template parameters and other members are provided by the enclosing class.
friend constexpr bool operator==(const to_chars_result&, const to_chars_result&) noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| Left operand | Input | The conversion result being compared; the comparison does not modify it. |
| Right operand | Input | The conversion result being compared; the comparison does not modify it. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | true when the corresponding equality/ordering comparison expression holds, and false otherwise. |

## Constraints

- Compares the two members, pointer and error code; this is a non-member friend defined inside the class, found via ADL, and is not called in the object.operator form.

## Example

The following Host example provides concrete inputs and checks the result while the object and the underlying storage remain valid.

```cpp
#include <asc/std/charconv>

bool example()
{
    char output[2]{};
    asc::std::to_chars_result left{output, asc::std::errc{}};
    asc::std::to_chars_result right{output, asc::std::errc{}};
    return left == right;
}
```

## Related APIs

- [`asc::std::to_chars_result`](to_chars_result.md)
- [API list for this header](asc_std_charconv.md)
