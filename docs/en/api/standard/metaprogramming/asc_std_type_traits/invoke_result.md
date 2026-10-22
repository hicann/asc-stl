# asc::std::invoke_result

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

`asc::std::invoke_result` obtains the result type of calling a function object with the given arguments.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class Fp, class ...Args> struct invoke_result;
} // namespace asc::std
```

## Constraints

- The result member `type` is provided only when the expression invoking `Fn` with `Args...` under the `asc::std::invoke` rules is valid, and the return reference category of that expression is preserved.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    struct Functor { double operator()(int) const { return 0.5; } }; // local functor
    // Result type of calling a function pointer with int
    static_assert(asc::std::is_same_v<asc::std::invoke_result<int (*)(int), int>::type, int>);
    static_assert(asc::std::is_same_v<asc::std::invoke_result_t<Functor, int>, double>);
    // Counterexample: calling Functor with int does not return int
    static_assert(!asc::std::is_same_v<asc::std::invoke_result_t<Functor, int>, int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
