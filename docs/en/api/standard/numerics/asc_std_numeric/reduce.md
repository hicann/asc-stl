# asc::std::reduce

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

`asc::std::reduce` reduces the range starting from the initial value in the input order of the current implementation.

This page describes the sequentially executed overloads. The Device parallel submission entry point is [`asc::parallel::reduce`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_reduce.md); for its parameters, status return, and completion conditions, see the corresponding page.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class T, class BinaryO> [[nodiscard]] constexpr T reduce(InputIterator first, InputIterator last, T init, BinaryO binary_op);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class T> [[nodiscard]] constexpr T reduce(InputIterator first, InputIterator last, T init);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
template<class InputIterator> [[nodiscard]] constexpr typename iterator_traits<InputIterator>::value_type reduce(InputIterator first, InputIterator last);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | The type of the reduction initial value, the intermediate accumulated value, and the returned result. |
| `BinaryO` | The callable type of the binary operation that merges the accumulated value step by step: accepts two T values and returns a result convertible to T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `init` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |
| `binary_op` | Input | The binary reduction operation object, which merges step by step as binary_op(current accumulated value, current element); the overload omitting this parameter uses `operator+`. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | The type of the reduction initial value, the intermediate accumulated value, and the returned result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `init` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the value of the input range reduced with the selected binary operation. |
| Prototype 2 | `T` | Returns the value of the input range reduced with the selected binary operation. |
| Prototype 3 | `typename iterator_traits<InputIterator>::value_type` | Returns the value of the input range reduced with the selected binary operation. |

## Constraints

- `[first, last)` must be a valid readable input range.
- The current implementation reduces in input order, updating the accumulated value with `operator+` or `binary_op`; the operation results must be assignable back to the result type.
- The overload without an initial value uses a value-initialized object of the input element value type as the initial value; an empty range returns the initial value.

## Example

The following example reduces 1, 2, 3, 4 starting from 0 and returns 10.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::reduce(input, input + 4, 0);
}

bool verify_example()
{
    return example() == 10;
}
```

## Related APIs

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): the Device execution policy that specifies the Stream, temporary storage, and execution requirements.
