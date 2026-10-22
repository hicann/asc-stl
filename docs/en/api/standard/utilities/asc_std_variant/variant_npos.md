# asc::std::variant_npos

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

Header: `<asc/std/variant>`.

`asc::std::variant_npos` is the index value indicating that there is no active alternative.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Declaration

```cpp
namespace asc::std {
inline constexpr size_t variant_npos = static_cast<size_t>(-1);
}
```

## Constraints

- `index()` returns this sentinel value when the object has no active alternative, for example after the construction of a new alternative throws while switching alternatives on the Host.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example demonstrates this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/variant>

bool example()
{
    static_assert(asc::std::variant_npos == static_cast<asc::std::size_t>(-1));
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
