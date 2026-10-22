# asc::std::uintmax_t

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

Headers: `<asc/std/cinttypes>`, `<asc/std/cstdint>`.

`asc::std::uintmax_t` designates the maximum-width integer type supported by the current ABI.

Standard semantics reference: [cppreference `cinttypes`](https://en.cppreference.com/w/cpp/header/cinttypes).

## Declaration

It brings in the same-named integer type provided by the system `<stdint.h>`; the width is guaranteed by the definition of that type.

```cpp
namespace asc::std {
using uintmax_t = __UINTMAX_TYPE__;
}
```

## Constraints

- Only types and macros that actually exist in the Ascend 950 and Host ABIs are provided.
- Provides pure integer type operations and format macros.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cinttypes>
#include <asc/std/type_traits>

bool example()
{
    using Integer = asc::std::uintmax_t;
    static_assert(asc::std::is_integral_v<Integer>);
    static_assert(asc::std::is_signed_v<Integer> == false);
    Integer left = 2;
    Integer right = 3;
    return left + right == 5;
}
```

## Related APIs

- [API list for this header](asc_std_cinttypes.md)
