# asc::std::lldiv_t::quot

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

Header: `<asc/std/cstdlib>`.

`asc::std::lldiv_t::quot` stores the quotient of the integer division result.

Standard semantics reference: [cppreference `cstdlib`](https://en.cppreference.com/w/cpp/header/cstdlib).

## Declaration

Member of: [`asc::std::lldiv_t`](lldiv_t.md).

```cpp
// Excerpt of the declaration inside class asc::std::lldiv_t; template parameters and other members are provided by the owning class.
long long quot;
```

## Constraints

- Provides integer overloads and the corresponding result types.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cstdlib>

bool example()
{
    asc::std::lldiv_t result = asc::std::lldiv(17, 5);
    return result.quot == 3 && result.rem == 2;
}
```

## Related APIs

- [`asc::std::lldiv_t`](lldiv_t.md)
- [API list for this header](asc_std_cstdlib.md)
