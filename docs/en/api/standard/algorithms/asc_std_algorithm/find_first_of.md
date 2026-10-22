# asc::std::find_first_of

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

`asc::std::find_first_of` finds the first position in the range that matches an element of the given set; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
[[nodiscard]] constexpr ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
[[nodiscard]] constexpr ForwardIterator1 find_first_of(
    ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator1` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `ForwardIterator2` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `BinaryPredicate` | Callable object type that determines whether the elements satisfy the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the input range. |
| `last1` | Input | End position of the input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the input range. |
| `last2` | Input | End position of the input range, not included. |
| `predicate` | Input | Callable object used to determine whether the elements satisfy the condition. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator1` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `ForwardIterator2` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the input range. |
| `last1` | Input | End position of the input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the input range. |
| `last2` | Input | End position of the input range, not included. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator1` | Returns the matched position found; returns the end of the input range when there is no match. |
| Prototype 2 | `ForwardIterator1` | Returns the matched position found; returns the end of the input range when there is no match. |

## Constraints

- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::find_first_of(values, values + 8, other, other + 3);
    return result == values;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
