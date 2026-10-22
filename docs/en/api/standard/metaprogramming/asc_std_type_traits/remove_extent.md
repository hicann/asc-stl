# asc::std::remove_extent

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

Header: `<asc/std/type_traits>`.

`asc::std::remove_extent` yields the type obtained by removing the qualification, reference, or extent indicated by the name.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T>
struct remove_extent;
} // namespace asc::std
```

## Constraints

- Removes only one outermost array dimension; non-array types keep the original type, and inner dimensions and element qualification are preserved.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // Positive example: remove_extent removes only the outermost array dimension
    static_assert(asc::std::is_same_v<asc::std::remove_extent_t<int[2][3]>, int[3]>);
    static_assert(asc::std::is_same_v<typename asc::std::remove_extent<const char[4]>::type, const char>);
    // Counterexample: remove_extent_t<int[2][3]> is not int
    static_assert(!asc::std::is_same_v<asc::std::remove_extent_t<int[2][3]>, int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
