# asc::std::transform

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

`asc::std::transform` invokes the transformation function on each input element and writes the results in order into the output; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class OutputIterator, class UnaryOperation>
constexpr OutputIterator transform(
    InputIterator first, InputIterator last, OutputIterator result, UnaryOperation operation);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
constexpr OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
    OutputIterator result, BinaryOperation binary_op);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `UnaryOperation` | Type of the callable object that performs the operation of this page on input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `result` | Output | Output iterator for writing results; the destination range must have sufficient capacity. |
| `operation` | Input | Unary transformation operation invoked once for each input element in order in the form `operation(elem)`, with the return value written to the corresponding position of the output range. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `BinaryOperation` | Type of the callable object that performs the operation of this page on input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the first input range. |
| `last1` | Input | End position of the first input range, exclusive. |
| `first2` | Input | Iterator or pointer to the start of the second input range; the pointed-to range must be at least as long as the first input range. |
| `result` | Output | Output iterator for writing results; the destination range must have capacity for all transformation results. |
| `binary_op` | Input | Binary transformation operation invoked once for each pair of corresponding elements of the two input ranges in order in the form `binary_op(elem1, elem2)`, with the return value written to the corresponding position of the output range. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position after the last written element in the output range. |
| Prototype 2 | `OutputIterator` | Returns the position after the last written element in the output range. |

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
    auto operation = [](int value) { return value * 2; };
    auto result = asc::std::transform(values, values + 8, output, operation);
    return result == output + 8 && output[0] == 2 && output[7] == 16;
}
```

## Related APIs

- [`asc::parallel::transform`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform.md): Submits an asynchronous device operation using an execution policy.
