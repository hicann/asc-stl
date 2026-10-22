# asc::std::unique_copy

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

`asc::std::unique_copy` copies the range, skipping consecutive equivalent duplicate elements; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class OutputIterator, class BinaryPredicate>
constexpr OutputIterator unique_copy(
    InputIterator first, InputIterator last, OutputIterator result, BinaryPredicate pred);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class InputIterator, class OutputIterator>
constexpr OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result);
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
| `BinaryPredicate` | Binary predicate type that determines whether adjacent elements are equivalent. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `result` | Output | Output iterator for writing results; the destination range must have sufficient capacity. |
| `pred` | Input | Binary predicate invoked in the form `pred(elem1, elem2)` returning bool; a return value of true is treated as adjacent equivalence, and only the first of each group of equivalent elements is copied. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `result` | Output | Output iterator for writing results; the destination range must have sufficient capacity. |

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
    auto result = asc::std::unique_copy(values, values + 8, output);
    return result == output + 8 && output[0] == 1 && output[7] == 8;
}
```

## Related APIs

- [`asc::parallel::unique_copy`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_unique_copy.md): Submits an asynchronous device operation using an execution policy.
