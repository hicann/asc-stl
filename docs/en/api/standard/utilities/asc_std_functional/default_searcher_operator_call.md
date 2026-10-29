# asc::std::default_searcher::`operator()`

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

`asc::std::default_searcher::operator()` processes the current object and the operands according to the available operator rules of `default_searcher`.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::default_searcher`](default_searcher.md).

```cpp
// Excerpt of the declaration inside asc::std::default_searcher; the template parameters and other members are provided by the enclosing class.
template<class ForwardIterator2> asc::std::pair<ForwardIterator2, ForwardIterator2> operator()(ForwardIterator2 first, ForwardIterator2 last) const;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator2` | The iterator type used to traverse the input range; it must satisfy the traversal capability required by the prototype. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::pair<ForwardIterator2, ForwardIterator2>` | Returns the start and end iterators of the matched subsequence; returns the end position when no match is found. |

## Constraints

- The pattern iterators must designate a valid forward range; the underlying storage of that range must remain valid while the searcher is in use. The predicate and the searched range must satisfy the comparison and iteration requirements; whether a user predicate itself allocates is determined by its implementation.

## Example

The following Host snippet demonstrates the call with concrete types; the input ranges and objects must remain valid while in use.

```cpp
#include <asc/std/functional>

decltype(auto) example(int* pattern, int* values)
{
    asc::std::default_searcher<int*> searcher(pattern, pattern + 2);
    return searcher(values, values + 4);
}

bool verify_example()
{
    int pattern[] = {2, 3};
    int values[] = {1, 2, 3, 4};
    const auto result = example(pattern, values);
    return result.first == values + 1 && result.second == values + 3;
}
```

## Related APIs

- [`asc::std::default_searcher`](default_searcher.md)
- [API list for this header](asc_std_functional.md)
