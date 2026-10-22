# asc::std::relation

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

Header: `<asc/std/concepts>`.

`asc::std::relation` determines that the callable object `R` forms a binary relation over the two domains of values `T` and `U`: let `r` be an expression of type `R`, `a` of type `T`, and `b` of type `U`; then the four call combinations `r(a, a)`, `r(b, b)`, `r(a, b)`, and `r(b, a)` must all satisfy `predicate`. `equivalence_relation` and `strict_weak_order` further impose the semantic requirements of an equivalence relation or a strict weak ordering on top of this.

C++17 provides an `inline constexpr bool` variable template of the same name; C++20 and above with concepts enabled provide a native concept. Both forms can be used in `static_assert`, and in C++17 the name can also be used together with `enable_if`. Constrained template parameters, `requires`, and constraint subsumption still require C++20 language support.

Standard semantics reference: [cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts).

## Declaration

This public name is an inline constexpr bool variable template in C++17 and a native concept in C++20 and above with concepts enabled. The two forms have the same template parameters. The following queries the Boolean value through the already-defined public name; it is not a forward declaration of the concept; satisfies_relation is only the query name used in the example.

```cpp
template<class R, class T, class U>
inline constexpr bool satisfies_relation = asc::std::relation<R, T, U>;
```

## Constraints

- The C++17 variable template does not participate in concept constraint subsumption.
- R must satisfy predicate for all four argument combinations T/T, U/U, T/U, and U/T; verifying only one cross-type call is not sufficient.
- The same-named condition can be used in static_assert or SFINAE from C++17 onward; the native concept, requires, and constraint subsumption require the corresponding C++20 language support.
- The condition query only checks the expressible type and expression properties; it does not actually construct, swap, or call objects, and does not replace the corresponding runtime semantic preconditions.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/concepts>

struct increment { int operator()(int value) const { return value + 1; } };

struct less { bool operator()(int left, int right) const { return left < right; } };

static_assert(asc::std::relation<less, int, long>);
static_assert(!asc::std::relation<increment, int, int>);
```

## Related APIs

- [API list for this header](asc_std_concepts.md)
