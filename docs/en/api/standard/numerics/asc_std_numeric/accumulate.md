# asc::std::accumulate

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

`asc::std::accumulate` sequentially reduces the input range starting from the initial value.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator, class T, class BinaryOperation> [[nodiscard]] constexpr T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op);
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class T> [[nodiscard]] constexpr T accumulate(InputIterator first, InputIterator last, T init);
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | The type of the reduction initial value, the intermediate accumulated value, and the returned result. |
| `BinaryOperation` | The type of the binary operation callable that merges the accumulated value step by step: accepts the accumulated value T and the value obtained by dereferencing the input iterator, and returns a result convertible to T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |
| `init` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |
| `binary_op` | Input | The binary reduction operation object, which merges the initial value and each element step by step as binary_op(current accumulated value, current element); the overload omitting this parameter uses `operator+`. |

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

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | The numeric result of the input values after the operation specified by the interface. |
| Prototype 2 | `T` | The numeric result of the input values after the operation specified by the interface. |

## Constraints

- `[first, last)` must be a valid readable input range.
- The default overload accumulates as `init + *first`; the custom overload accumulates as `binary_op(init, *first)`, and the result must be assignable back to `T`.
- Inputs are processed in iteration order; the accumulated object is passed to the operation by move semantics. The operation must not modify the input range or invalidate iterators.

## Example

The following example accumulates 1, 2, 3, 4 starting from 0 and returns 10.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::accumulate(input, input + 4, 0);
}

bool verify_example()
{
    return example() == 10;
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)

[Complete usage example](../../../../../../examples/standard/array_statistics/README_en.md).
