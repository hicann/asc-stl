# asc::std::is_nothrow_invocable

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

`asc::std::is_nothrow_invocable` determines at compile time whether invocation with the given arguments is possible and does not throw.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class Fn, class ...Args> struct is_nothrow_invocable;
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
    using fn = int (*)(int);
    struct nothrow {
        int operator()(int) const noexcept { return 0; }
    };
    struct throws {
        int operator()(int) { throw 0; }
    };
    // Positive example: operator() is declared noexcept, so the call does not throw
    static_assert(asc::std::is_nothrow_invocable<nothrow, int>::value);
    static_assert(asc::std::is_nothrow_invocable_v<nothrow, int>);
    // Counterexample: a function pointer cannot statically guarantee no throwing, and operator() may throw
    static_assert(!asc::std::is_nothrow_invocable_v<fn, int>);
    static_assert(!asc::std::is_nothrow_invocable_v<throws, int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
