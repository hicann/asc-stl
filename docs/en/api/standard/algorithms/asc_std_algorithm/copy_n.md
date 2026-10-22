# asc::std::copy_n

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

`asc::std::copy_n` copies the specified number of elements starting from the start position; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

```cpp
namespace asc::std {
template <class InputIterator, class Size, class OutputIterator>
constexpr OutputIterator copy_n(InputIterator first, Size count, OutputIterator result);
}  // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `Size` | Type representing the number of elements to copy, typically an integer type or the iterator difference type. |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `count` | Input | Number of elements to copy starting from first. |
| `result` | Output | Output iterator where the results are written; the destination range must have sufficient capacity. |

## Return Value

| Return type | Description |
| --- | --- |
| `OutputIterator` | Returns the position just after the last written element; returns `result` unchanged when `count <= 0`. |

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
    int output[16] = {};
    auto result = asc::std::copy_n(values, 4, output);
    return result == output + 4 && output[0] == 1 && output[3] == 4;
}
```

## Related APIs

- [`asc::parallel::copy_n`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_copy_n.md): Submits an asynchronous device operation using an execution policy.
