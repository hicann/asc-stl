# asc::is_trivially_relocatable_v

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

`<asc/type_traits>`

`asc::is_trivially_relocatable_v<T>` is exactly `asc::is_trivially_relocatable<T>::value`.

## Declaration

```cpp
namespace asc {
template<class T> inline constexpr bool is_trivially_relocatable_v = is_trivially_relocatable<T>::value;
} // namespace asc
```

## Constraints

C++17 minimum and C++20 are supported. Completeness, cv/ref, specialization and frontend requirements are specified in the [header contract](asc_type_traits.md).

## Example

```cpp
#include <asc/type_traits>

bool example()
{
    struct Value { int value; };
    static_assert(asc::is_trivially_relocatable_v<int>);
    static_assert(!asc::is_trivially_relocatable_v<const int>);
    static_assert(!asc::is_trivially_relocatable_v<Value>);
    return true;
}
```

## Related APIs

- [asc/type_traits](asc_type_traits.md)
