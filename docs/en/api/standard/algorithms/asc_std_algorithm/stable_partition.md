# asc::std::stable_partition

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

`asc::std::stable_partition` partitions the range according to a predicate while preserving the original order within each group; it executes sequentially within the execution entity where the caller resides.

Availability of this interface: Host; Host, AI Core SIMD programming.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class Predicate>
constexpr ForwardIterator stable_partition(ForwardIterator first, ForwardIterator last, Predicate predicate);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Predicate` | Type of the callable object that determines whether an element satisfies the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `predicate` | Input | Callable object used to determine whether an element satisfies the condition. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator` | Returns the boundary position between the two groups of elements after the stable partition. |

## Constraints

- Uses C++17.
- Non-allocating, non-recursive random-access pointer cores of stable_sort/stable_partition/inplace_merge.
- Host + ordinary AI Core.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto predicate = [](int value) { return value % 2 == 0; };
    auto result = asc::std::stable_partition(values, values + 8, predicate);
    return result == values + 4 && values[0] == 2 && values[3] == 8 && values[4] == 1 && values[7] == 7;
}
```

## Related APIs

- [`asc::parallel::stable_partition`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_stable_partition.md): Submits an asynchronous device operation using an execution policy.
