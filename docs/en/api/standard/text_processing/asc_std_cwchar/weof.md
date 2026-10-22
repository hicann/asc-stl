# WEOF

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

`WEOF` denotes the end-of-input or error state of wide character input and output.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Declaration

The Host definition comes from the system standard library and its exact expansion is implementation-dependent; do not rely on its exact macro text. The following is only the fallback adopted on Device when it is not predefined.

```cpp
#define WEOF (static_cast<asc::std::wint_t>(-1))
```

This prototype corresponds to the headers: `<asc/std/cwchar>`, `<asc/std/cwctype>`.

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Type widths, value ranges, and sentinel values are determined by the compilation target; do not assume they are the same as on another platform.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

#ifndef WEOF
#error "WEOF is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
