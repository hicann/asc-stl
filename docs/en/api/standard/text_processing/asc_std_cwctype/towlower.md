# asc::std::towlower

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

`asc::std::towlower` converts an uppercase letter to the corresponding lowercase letter; returns the original value when there is no corresponding conversion.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype).

## Function Prototype

```cpp
namespace asc::std {
wint_t towlower(wint_t value) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The wide character (wint_t) whose case is to be converted; the value must be representable as a wide character or equal to WEOF, and when it equals WEOF, it is returned unchanged. |

## Return Value

| Return type | Description |
| --- | --- |
| `wint_t` | Returns the wide character obtained by applying the specified character conversion rule. |

## Constraints

- The Host behavior is implemented by the system `<cwctype>` and is affected by the current C locale.
- The wide character classification and case conversion on Device use the C locale as fixed.
- Host provides the full interface, and the device side provides only the C locale related interfaces.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/cwctype>

bool example()
{
    return asc::std::towlower(L'A') == L'a';
}
```

## Related APIs

- [API list for this header](asc_std_cwctype.md)
