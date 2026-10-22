# asc::std::wctrans

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

`asc::std::wctrans` obtains or applies wide character classification and conversion descriptors according to the currently supported C locale rules.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype).

## Function Prototype

```cpp
namespace asc::std {
wctrans_t wctrans(const char* property) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `property` | Input | The narrow character property name terminated by a zero character, for example tolower or toupper. The returned descriptor is used by the corresponding wide character classification or conversion function. |

## Return Value

| Return type | Description |
| --- | --- |
| `wctrans_t` | Returns the corresponding descriptor when the name is supported by the current locale; returns 0 for an unknown name. |

## Constraints

- property must point to a valid name terminated by a zero character. On Device, the conversion names are only tolower and toupper.

- The Host behavior is implemented by the system `<cwctype>` and is affected by the current C locale.
- The wide character classification and case conversion on Device use the C locale as fixed.
- Host provides the full interface, and the device side provides only the C locale related interfaces.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/cwctype>

bool example()
{
    const auto descriptor = asc::std::wctrans("tolower");
    return descriptor != 0 && asc::std::towctrans(L'A', descriptor) == L'a';
}
```

## Related APIs

- [API list for this header](asc_std_cwctype.md)
