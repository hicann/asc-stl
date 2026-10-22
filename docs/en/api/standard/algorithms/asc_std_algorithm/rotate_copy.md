# asc::std::rotate_copy

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

`asc::std::rotate_copy` copies the elements, in their rotated order, into the output range; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class OutputIterator>
constexpr OutputIterator rotate_copy(
    ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `middle` | Input | Rotation boundary iterator, which must lie within [first, last] (equal to last is allowed); the output order is [middle, last) followed by [first, middle). |
| `last` | Input | End position of the input range, exclusive. |
| `result` | Output | Output iterator for writing results; the destination range must have sufficient capacity. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position after the last written element in the output range. |

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
    auto result = asc::std::rotate_copy(values, values + 3, values + 8, output);
    return result == output + 8 && output[0] == 4 && output[4] == 8 && output[5] == 1;
}
```

## Related APIs

- [`asc::parallel::rotate_copy`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_rotate_copy.md): Submits an asynchronous device operation using an execution policy.
