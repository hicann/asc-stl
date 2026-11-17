# asc::std::equal_range

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

`asc::std::equal_range` returns the half-open subrange of elements equivalent to the target in a sorted range; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class T, class Compare>
[[nodiscard]] constexpr pair<ForwardIterator, ForwardIterator> equal_range(
    ForwardIterator first, ForwardIterator last, const T& value, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
[[nodiscard]] constexpr pair<ForwardIterator, ForwardIterator> equal_range(
    ForwardIterator first, ForwardIterator last, const T& value);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the value to find; must be usable as an argument of compare for comparison with the elements. |
| `Compare` | Comparator type; invoked in the form compare(a, b), returns bool and must satisfy strict weak ordering. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the sorted input range. |
| `last` | Input | End position of the sorted input range, not included. |
| `value` | Input | The value to find; the boundaries of the subrange of elements equivalent to this value are returned. |
| `compare` | Input | Comparator; invoked in the form compare(a, b), returns bool, where true means a is ordered before b; must satisfy strict weak ordering and be consistent with the ordering rule of the range. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the input range elements or of the values participating in the operation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the sorted input range. |
| `last` | Input | End position of the sorted input range, not included. |
| `value` | Input | The value to find; the boundaries of the subrange of elements equivalent to this value are returned. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<ForwardIterator, ForwardIterator>` | Returns the half-open subrange equivalent to the target value. |
| Prototype 2 | `pair<ForwardIterator, ForwardIterator>` | Returns the half-open subrange equivalent to the target value. |

Equivalence is defined by `!compare(element, value) && !compare(value, element)`;
it does not require `element == value`. With no equivalent element, both iterators
point to the insertion position, which can be inside the input range. For an empty
input, both are `first`. For random-access iterators, subtracting the returned
iterators gives the candidate count without scanning the equivalent elements.

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

This Host example locates candidate rows in a key-sorted table for a batch of
queries. Each returned interval identifies all matching rows, including repeated
keys. A missing key produces a zero count at its insertion position. A SIMT
operator can assign one query to each thread; `equal_range` itself remains
sequential within that thread.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int row_keys[6] = {2, 2, 2, 5, 5, 9};
    int queries[4] = {2, 4, 9, 10};
    int begins[4] = {}, ends[4] = {}, counts[4] = {};
    for (int i = 0; i < 4; ++i) {
        const auto rows = asc::std::equal_range(row_keys, row_keys + 6, queries[i]);
        begins[i] = static_cast<int>(rows.first - row_keys);
        ends[i] = static_cast<int>(rows.second - row_keys);
        counts[i] = ends[i] - begins[i];
    }
    return begins[0] == 0 && ends[0] == 3 && counts[0] == 3 &&
        begins[1] == 3 && ends[1] == 3 && counts[1] == 0 &&
        begins[2] == 5 && ends[2] == 6 && counts[2] == 1 &&
        begins[3] == 6 && ends[3] == 6 && counts[3] == 0;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
