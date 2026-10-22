# asc::std::nullptr_t

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

Header: `<asc/std/cstddef>`.

`asc::std::nullptr_t` identifies the size, pointer difference, null pointer, or maximum alignment type corresponding to the current C++ ABI.

Standard semantics reference: [cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef).

## Declaration

```cpp
namespace asc::std {
using nullptr_t = decltype(nullptr);
} // namespace asc::std
```

## Constraints

- The standard declaration is provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cstddef>

bool example()
{
    asc::std::nullptr_t empty = nullptr;
    int* pointer = empty;
    return pointer == nullptr;
}
```

## Related APIs

- [API list for this header](asc_std_cstddef.md)
