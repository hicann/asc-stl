# asc::std::mbstate_t

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

Header: `<asc/std/cuchar>`, `<asc/std/cwchar>`.

`asc::std::mbstate_t` holds the multibyte character conversion state; Host and the device side each use their own state representation.

The availability of this interface is Host (full interface), device side (C locale-related interfaces).

Standard semantics reference: [cppreference `cuchar`](https://en.cppreference.com/w/cpp/header/cuchar).

## Declaration

Host uses the state type from the system standard library:

```cpp
namespace asc::std {
using ::std::mbstate_t;
}
```

The device side uses the following standalone state type:

```cpp
namespace asc::std {
struct mbstate_t {
    unsigned int state = 0;
};
}
```

## Constraints

- Host uses the system multibyte conversion state type; initialize it with `{}` before the first conversion and keep the object across consecutive calls for the same character sequence.
- The device side uses stateless single-byte conversion; `mbstate_t` is retained for interface compatibility and does not indicate support for arbitrary locales or multibyte continuation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cuchar>

bool example()
{
    asc::std::mbstate_t state{};
    char16_t result{};
    auto count = asc::std::mbrtoc16(&result, "A", 1, &state);
    return count == 1 && result == u'A';
}
```

## Related APIs

- [API list for this header](asc_std_cuchar.md)
