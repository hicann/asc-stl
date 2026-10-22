# asc::std::alignment_of

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

`asc::std::alignment_of` obtains the alignment requirement of a type at compile time.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T> struct alignment_of;
} // namespace asc::std
```

## Constraints

- `T` must make `alignof(T)` valid, for example a complete object type, a reference to a valid object type, or an array whose element type is complete. `void`, functions, and incomplete classes must not be used.
- The result is in bytes and represents the alignment requirement of an object of the type; the query allocates no memory.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // Both ::value and _v return the alignof result
    static_assert(asc::std::alignment_of<int>::value == alignof(int));
    static_assert(asc::std::alignment_of_v<double> == alignof(double));
    static_assert(asc::std::alignment_of<char>::value == 1); // the alignment of char is always 1
    // Counterexample: char and int have different alignment values
    static_assert(asc::std::alignment_of_v<char> != asc::std::alignment_of_v<int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
