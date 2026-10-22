# asc::is_extended_floating_point_v

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

Header: `<asc/type_traits>`.

`asc::is_extended_floating_point_v<T>` is a bool variable template shorthand for `is_extended_floating_point<T>::value`.

## Declaration

```cpp
namespace asc {
template<class T> inline constexpr bool is_extended_floating_point_v = asc::is_extended_floating_point<T>::value;
} // namespace asc
```

## Constraints

- The result is an exact bool projection of the corresponding customization point's value.

## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/type_traits>

inline constexpr auto example = asc::is_extended_floating_point_v<float>;
```

## Related APIs

- [API list for this header](asc_type_traits.md)
