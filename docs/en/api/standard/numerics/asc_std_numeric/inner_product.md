# asc::std::inner_product

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

`asc::std::inner_product` combines two ranges element by element and reduces the results starting from the initial value.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2> [[nodiscard]] constexpr T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2);
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator1, class InputIterator2, class T> [[nodiscard]] constexpr T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init);
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | The iterator type for reading elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | The type of the reduction initial value, the intermediate accumulated value, and the returned result. |
| `BinaryOperation1` | The callable type of the binary reduction operation that merges each pairwise combination result into the accumulated value. |
| `BinaryOperation2` | The callable type of the binary transformation that combines elements at corresponding positions of the two input ranges. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | The starting iterator or pointer of the first input range. |
| `last1` | Input | The end position of the first input range, exclusive. |
| `first2` | Input | The starting iterator of the second input range; the length of this range must not be smaller than the first range. |
| `init` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |
| `binary_op1` | Input | The binary reduction operation object, which merges the result of binary_op2 combining the corresponding elements of the two ranges into the current accumulated value. |
| `binary_op2` | Input | The binary combination operation object, applied to elements at corresponding positions of the two ranges; the overload omitting this parameter uses elementwise multiplication. |

### Parameters of Prototype 2

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
| `init` | Input | The reduction initial value, used as the starting accumulated value for element-by-element merging; returned as is when the range is empty. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | The numeric result of the input values after the operation specified by the interface. |
| Prototype 2 | `T` | The numeric result of the input values after the operation specified by the interface. |

## Constraints

- `[first1, last1)` must be a valid readable input range, and the second range starting from `first2` must have at least the same number of readable elements.
- The default overload multiplies elementwise and accumulates; custom overloads first call `binary_op2` to combine the corresponding elements, then call `binary_op1` to update the accumulated value.
- Inputs are processed in iteration order, and the operation results must be assignable back to `T`; the operations must not modify the input ranges or invalidate iterators.

## Example

The following example multiplies the array by itself elementwise and accumulates the products, returning 30.

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::inner_product(input, input + 4, input, 0);
}

bool verify_example()
{
    return example() == 30;
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
