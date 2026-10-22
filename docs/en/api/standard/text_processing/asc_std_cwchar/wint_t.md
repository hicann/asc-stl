# asc::std::wint_t

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

Headers: `<asc/std/cwchar>`, `<asc/std/cwctype>`.

`asc::std::wint_t` identifies the time, character conversion, or wide character type corresponding to the current ABI.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Declaration

Host preserves the system type identity:

```cpp
namespace asc::std {
using wint_t = ::std::wint_t;
}
```

Device uses an unsigned integer representation:

```cpp
namespace asc::std {
using wint_t = unsigned int;
}
```

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Type widths, value ranges, and sentinel values are determined by the compilation target; do not assume they are the same as on another platform.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cwchar>

bool example()
{
    asc::std::wint_t value = asc::std::btowc('A');
    return value == static_cast<asc::std::wint_t>(L'A') && asc::std::wctob(value) == 'A';
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
