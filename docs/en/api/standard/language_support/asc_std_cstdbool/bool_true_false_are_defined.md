# __bool_true_false_are_defined

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

Header: `<asc/std/cstdbool>`.

`__bool_true_false_are_defined` provides a C-compatible feature macro with the value 1 in C++17 mode, used to check the C++-compatible definition of the boolean type.

## Declaration

```cpp
#define __bool_true_false_are_defined 1
```

## Constraints

- This library supplements this macro only in C++17 mode; in C++20 and later modes the header can still be included, but this library does not add the macro there.
- If a preceding system header already defines this macro, this library keeps that definition and does not deliberately redefine or remove it.

## Example

The following snippet applies to C++17.

```cpp
#include <asc/std/cstdbool>

static_assert(__bool_true_false_are_defined == 1);
```

## Related APIs

- [API list for this header](asc_std_cstdbool.md)
