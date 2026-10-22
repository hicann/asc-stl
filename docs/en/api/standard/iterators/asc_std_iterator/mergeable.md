# asc::std::mergeable

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

`asc::std::mergeable` determines whether a type or expression satisfies the requirements of `mergeable`.

C++17 provides a same-name `inline constexpr bool` variable template; C++20 and above provide the concept. Both forms can be used in `static_assert`, and in C++17 it can also be used together with `enable_if`. Constrained template parameters, `requires`, and constraint subsumption still require C++20 language support.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

The following is an excerpt of the definition; the auxiliary constraints it references are provided by the header. Both the C++17 variable template and the C++20 concept can be used directly in `static_assert`.

### C++20 and above

```cpp
namespace asc::std {
template <class _Input1, class _Input2, class _Output, class _Comp = ::asc::std::ranges::less, class _Proj1 = identity,
    class _Proj2 = identity>
concept mergeable = input_iterator<_Input1> && input_iterator<_Input2> && weakly_incrementable<_Output> &&
    indirectly_copyable<_Input1, _Output> && indirectly_copyable<_Input2, _Output> &&
    indirect_strict_weak_order<_Comp, projected<_Input1, _Proj1>, projected<_Input2, _Proj2>>;
}
```

### C++17

```cpp
namespace asc::std {
template <class Input1, class Input2, class Output, class Comp = ::asc::std::ranges::less, class Proj1 = identity,
    class Proj2 = identity>
inline constexpr bool mergeable = __mergeable_impl<Input1, Input2, Output, Comp, Proj1, Proj2>;
}
```

The C++20 code block shows the Host definition; the device side performs the test through the corresponding projection call results and predicate conditions. The default comparison and projection arguments apply in the same way at the corresponding call positions.

## Constraints

- The iterator test is used as a Boolean constant in C++17; beyond the expression conditions checkable at compile time, the semantic requirements of that iterator category must also be satisfied.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/functional>

bool example()
{
    static_assert(asc::std::mergeable<int*, int*, int*>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
