# asc::std::remove

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

`asc::std::remove` moves the elements not equal to the target value stably to the front of the range and returns the new logical end; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
[[nodiscard]] constexpr ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value_);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the value to be removed; must be comparable with elements of the range via `operator==`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `value_` | Input | Value to be removed, compared with elements by equality semantics (`operator==`); equal elements are not kept in the logical result range. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator` | Returns the new logical end after the retained elements; the container size is unchanged. |

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
    auto result = asc::std::remove(values, values + 8, 3);
    return result == values + 7 && values[2] == 4 && values[6] == 8;
}
```

## Related APIs

- [`asc::parallel::remove`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_remove.md): Submits an asynchronous device operation using an execution policy.
