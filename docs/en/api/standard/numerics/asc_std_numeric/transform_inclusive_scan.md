# asc::std::transform_inclusive_scan

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

`asc::std::transform_inclusive_scan` first transforms the inputs, then writes out the prefix reduction including the current item.

This page describes the sequentially executed overloads. The Device parallel submission entry point is [`asc::parallel::transform_inclusive_scan`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform_inclusive_scan.md); for its parameters, status return, and completion conditions, see the corresponding page.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class BinaryO, class UnaryO> constexpr OutputIterator transform_inclusive_scan(InputIterator first, InputIterator last, OutputIterator result, BinaryO binary_op, UnaryO unary_op);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class T, class BinaryO, class UnaryO> constexpr OutputIterator transform_inclusive_scan(InputIterator first, InputIterator last, OutputIterator result, BinaryO binary_op, UnaryO unary_op, T init);
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
| `BinaryO` | The callable type of the binary operation for the prefix reduction: accepts the current accumulated value and the transformed element. |
| `UnaryO` | The callable type of the unary transformation: each input element is transformed before being reduced. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |
| `binary_op` | Input | The binary reduction operation object, which merges the current element transformed by unary_op into the accumulated value. |
| `unary_op` | Input | The unary transformation operation object, applied to each input element first before taking part in the reduction. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | The iterator type for writing the result range; the destination storage must have sufficient capacity. |
| `T` | The type of the reduction initial value and the prefix results. |
| `BinaryO` | The callable type of the binary operation for the prefix reduction: accepts the current accumulated value and the transformed element. |
| `UnaryO` | The callable type of the unary transformation: each input element is transformed before being reduced. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |
| `binary_op` | Input | The binary reduction operation object, which merges the current element transformed by unary_op into the accumulated value. |
| `unary_op` | Input | The unary transformation operation object, applied to each input element first before taking part in the reduction. |
| `init` | Input | The reduction initial value, used as the starting accumulated value before the first output; it is counted into every output element. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position just after the last written result in the output range. |
| Prototype 2 | `OutputIterator` | Returns the position just after the last written result in the output range. |

## Constraints

- `[first, last)` must be a valid readable input range; starting from `result`, the same number of results must be writable.
- `unary_op` is called first to transform the inputs, then `binary_op` is called to reduce; every output includes the transformation result at the current position.
- Prototype 1 initializes the accumulator with the first transformed element and stores it in the input iterator’s value type. In prototype 2, `init` supplies the starting value and the accumulator type. To accumulate in a wider type, pass an initial value of that type, such as `int{0}` for a sum. Each reduction result must be assignable to the accumulator.
- The operations must not modify the input range or invalidate iterators; in-place computation with `result == first` is allowed.

## Example

The example converts byte values to `int` and writes their prefix sums 200, 300 and 360.

```cpp
#include <asc/std/numeric>

bool example()
{
    const unsigned char input[] = {200, 100, 60};
    int output[3] = {};
    const auto end = asc::std::transform_inclusive_scan(input, input + 3, output,
        [](int a, int b) { return a + b; }, [](unsigned char value) { return static_cast<int>(value); }, int{0});
    return end == output + 3 && output[0] == 200 && output[1] == 300 && output[2] == 360;
}
```

## Related APIs

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): the Device execution policy that specifies the Stream, temporary storage, and execution requirements.
