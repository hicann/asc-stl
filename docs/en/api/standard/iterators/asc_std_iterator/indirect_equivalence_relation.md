# asc::std::indirect_equivalence_relation

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

Header: `<asc/std/iterator>`.

`asc::std::indirect_equivalence_relation` determines whether a type or expression satisfies the requirements of `indirect_equivalence_relation`.

C++17 provides a same-name `inline constexpr bool` variable template; C++20 and above provide the concept. Both forms can be used in `static_assert`, and in C++17 it can also be used together with `enable_if`. Constrained template parameters, `requires`, and constraint subsumption still require C++20 language support.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

The following is an excerpt of the definition; the auxiliary constraints it references are provided by the header. Both the C++17 variable template and the C++20 concept can be used directly in `static_assert`.

### C++20 and above

```cpp
namespace asc::std {
template <class F, class It1, class It2 = It1>
concept indirect_equivalence_relation = indirectly_readable<It1> && indirectly_readable<It2> && copy_constructible<F> &&
    equivalence_relation<F&, iter_value_t<It1>&, iter_value_t<It2>&> &&
    equivalence_relation<F&, iter_value_t<It1>&, iter_reference_t<It2>> &&
    equivalence_relation<F&, iter_reference_t<It1>, iter_value_t<It2>&> &&
    equivalence_relation<F&, iter_reference_t<It1>, iter_reference_t<It2>> &&
    equivalence_relation<F&, iter_common_reference_t<It1>, iter_common_reference_t<It2>>;
}
```

### C++17

```cpp
namespace asc::std {
template <class F, class It1, class It2 = It1>
inline constexpr bool indirect_equivalence_relation = __indirect_binary_predicate_impl<F, It1, It2, 1>;
}
```

## Constraints

- The iterator test is used as a Boolean constant in C++17; beyond the expression conditions checkable at compile time, the semantic requirements of that iterator category must also be satisfied.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/functional>

bool example()
{
    static_assert(asc::std::indirect_equivalence_relation<asc::std::equal_to<>, int*, int*>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
