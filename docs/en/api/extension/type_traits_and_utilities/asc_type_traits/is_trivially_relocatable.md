# asc::is_trivially_relocatable

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

`asc::is_trivially_relocatable<T>` determines whether an object can be relocated by copying it byte by byte to a new address and ending the lifetime of the source object; trivially copyable types satisfy this condition by default.

## Declaration

```cpp
namespace asc {
template<class T> struct is_trivially_relocatable;
} // namespace asc
```

## Constraints

- This interface is a single-type customization point.
- User specializations must satisfy the semantic preconditions declared on this page.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/type_traits>

bool example()
{
    static_assert(asc::is_trivially_relocatable<int>::value);
    return true;
}
```

## Related APIs

- [API list for this header](asc_type_traits.md)
