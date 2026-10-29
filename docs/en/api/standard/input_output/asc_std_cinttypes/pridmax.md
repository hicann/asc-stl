# PRIdMAX

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

Header: `<asc/std/cinttypes>`.

`PRIdMAX` provides the printf format conversion specifier for the maximum-width signed integer (intmax_t); this product uses the LP64 data model, where intmax_t is long.

Standard semantics reference: [cppreference `cinttypes`](https://en.cppreference.com/w/cpp/header/cinttypes).

## Declaration

```cpp
#define PRIdMAX "ld"
```

## Constraints

- Provides pure integer type operations and format macros.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <cstdio>
#include <asc/std/cinttypes>

#ifndef PRIdMAX
#error "PRIdMAX is required by this public Header"
#endif

bool verify_example()
{
    char text[32] = {};
    const int count = ::std::snprintf(text, sizeof(text), "%" PRIdMAX, static_cast<asc::std::intmax_t>(123));
    return count == 3 && text[0] == '1' && text[1] == '2' && text[2] == '3' && text[3] == 0;
}
```

## Related APIs

- [API list for this header](asc_std_cinttypes.md)
