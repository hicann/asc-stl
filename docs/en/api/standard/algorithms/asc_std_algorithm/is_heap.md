# asc::std::is_heap

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

`asc::std::is_heap` determines whether the range satisfies heap ordering; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class RandomAccessIterator, class Compare>
[[nodiscard]] constexpr bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class RandomAccessIterator>
[[nodiscard]] constexpr bool is_heap(RandomAccessIterator first, RandomAccessIterator last);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Compare` | Comparison object type that defines the ordering of the elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `comp` | Input | Comparison object used to determine the ordering of the elements. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Returns `true` when the input range satisfies the property indicated by the interface name, `false` otherwise. |
| Prototype 2 | `bool` | Returns `true` when the input range satisfies the property indicated by the interface name, `false` otherwise. |

## Constraints

- Uses C++17.
- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer with sufficient capacity.

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::is_heap(values, values + 8);
}

bool verify_example()
{
    return example() == false;
}
```

## Related APIs

- [`asc::parallel::is_heap`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_is_heap.md): Submits an asynchronous device operation using an execution policy.
