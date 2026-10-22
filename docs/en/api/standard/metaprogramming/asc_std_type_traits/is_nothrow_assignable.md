# asc::std::is_nothrow_assignable

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

`asc::std::is_nothrow_assignable` determines at compile time whether assignment with the given arguments is possible and does not throw.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T, class Arg> struct is_nothrow_assignable;
} // namespace asc::std
```

## Constraints

- Provides the trait class and the _v helper form.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    struct throws {
        throws& operator=(const throws&) { throw 0; }
    };
    // Positive example: assigning an int to an int lvalue does not throw
    static_assert(asc::std::is_nothrow_assignable<int&, int>::value);
    static_assert(asc::std::is_nothrow_assignable_v<int&, int>);
    // Counterexample: a user-provided copy assignment operator may throw
    static_assert(!asc::std::is_nothrow_assignable_v<throws&, const throws&>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
