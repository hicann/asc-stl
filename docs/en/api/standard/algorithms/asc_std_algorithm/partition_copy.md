# asc::std::partition_copy

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

`asc::std::partition_copy` copies elements into two output ranges respectively according to a predicate; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class OutputIterator1, class OutputIterator2, class Predicate>
constexpr pair<OutputIterator1, OutputIterator2> partition_copy(
    InputIterator first, InputIterator last, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator1` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `OutputIterator2` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `Predicate` | Type of the callable object that determines whether an element satisfies the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `out_true` | Output | One of the output iterators for writing results; elements for which the predicate returns true are copied into this range, whose capacity must be sufficient to hold the corresponding elements. |
| `out_false` | Output | One of the output iterators for writing results; elements for which the predicate returns false are copied into this range, whose capacity must be sufficient to hold the corresponding elements. |
| `pred` | Input | Unary predicate invoked in the form `pred(elem)` returning bool, which determines which output range an element is copied into. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<OutputIterator1, OutputIterator2>` | Returns the end positions of the written portions of the two output ranges. |

## Constraints

- Uses C++17.
- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto predicate = [](int value) { return value % 2 == 0; };
    auto result = asc::std::partition_copy(values, values + 8, output, output + 8, predicate);
    return result.first == output + 4 && result.second == output + 12 && output[0] == 2 && output[8] == 1;
}
```

## Related APIs

- [`asc::parallel::partition_copy`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_partition_copy.md): Submits an asynchronous device operation using an execution policy.
