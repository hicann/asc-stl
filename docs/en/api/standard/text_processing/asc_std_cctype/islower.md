# asc::std::islower

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

Header: `<asc/std/cctype>`.

`asc::std::islower` determines whether the input is a lowercase letter; it returns a non-zero value when the condition is satisfied and 0 otherwise.

Standard semantics reference: [cppreference `cctype`](https://en.cppreference.com/w/cpp/header/cctype).

## Function Prototype

```cpp
namespace asc::std {
int islower(int value) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The character value to classify; it must be representable as an unsigned char or equal to EOF, otherwise the behavior is undefined. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | Returns a non-zero value if the character satisfies the classification indicated by the interface name, and zero otherwise. |

## Constraints

- The input must be `EOF` or a value representable by `unsigned char`; other negative values do not satisfy the precondition.
- Host delegates to the current system C locale.
- The device-side execution environment uses a fixed C locale.
- The valid input domain is EOF and all 256 unsigned char values.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/cctype>

bool example()
{
    return asc::std::islower('a') != 0;
}
```

## Related APIs

- [API list for this header](asc_std_cctype.md)
