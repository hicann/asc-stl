# asc::std::exclusive_scan

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

`asc::std::exclusive_scan` writes out the prefix reduction excluding the current input, with the initial value as the first item.

This page describes the sequentially executed overloads. The Device parallel submission entry point is [`asc::parallel::exclusive_scan`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_exclusive_scan.md); for its parameters, status return, and completion conditions, see the corresponding page.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class T, class BinaryO> constexpr OutputIterator exclusive_scan(InputIterator first, InputIterator last, OutputIterator result, T init, BinaryO binary_op);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class T> constexpr OutputIterator exclusive_scan(InputIterator first, InputIterator last, OutputIterator result, T init);
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
| `T` | The type of the reduction initial value and the prefix results. |
| `BinaryO` | The callable type of the binary operation for the prefix reduction: accepts the current accumulated value and the current element. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |
| `init` | Input | The initial accumulated value of the prefix reduction; the first output element is this value, and each subsequent output is obtained by reducing this value with the prefix elements. |
| `binary_op` | Input | The binary reduction operation object, which produces the prefix results excluding the current item as binary_op(current accumulated value, current element); the overload omitting this parameter uses `operator+`. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | The iterator type for writing the result range; the destination storage must have sufficient capacity. |
| `T` | The type of the reduction initial value and the prefix results. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |
| `init` | Input | The initial accumulated value of the prefix reduction; the first output element is this value, and each subsequent output is obtained by reducing this value with the prefix elements. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position just after the last written result in the output range. |
| Prototype 2 | `OutputIterator` | Returns the position just after the last written result in the output range. |

## Constraints

- `[first, last)` must be a valid readable input range; starting from `result`, the same number of results must be writable.
- For a non-empty range, the first output is `init`, and subsequent outputs exclude the input at the current position; the operation results must be constructible or assignable to the accumulation type `T`.
- Custom operations must not modify the input range or invalidate iterators; in-place computation with `result == first` is allowed.

## Example

The following example writes the prefix sums 0, 1, 3, 6 excluding the current item to the four output elements.

```cpp
#include <asc/std/numeric>

bool example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    const auto end = asc::std::exclusive_scan(input, input + 4, output, 0);
    return end == output + 4 &&
        output[0] == 0 &&
        output[1] == 1 &&
        output[2] == 3 &&
        output[3] == 6;
}
```

## Related APIs

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): the Device execution policy that specifies the Stream, temporary storage, and execution requirements.
