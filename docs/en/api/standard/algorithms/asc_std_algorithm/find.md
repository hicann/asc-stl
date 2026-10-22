# asc::std::find

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

`asc::std::find` finds the first element equal to `value` in the half-open range `[first, last)`. It returns the position of that element when found; it returns `last` when the target element does not exist.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator, class T>
[[nodiscard]] constexpr InputIterator find(InputIterator first, InputIterator last, const T& value);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the input range elements or of the values participating in the operation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator to the start of the input range. |
| `last` | Input | Iterator to the end of the input range, not included. |
| `value` | Input | The value to find. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `InputIterator` | Returns the position of the first element equal to value; returns last when not found. |

## Constraints

- Uses C++17.
- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following example finds the value 3 in an integer array and checks the returned position and element value.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4, 5};
    const auto result = asc::std::find(values, values + 5, 3);
    return result == values + 2 && *result == 3;
}
```

## Related APIs

- [`asc::parallel::find`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_find.md): Submits an asynchronous device operation using an execution policy.
