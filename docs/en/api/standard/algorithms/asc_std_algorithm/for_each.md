# asc::std::for_each

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

`asc::std::for_each` invokes the function object on every element in the range in order; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class Function>
constexpr Function for_each(InputIterator first, InputIterator last, Function f);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `Function` | Callable object type that performs the operation of this page on the input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `f` | Input | Callable object; invoked once in the form f(elem) on every element in [first, last) in order; returned unchanged after processing. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `Function` | Returns the function object after it has been applied in order to all input elements. |

## Constraints

- Uses C++17.
- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer with sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    asc::std::for_each(values, values + 8, [](int& value) { ++value; });
    const int expected[8] = {9, 4, 7, 2, 8, 3, 6, 5};
    for (int index = 0; index < 8; ++index) { if (values[index] != expected[index]) return false; }
    return true;
}
```

## Related APIs

- [`asc::parallel::for_each`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_for_each.md): Submits an asynchronous device operation using an execution policy.
