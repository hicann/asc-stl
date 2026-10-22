# asc::std::wctype_t

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

`asc::std::wctype_t` identifies the time, character conversion, or wide character type corresponding to the current ABI.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype).

## Declaration

Host preserves the system type identity:

```cpp
namespace asc::std {
using wctype_t = ::std::wctype_t;
}
```

Device uses an unsigned integer representation:

```cpp
namespace asc::std {
using wctype_t = unsigned int;
}
```

## Constraints

- The Host behavior is implemented by the system `<cwctype>` and is affected by the current C locale.
- The wide character classification and case conversion on Device use the C locale as fixed.
- Host provides the full interface, and the device side provides only the C locale related interfaces.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cwctype>

bool example()
{
    asc::std::wctype_t category = asc::std::wctype("digit");
    return asc::std::iswctype(L'7', category) != 0 && asc::std::iswctype(L'A', category) == 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwctype.md)
