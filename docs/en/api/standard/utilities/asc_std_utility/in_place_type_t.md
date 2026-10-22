# asc::std::in_place_type_t

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

Header: `<asc/std/utility>`.

`asc::std::in_place_type_t` marks in-place construction of an object by alternative type.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Declaration

```cpp
namespace asc::std {
template<class T> struct in_place_type_t;
} // namespace asc::std
```

## Constraints

- Provides the complete standard form.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/utility>
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(asc::std::in_place_type_t<int>{}, 7);
    return value.index() == 0 && *asc::std::get_if<int>(&value) == 7;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
