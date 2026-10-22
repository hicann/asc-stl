# asc::std::fill_n

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

`asc::std::fill_n` assigns the given value to the specified number of elements starting from the start position; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class OutputIterator, class Size, class T>
constexpr OutputIterator fill_n(OutputIterator first, Size count, const T& value);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OutputIterator` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `Size` | Type representing the number of elements to fill, typically an integer type or the iterator difference type. |
| `T` | Type of the value to fill; must be assignable to the destination elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the destination output range; results are written starting from this position. |
| `count` | Input | Number of elements to fill starting from first. |
| `value` | Input | The value to fill; assigned to the count elements starting from first. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position just after the last written element in the output range. |

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
    auto result = asc::std::fill_n(values, 4, 7);
    return result == values + 4 && values[0] == 7 && values[3] == 7 && values[4] == 5;
}
```

## Related APIs

- [`asc::parallel::fill_n`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_fill_n.md): Submits an asynchronous device operation using an execution policy.
