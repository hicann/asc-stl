# asc::std::shift_right

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

`asc::std::shift_right` shifts the elements of the range right by the specified distance; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator>
constexpr ForwardIterator shift_right(
    ForwardIterator first, ForwardIterator last, typename iterator_traits<ForwardIterator>::difference_type n);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `n` | Input | Non-negative shift distance in elements; when the distance is not less than the range length, no elements are retained. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `ForwardIterator` | Returns the start position of the retained shifted range; it is first when `n == 0`, and last when `n` is not less than the range length. |

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
    auto result = asc::std::shift_right(values, values + 8, 2);
    return result == values + 2 && values[2] == 1 && values[7] == 6;
}
```

## Related APIs

- [`asc::parallel::shift_right`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_shift_right.md): Submits an asynchronous device operation using an execution policy.
