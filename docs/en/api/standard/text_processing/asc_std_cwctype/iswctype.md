# asc::std::iswctype

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

Header: `<asc/std/cwctype>`.

`asc::std::iswctype` classifies the input character according to the currently supported C locale rules.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype).

## Function Prototype

```cpp
namespace asc::std {
int iswctype(wint_t value, wctype_t descriptor) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The wide character (wint_t) to classify; the value must be representable as a wide character or equal to WEOF, and when it equals WEOF, the result is 0. |
| `descriptor` | Input | The character classification descriptor (wctype_t), obtained from wctype; it specifies the classification category participating in the test (such as letter, digit, or whitespace). |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | Returns a non-zero value when the character satisfies the classification indicated by the interface name, and returns zero otherwise. |

## Constraints

- The descriptor must come from a non-zero descriptor successfully returned by wctype under the same locale; obtain the descriptor again after a locale change. The 0 returned for an unknown name must not be treated as a valid descriptor.

- The Host behavior is implemented by the system `<cwctype>` and is affected by the current C locale.
- The wide character classification and case conversion on Device use the C locale as fixed.
- Host provides the full interface, and the device side provides only the C locale related interfaces.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/cwctype>

bool example()
{
    const auto descriptor = asc::std::wctype("alpha");
    return descriptor != 0 && asc::std::iswctype(L'A', descriptor) != 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwctype.md)
