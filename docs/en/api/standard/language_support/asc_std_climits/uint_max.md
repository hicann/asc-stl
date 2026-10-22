# UINT_MAX

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

Header: `<asc/std/climits>`.

`UINT_MAX` gives the limit value of the integer type or size corresponding to `UINT`.

Standard semantics reference: [cppreference `climits`](https://en.cppreference.com/w/cpp/header/climits).

## Declaration

This macro is provided by the platform header; the public header keeps its spelling and value and does not invent a substitute macro name.

```cpp
#include <asc/std/climits>
```

## Constraints

- Only macros actually supported by the compiler ABI are provided.

## Example

The following Host example uses concrete inputs and checks an observable result of the interface.

```cpp
#include <asc/std/climits>

static_assert(UINT_MAX >= 65535U);
```

## Related APIs

- [API list for this header](asc_std_climits.md)
