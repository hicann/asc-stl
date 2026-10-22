# asc::std::default_searcher

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

Header: `<asc/std/functional>`.

`asc::std::default_searcher` stores the search pattern and the comparison condition for subsequence searching.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

```cpp
namespace asc::std {
template<class ForwardIterator, class BinaryPredicate = asc::std::equal_to<>> class default_searcher;
} // namespace asc::std
```

## Constraints

- The pattern iterators must designate a valid forward range; the underlying storage of that range must remain valid while the searcher is in use. The predicate and the searched range must satisfy the comparison and iteration requirements; whether a user predicate itself allocates is determined by its implementation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/functional>

bool example()
{
    int values[] = {1, 2, 3, 4};
    int pattern[] = {2, 3};
    asc::std::default_searcher<int*> searcher(pattern, pattern + 2);
    auto result = searcher(values, values + 4);
    return result.first == values + 1 && result.second == values + 3;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
