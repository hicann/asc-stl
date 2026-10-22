# asc::std::for_each_n

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

`asc::std::for_each_n` invokes the function object on the specified number of elements starting from the start position; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class Size, class Function>
constexpr InputIterator for_each_n(InputIterator first, Size orig_n, Function f);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `Size` | Type representing the number of elements to process, typically an integer type or the iterator difference type. |
| `Function` | Callable object type that performs the operation of this page on the input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `orig_n` | Input | Number of elements starting from first to which the function object is applied. |
| `f` | Input | Callable object; invoked once in the form f(elem) on every element starting from first. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `InputIterator` | Returns the iterator or result object after processing the specified number of elements. |

## Constraints

- Uses C++17.
- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto action = [](int& value) { ++value; };
    auto result = asc::std::for_each_n(values, 4, action);
    return result == values + 4 && values[0] == 2 && values[3] == 5 && values[4] == 5;
}
```

## Related APIs

- [`asc::parallel::for_each_n`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_for_each_n.md): Submits an asynchronous device operation using an execution policy.
