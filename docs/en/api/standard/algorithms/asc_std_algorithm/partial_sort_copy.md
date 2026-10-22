# asc::std::partial_sort_copy

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

`asc::std::partial_sort_copy` copies the smallest elements of the input, in sorted order, into a bounded output range; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class RandomAccessIterator, class Compare>
constexpr RandomAccessIterator partial_sort_copy(InputIterator first, InputIterator last,
    RandomAccessIterator result_first, RandomAccessIterator result_last, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class InputIterator, class RandomAccessIterator>
constexpr RandomAccessIterator partial_sort_copy(
    InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Compare` | Type of the comparison object that defines the order of elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `result_first` | Output | Iterator to the start of the output range; results are written into the range starting at this position. |
| `result_last` | Output | End position of the output range (exclusive); together with `result_first` it bounds the capacity. |
| `compare` | Input | Comparison object used to determine the order of elements. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `result_first` | Output | Iterator to the start of the output range; results are written into the range starting at this position. |
| `result_last` | Output | End position of the output range (exclusive); together with `result_first` it bounds the capacity. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `RandomAccessIterator` | Returns the position after the last written element in the output range. |
| Prototype 2 | `RandomAccessIterator` | Returns the position after the last written element in the output range. |

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto result = asc::std::partial_sort_copy(values, values + 8, output, output + 8);
    return result == output + 8 && output[0] == 1 && output[7] == 8;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
