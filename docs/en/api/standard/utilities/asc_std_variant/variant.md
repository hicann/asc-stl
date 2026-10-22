# asc::std::variant

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

`asc::std::variant` holds one active value from multiple alternative types.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Declaration

```cpp
namespace asc::std {
template<class ...Types> class variant;
} // namespace asc::std
```

## Constraints

- On the Host, when switching alternatives or calling `emplace`, the old value is destroyed first; if the construction of the new alternative throws, the object has no active alternative, `index()` is `variant_npos`, and `valueless_by_exception()` is `true`. The object can still be safely destroyed and recovered through a successful `emplace` or assignment.
- When an assignment to the same active alternative throws, the active index stays unchanged and the state of the value is determined by that alternative type's assignment operation.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    const bool integer = value.index() == 0 && *asc::std::get_if<0>(&value) == 7;
    value.emplace<1>(2.0F);
    return integer && value.index() == 1 && *asc::std::get_if<1>(&value) == 2.0F;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
