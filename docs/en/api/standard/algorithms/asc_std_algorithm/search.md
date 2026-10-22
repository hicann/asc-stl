# asc::std::search

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

Header: `<asc/std/algorithm>`.

`asc::std::search` returns the start position of the first occurrence of a subsequence within the range; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class Searcher>
constexpr ForwardIterator search(ForwardIterator first, ForwardIterator last, const Searcher& searcher);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
constexpr ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 pattern_first,
    ForwardIterator2 pattern_last, BinaryPredicate predicate);
}  // namespace asc::std
```

### Prototype 3

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
constexpr ForwardIterator1 search(
    ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 pattern_first, ForwardIterator2 pattern_last);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Searcher` | Searcher type; invoking searcher(first, last) returns the start and end iterators of the matched range. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `searcher` | Input | Reference to the object used to provide "the start position of the first occurrence of the query subsequence in the range"; the referenced object must remain valid during the call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator1` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `ForwardIterator2` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `BinaryPredicate` | Type of the callable object that determines whether an element satisfies the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `pattern_first` | Input | Iterator or pointer to the start of the input range. |
| `pattern_last` | Input | End position of the input range, exclusive. |
| `predicate` | Input | Callable object used to determine whether an element satisfies the condition. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator1` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `ForwardIterator2` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `pattern_first` | Input | Iterator or pointer to the start of the input range. |
| `pattern_last` | Input | End position of the input range, exclusive. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator` | Returns the start position of the first occurrence of the subsequence within the range. |
| Prototype 2 | `ForwardIterator1` | Returns the start position of the first occurrence of the subsequence within the range. |
| Prototype 3 | `ForwardIterator1` | Returns the start position of the first occurrence of the subsequence within the range. |

## Constraints

- Returns last1 when the subsequence is not found; returns first1 for an empty subsequence.

- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::search(values, values + 8, other, other + 3);
    return result == values;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
