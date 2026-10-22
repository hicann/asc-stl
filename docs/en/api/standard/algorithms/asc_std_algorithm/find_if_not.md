# asc::std::find_if_not

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

`asc::std::find_if_not` returns the position of the first element in the range that does not satisfy the predicate; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class Predicate>
constexpr InputIterator find_if_not(InputIterator first, InputIterator last, Predicate pred);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `Predicate` | Callable object type that determines whether the elements satisfy the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `pred` | Input | Callable object used to determine whether the elements satisfy the condition. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `InputIterator` | Returns the position of the first element in the range that does not satisfy the predicate. |

## Constraints

- Returns last when every element satisfies the predicate.

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
    auto predicate = [](int value) { return value % 2 == 0; };
    auto result = asc::std::find_if_not(values, values + 8, predicate);
    return result == values;
}
```

## Related APIs

- [`asc::parallel::find_if_not`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_find_if_not.md): Submits an asynchronous device operation using an execution policy.
