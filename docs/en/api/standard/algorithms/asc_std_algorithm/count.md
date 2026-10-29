# asc::std::count

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

`asc::std::count` counts the elements in the range that are equal to the given value; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class T>
[[nodiscard]] constexpr typename asc::std::iterator_traits<InputIterator>::difference_type count(
    InputIterator first, InputIterator last, const T& value);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the value to count; must be comparable with the input elements via `operator==`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `value` | Input | The value to count; compared with the elements of the input range using equality semantics (`operator==`). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `typename asc::std::iterator_traits<InputIterator>::difference_type` | Returns the number of elements in the input range that match the target value or satisfy the predicate. |

## Constraints

- Uses C++17.
- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer with sufficient capacity.

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::count(values, values + 8, 3);
}

bool verify_example()
{
    return example() == 1;
}
```

## Related APIs

- [`asc::parallel::count`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_count.md): Submits an asynchronous device operation using an execution policy.
