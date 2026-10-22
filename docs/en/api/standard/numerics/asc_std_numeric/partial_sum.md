# asc::std::partial_sum

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

`asc::std::partial_sum` writes out the prefix reduction results in order.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class BinaryOperation> constexpr OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op);
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator> constexpr OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result);
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | The iterator type for writing the result range; the destination storage must have sufficient capacity. |
| `BinaryOperation` | The callable type of the binary operation for the prefix reduction: accepts the current partial sum and the current element and returns the new partial sum. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |
| `binary_op` | Input | The binary reduction operation object, which produces the prefix results as binary_op(current partial sum, current element); the overload omitting this parameter uses `operator+`. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `OutputIterator` | The iterator type for writing the result range; the destination storage must have sufficient capacity. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `result` | Output | The output iterator for writing the results; the destination range must have sufficient capacity. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `OutputIterator` | Returns the position just after the last written result in the output range. |
| Prototype 2 | `OutputIterator` | Returns the position just after the last written result in the output range. |

## Constraints

- `[first, last)` must be a valid readable input range; starting from `result`, the same number of results must be writable.
- The first output is the first input element; subsequent outputs merge the current accumulated value and the input element in order using `operator+` or `binary_op`.
- The operation results must be assignable to the value type of the input elements; the operations must not modify the input range or invalidate iterators. In-place computation with `result == first` is allowed.

## Example

The following example writes the prefix sums 1, 3, 6, 10 of 1, 2, 3, 4 to the four output elements.

```cpp
#include <asc/std/numeric>

bool example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    const auto end = asc::std::partial_sum(input, input + 4, output);
    return end == output + 4 &&
        output[0] == 1 &&
        output[1] == 3 &&
        output[2] == 6 &&
        output[3] == 10;
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
