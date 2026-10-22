# asc::std::greater_equal::is_transparent

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

Header: `<asc/std/functional>`.

`asc::std::greater_equal::is_transparent` marks that the function object supports transparent calls with heterogeneous argument types.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

Member of: [`asc::std::greater_equal`](greater_equal.md).

```cpp
// Excerpt of the declaration inside asc::std::greater_equal; the template parameters and other members are provided by the enclosing class.
using is_transparent = void;
```

## Constraints

- Both the typed form and the transparent call form are provided.

## Example

The following Host example checks the alias or tag result with concrete types and an independent expectation.

```cpp
#include <asc/std/functional>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = typename asc::std::greater_equal<void>::is_transparent;
    static_assert(asc::std::is_same_v<alias_type, void>);
}
```

## Related APIs

- [`asc::std::greater_equal`](greater_equal.md)
- [API list for this header](asc_std_functional.md)
