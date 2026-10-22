# asc::std::merge

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

`asc::std::merge` merges two sorted ranges and writes the result to the output range; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
constexpr OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
    OutputIterator result, Compare compare);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class OutputIterator>
constexpr OutputIterator merge(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `Compare` | Comparator type; invoked in the form compare(a, b), returns bool and must satisfy strict weak ordering. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the first sorted input range. |
| `last1` | Input | End position of the first sorted input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the second sorted input range. |
| `last2` | Input | End position of the second sorted input range, not included. |
| `result` | Output | Output iterator where the merged results are written; the destination range must have enough capacity to hold all elements of both input ranges. |
| `compare` | Input | Comparator; invoked in the form compare(a, b), returns bool; returning true means a is ordered before b; must satisfy strict weak ordering and be consistent with the ordering rules of both input ranges. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the first sorted input range. |
| `last1` | Input | End position of the first sorted input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the second sorted input range. |
| `last2` | Input | End position of the second sorted input range, not included. |
| `result` | Output | Output iterator where the merged results are written; the destination range must have enough capacity to hold all elements of both input ranges. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position just after the last written element in the output range. |
| Prototype 2 | `OutputIterator` | Returns the position just after the last written element in the output range. |

## Constraints

- Uses C++17.
- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto result = asc::std::merge(values, values + 8, other, other + 8, output);
    return result == output + 16 && output[0] == 1 && output[1] == 1 && output[15] == 8;
}
```

## Related APIs

- [`asc::parallel::merge`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_merge.md): Submits an asynchronous device operation using an execution policy.
