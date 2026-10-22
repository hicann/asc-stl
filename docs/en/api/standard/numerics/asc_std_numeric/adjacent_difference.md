# asc::std::adjacent_difference

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

Header: `<asc/std/numeric>`.

`asc::std::adjacent_difference` writes out the differences of adjacent input elements in order.

This page describes the sequentially executed overloads. The Device parallel submission entry point is [`asc::parallel::adjacent_difference`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_adjacent_difference.md); for its parameters, status return, and completion conditions, see the corresponding page.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class BinaryOperation> constexpr OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator> constexpr OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | The iterator type for writing the result range; the destination storage must have sufficient capacity. |
| `BinaryOperation` | The callable type of the binary operation for computing adjacent differences: accepts the current item and the previous item and returns the difference result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |
| `binary_op` | Input | The binary difference operation object, which computes the adjacent element differences as binary_op(current item, previous item); the overload omitting this parameter uses `operator-`. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | The iterator type for writing the result range; the destination storage must have sufficient capacity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position just after the last written result in the output range. |
| Prototype 2 | `OutputIterator` | Returns the position just after the last written result in the output range. |

## Constraints

- `[first, last)` must be a valid readable input range; starting from `result`, the same number of results must be writable.
- The first output is the first input element; subsequent outputs are computed as `current item - previous item` or `binary_op(current item, previous item)`.
- The operation results must be writable to the output range; custom operations must not modify the input range or invalidate iterators. In-place computation with `result == first` is allowed.

## Example

The following example writes the adjacent differences 1, 1, 1, 1 of 1, 2, 3, 4 to the four output elements.

```cpp
#include <asc/std/numeric>

bool example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    const auto end = asc::std::adjacent_difference(input, input + 4, output);
    return end == output + 4 &&
        output[0] == 1 &&
        output[1] == 1 &&
        output[2] == 1 &&
        output[3] == 1;
}
```

## Related APIs

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): the Device execution policy that specifies the Stream, temporary storage, and execution requirements.
