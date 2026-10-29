# asc::std::transform_reduce

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

`asc::std::transform_reduce` transforms element by element first and then reduces the results.

This page describes the sequentially executed overloads. The Device parallel submission entry point is [`asc::parallel::transform_reduce`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform_reduce.md); for its parameters, status return, and completion conditions, see the corresponding page.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class T, class BinaryO, class UnaryO> [[nodiscard]] constexpr T transform_reduce(InputIterator first, InputIterator last, T initial, BinaryO reduce_operation, UnaryO transform_operation);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator1, class InputIterator2, class T, class BinaryOp1, class BinaryOp2> [[nodiscard]] constexpr T transform_reduce(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T initial, BinaryOp1 reduce_operation, BinaryOp2 transform_op);
} // namespace asc::std
```

This prototype applies to `C++17+`, with availability in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
template<class InputIterator1, class InputIterator2, class T> [[nodiscard]] constexpr T transform_reduce(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T initial);
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
| `BinaryO` | The callable type of the binary reduction operation that merges each elementwise transformation result into the accumulated value. |
| `UnaryO` | The callable type of the unary transformation applied to a single input element. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `initial` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |
| `reduce_operation` | Input | The binary reduction operation object, which merges each elementwise transformation or combination result into the current accumulated value. |
| `transform_operation` | Input | The unary transformation operation object, applied to each element of the first range before taking part in the reduction. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | The type of the reduction initial value, the intermediate accumulated value, and the returned result. |
| `BinaryOp1` | The callable type of the binary reduction operation that merges each pairwise combination result into the accumulated value. |
| `BinaryOp2` | The callable type of the binary transformation that combines elements at corresponding positions of the two input ranges. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | The starting iterator or pointer of the first input range. |
| `last1` | Input | The end position of the first input range, exclusive. |
| `first2` | Input | The starting iterator of the second input range; the length of this range must not be smaller than the first range. |
| `initial` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |
| `reduce_operation` | Input | The binary reduction operation object, which merges each elementwise transformation or combination result into the current accumulated value. |
| `transform_op` | Input | The binary combination operation object, applied to elements at corresponding positions of the two ranges. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | The type of the reduction initial value, the intermediate accumulated value, and the returned result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | The starting iterator or pointer of the first input range. |
| `last1` | Input | The end position of the first input range, exclusive. |
| `first2` | Input | The starting iterator of the second input range; the length of this range must not be smaller than the first range. |
| `initial` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | The numeric result of the input values after the operation specified by the interface. |
| Prototype 2 | `T` | The numeric result of the input values after the operation specified by the interface. |
| Prototype 3 | `T` | The numeric result of the input values after the operation specified by the interface. |

## Constraints

- The single input range must be a valid readable range; the two input range form requires at least as many readable elements starting from `first2` as there are in `[first1, last1)`.
- The transformation is performed first on a single input or on two corresponding inputs, then the results are reduced with the initial value; the operation results must be assignable back to `T`.
- The current implementation processes in input order; the transformation and reduction operations must not modify the input ranges or invalidate iterators.

## Example

The following example first multiplies each of 1, 2, 3, 4 by 2, then reduces starting from 0 and returns 20.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::transform_reduce(input, input + 4, 0, [](int a, int b) { return a + b; }, [](int a) { return a * 2; });
}

bool verify_example()
{
    return example() == 20;
}
```

## Related APIs

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): the Device execution policy that specifies the Stream, temporary storage, and execution requirements.
