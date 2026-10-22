# asc::std::search_n

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

`asc::std::search_n` finds a target value occurring consecutively a specified number of times; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class Size, class T, class BinaryPredicate>
[[nodiscard]] constexpr ForwardIterator search_n(
    ForwardIterator first, ForwardIterator last, Size count, const T& value_, BinaryPredicate pred);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class ForwardIterator, class Size, class T>
[[nodiscard]] constexpr ForwardIterator search_n(
    ForwardIterator first, ForwardIterator last, Size count, const T& value_);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Size` | Type representing the length of the sequence to be matched, usually an integer type or the iterator difference type. |
| `T` | Type of the value to be matched; must be comparable with elements of the range via `operator==` or usable as an argument of pred. |
| `BinaryPredicate` | Binary predicate type that determines whether an element and the value to be matched are equivalent. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `count` | Input | Number of consecutive elements to be matched. |
| `value_` | Input | Value to be matched; searches the range for the start position of a sequence of count consecutive elements equivalent to this value. |
| `pred` | Input | Binary predicate invoked in the form `pred(elem, value_)` returning bool; a return value of true is treated as an element match. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Size` | Type representing the length of the sequence to be matched, usually an integer type or the iterator difference type. |
| `T` | Type of the value to be matched; must be comparable with elements of the range via `operator==`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `count` | Input | Number of consecutive elements to be matched. |
| `value_` | Input | Value to be matched; searches the range for the start position of a sequence of count consecutive elements equivalent (`operator==`) to this value. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator` | Returns the matched position found; returns the end of the input range when there is no match. |
| Prototype 2 | `ForwardIterator` | Returns the matched position found; returns the end of the input range when there is no match. |

## Constraints

- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::search_n(values, values + 8, 2, 3);
    return result == values + 8;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
